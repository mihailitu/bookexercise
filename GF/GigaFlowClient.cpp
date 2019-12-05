#include "GigaFlowClient.h"

#include <iostream>
#include <vector>
#include <zmq.h>

CGigaFlowClient::CGigaFlowClient(const std::string &gfAddress, unsigned gfPort, std::string gfPublicKey, int zmqQueueSz, COrsAppDataManager *orsDataManager, message_handler messageHandler) :
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
    m_zmqSubSocket = zmq_socket(m_zmqContext, ZMQ_SUB);

    int rc = zmq_setsockopt(m_zmqSubSocket, ZMQ_SUBSCRIBE, "", 0);
    if (rc)
        return -1;

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

    if (m_dZMQQueueSz > 0) {
        rc = zmq_setsockopt(m_zmqSubSocket, ZMQ_RCVHWM, &m_dZMQQueueSz, sizeof(m_dZMQQueueSz));
        if (rc) {
            return -1;
        }
    }

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
                       unsigned char *temp_buffer, size_t temp_buffer_len)
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

short readShort(std::vector<unsigned char> &data, unsigned offset)
{
    return *(reinterpret_cast<short *>(data.data() + offset));
}

short readShortBigEndian(std::vector<unsigned char> &data, unsigned offset)
{
    // return readShort(data, offset);
    short j;
    j = data[offset];
    j <<= 8;
    j |= data[offset+1];
    return j;
}

void CGigaFlowClient::GFDataListener()
{
    unsigned long records = 0;
    const size_t temp_buffer_len = 300 * // average flow size
                                   10000; // maximum expected records
    // Create the temporary buffer used by decompress_data once and reuse it
    unsigned char temp_buffer[temp_buffer_len];

    std::cout << "Start listening..." << '\n';
    m_bTerminate = false;

    zmq_msg_t zmqMessage;

    while (!m_bTerminate) {
        zmq_msg_init(&zmqMessage);
        int rc = zmq_recvmsg(m_zmqSubSocket, &zmqMessage, 0);
        if (rc < 0) {
            std::cout << "recv error" << '\n';
            continue;
        }

        std::cout << "received " << zmq_msg_size(&zmqMessage) << '\n';

        if (!m_pfnMessageHandler)
            continue;

        std::cout << "Decompress..." << std::endl;

        unsigned char * inData = static_cast<unsigned char *>(zmq_msg_data(&zmqMessage));
        size_t inDataSz = zmq_msg_size(&zmqMessage);
        std::vector<unsigned char> decompressed;
        if (!decompress_data(inData, inDataSz, decompressed, temp_buffer, temp_buffer_len)) {
            std::cout << "Dec failed" << std::endl;
            continue;
        }

        size_t buffLen = decompressed.size();
        std::cout << "Decompressed sz " << buffLen << std::endl;

        if (buffLen < sizeof(short)) // make sure we have enough bytes
            continue;

        short recNo = readShortBigEndian(decompressed, 0);
        unsigned offset = sizeof(recNo); // normally, we will use sizeof(short). But the data comes from a Java program, so harcode it
        std::cout << "Rec no: " << recNo << std::endl;
        // continue;
        for(short i = 0; i < recNo; ++i) {
            if (offset + 2 > buffLen) // the buffer is malformed
                break;

            short recLen = readShortBigEndian(decompressed, offset);
            std::cout << "Rec: " << i << " len: " <<  recLen << std::endl;
            offset += sizeof(recLen);

            if (offset + recLen > buffLen) // the buffer is malformed
                break;

            const GigaFlow::Data::GFRecord * gfr = GigaFlow::Data::GetGFRecord(decompressed.data() + offset);

            if (m_pfnMessageHandler)
                m_pfnMessageHandler(m_pOrsDataManager, m_sGFAddress, gfr);

            offset += recLen;

            if ((++records % 1000) == 0) {
                std::cout << ".";
                std::cout.flush();
            }
        }
    }
}
