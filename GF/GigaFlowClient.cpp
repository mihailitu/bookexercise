#include "GigaFlowClient.h"

#include <iostream>
#include <vector>
#include <zmq.h>

CGigaFlowClient::CGigaFlowClient(const std::string &gfID, const std::string &gfAddress, unsigned gfPort, const std::string &gfPublicKey, int zmqQueueSz, COrsAppDataManager *orsDataManager, message_handler messageHandler) :
    m_sServerID(gfID),
    m_sGFAddress(gfAddress),
    m_dGFPort(gfPort),
    m_sServerPublicKey(gfPublicKey),
    m_dZMQQueueSz(zmqQueueSz),
    m_pOrsDataManager(orsDataManager),
    m_pfnMessageHandler(messageHandler)
{
    m_sPublicKey = "^d5+H{kG&}+Qm-m*I<Ss5iQ&wot:QQbr?+O]MESE";
    m_sSecretKey  = "{}Ff.6:>ItmqX/6gkCaL3hUjNQ@1zPoG]H:/^Xkl";
}

CGigaFlowClient::~CGigaFlowClient()
{
    CloseConnection();
}

int CGigaFlowClient::StartListener()
{
    m_zmqContext = zmq_ctx_new();
    m_zmqSubSocket = zmq_socket(m_zmqContext, ZMQ_REQ);

    int rc = 0;

    if (m_sPublicKey.length() > 0) {
        rc = zmq_setsockopt(m_zmqSubSocket, ZMQ_CURVE_PUBLICKEY, m_sPublicKey.c_str(), m_sPublicKey.length() + 1); // must include null byte
        if (rc) {
            std::cout << "setsockopt public" << '\n';
            return -1;
        }
    }

    if (m_sSecretKey.length() > 0) {
        rc = zmq_setsockopt(m_zmqSubSocket, ZMQ_CURVE_SECRETKEY, m_sSecretKey.c_str(), m_sSecretKey.length() + 1); // must include null byte
        if (rc) {
            std::cout << "setsockopt secret" << '\n';
            return -1;
        }
    }

    if (m_sServerPublicKey.length() > 0) {
        rc = zmq_setsockopt(m_zmqSubSocket, ZMQ_CURVE_SERVERKEY, m_sServerPublicKey.c_str(), m_sServerPublicKey.length() + 1); // must include null byte
        if (rc) {
            std::cout << "setsockopt secret" << '\n';
            return -1;
        }
    }

    //    int linger = 0;
    //    rc = zmq_setsockopt(m_zmqSubSocket, ZMQ_LINGER, &linger, sizeof(linger));
    //    if (rc) {
    //        return -1;
    //    }

//    if (m_dZMQQueueSz > 0) {
//        rc = zmq_setsockopt(m_zmqSubSocket, ZMQ_RCVHWM, &m_dZMQQueueSz, sizeof(m_dZMQQueueSz));
//        if (rc) {
//            return -1;
//        }
//    }

    rc = zmq_connect(m_zmqSubSocket, ("tcp://" + m_sGFAddress + ":" + std::to_string(m_dGFPort)).c_str());
    if (rc)
        return -1;

    m_gfListener = std::thread(&CGigaFlowClient::GFDataListener, this);
    return 0;
}

void CGigaFlowClient::CloseConnection()
{
    std::cout << "Killing connection... ";
    m_bTerminate = true;

    /* zmq_recvmsg() is blocking. Close the context to force zmq_recvmsg() return with -1.
    * We can use zmq_recvmsg(ZMQ_DONTWAIT) to make it non blocking,
    * but then the thread will use processor extensevly */
    zmq_close(m_zmqSubSocket);
    zmq_ctx_destroy(m_zmqContext);

    if (m_gfListener.joinable())
        m_gfListener.join();
    std::cout << "Done!\n";
}

#include <zlib.h>
bool decompress_data(unsigned char *in_data, size_t in_data_size,
                       std::vector<unsigned char> &out_data,
                       unsigned char *temp_buffer, size_t temp_buffer_len, const std::atomic<bool> &terminate)
{
    std::cout << "Decompress..." << in_data_size;
    std::cout.flush();

    z_stream strm;
    strm.zalloc = nullptr;
    strm.zfree = nullptr;
    strm.next_in = static_cast<unsigned char *>(in_data);
    strm.avail_in = static_cast<unsigned int>(in_data_size);
//    strm.next_out = temp_buffer;
//    strm.avail_out = static_cast<unsigned int>(temp_buffer_len);

    int ret = inflateInit(&strm);
    if (ret != Z_OK)
        return false;

    do {
        if (terminate) {
            ret = Z_STREAM_END; // just exit
            break;
        }
        strm.next_out = static_cast<Bytef*>(temp_buffer);
        strm.avail_out = static_cast<unsigned int>(temp_buffer_len);

        ret = inflate(&strm, 0);

        if (out_data.size() < strm.total_out) {
            out_data.insert(out_data.end(), temp_buffer,
                             temp_buffer + strm.total_out - out_data.size());
        }

    } while (ret == Z_OK);

    inflateEnd(&strm);

    if (ret != Z_STREAM_END)
        return false;

    return true;
}

#include <endian.h>
uint16_t readShortBigEndian(std::vector<unsigned char> &data, unsigned offset)
{
    uint16_t ret = *(reinterpret_cast<uint16_t*>(data.data() + offset));
    ret = be16toh(ret);
    return ret;
}

uint64_t readULongLongBigEndian(std::vector<unsigned char> &data, unsigned offset)
{
    uint64_t ret = *(reinterpret_cast<uint64_t *>(data.data() + offset));
    ret = be64toh(ret);
    return ret;
}

uint32_t readIntBigEndian(std::vector<unsigned char> &data, unsigned offset)
{
    uint32_t ret = *(reinterpret_cast<uint32_t *>(data.data() + offset));
    ret = be32toh(ret);
    return ret;
}

/*
 * ZMQ message format after decompression:
 * 8 bytes - timestamp (uint64_t)
 * 4 bytes - records number (uint32_t)
 * for each record:
 * 2 bytes - record length (uint16_t)
 * len bytes - flatbuffer data
 */

void CGigaFlowClient::GFDataListener()
{
    const size_t temp_buffer_len = 300 * // average flow size
                                   100000; // maximum expected records
    // Create the temporary buffer used by decompress_data once and reuse it
    unsigned char temp_buffer[temp_buffer_len];

    std::cout << "Start listening..." << '\n';
    m_bTerminate = false;
    uint64_t lastSeen = 0;

    while (!m_bTerminate) {
        //  {"type":"forensics",
        //   "lastseen":0}
        std::string jsonReq = R"({"type":"forensics","lastseen":)";
        jsonReq += std::to_string(lastSeen);
        jsonReq += "}";
        std::cout << "Request: " << jsonReq << std::endl;

        int rc = zmq_send(m_zmqSubSocket, jsonReq.c_str(), jsonReq.length(), 0);
        if (rc < 0) {
            std::cout << "send error" << '\n';
            continue;
        }
        zmq_msg_t zmqReply;
        zmq_msg_init(&zmqReply);
        rc = zmq_recvmsg(m_zmqSubSocket, &zmqReply, 0);
        if (rc < 0) {
            std::cout << "recv error" << '\n';
            continue;
        }

        std::cout << "received " << zmq_msg_size(&zmqReply) << '\n';

        if (zmq_msg_size(&zmqReply) == 0) { // no new data available
            std::cout << "No data available. Trying again later" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(10)); // try again in 10 seconds
            continue;
        }

        std::cout << "Decompress..." << std::endl;

        unsigned char * inData = static_cast<unsigned char *>(zmq_msg_data(&zmqReply));
        size_t inDataSz = zmq_msg_size(&zmqReply);
        std::vector<unsigned char> decompressed;
        if (!decompress_data(inData, inDataSz, decompressed, temp_buffer, temp_buffer_len, m_bTerminate)) {
            std::cout << "Dec failed" << std::endl;
            continue;
        }

        if (m_bTerminate)
            return;

        size_t buffLen = decompressed.size();
        std::cout << "Decompressed sz " << buffLen << std::endl;

        if (buffLen < sizeof(lastSeen))
            continue;

        unsigned offset = 0;

        lastSeen = readULongLongBigEndian(decompressed, offset);
        offset += sizeof(lastSeen);

        std::cout << "Timestamp: " << lastSeen << std::endl;

        if (buffLen < sizeof(short)) // make sure we have enough bytes
            continue;

        uint32_t recNo = readIntBigEndian(decompressed, offset);
        offset += sizeof(recNo);
        std::cout << "Rec no: " << recNo << std::endl;
        for(unsigned int i = 0; i < recNo; ++i) {
            if (m_bTerminate)
                break;

            if (offset + 2 > buffLen) // the buffer is malformed
                break;

            uint16_t recLen = readShortBigEndian(decompressed, offset);
            offset += sizeof(recLen);

            if (offset + recLen > buffLen) // the buffer is malformed
                break;

            const GigaFlow::Data::GFRecord * gfr = GigaFlow::Data::GetGFRecord(decompressed.data() + offset);

            if (m_pfnMessageHandler)
                m_pfnMessageHandler(m_pOrsDataManager, m_sServerID, gfr);

            offset += recLen;
        }
    }
}
