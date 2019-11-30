#include "GigaFlowClient.h"

#include <iostream>
#include <vector>
#include <zmq.h>


CGigaFlowClient::CGigaFlowClient(const std::string &gfAddress, unsigned gfPort, int zmqQueueSz, COrsAppDataManager *orsDataManager, message_handler messageHandler) :
	m_sGFAddress(gfAddress),
	m_dGFPort(gfPort),
	m_dZMQQueueSz(zmqQueueSz),
	m_pOrsDataManager(orsDataManager),
	m_pfnMessageHandler(messageHandler)
{
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

int inf(FILE *source, FILE *dest);
bool decompress(void* data, size_t datalen, std::vector<unsigned char> &decompressed);
void zerr(int ret);

unsigned short readShort(std::vector<unsigned char> &data, unsigned short offset)
{
    unsigned short ret;
    memcpy(&ret, data.data() + offset, 2);
    return ret;
    return *(reinterpret_cast<unsigned short *>(data.data() + offset));
}

unsigned short readShort(unsigned char *data, unsigned short offset)
{
    unsigned short ret;
    memcpy(&ret, data + offset, 2);
    return ret;
    return *(reinterpret_cast<unsigned short *>(data + offset));
}

//int resultLength = inflater.inflate(uncompressed); //Uncompress message into uncompressed object/array and return length
//short records = getShort(uncompressed, 0); //Get the flow record count
//int offset = 2; //move pointer after record count
//for (int i = 0; i < records; i++) { //iterate over each record
//    short recordLen = getShort(uncompressed, offset); //Get length of this specific flow record
//    byte[] t = new byte[recordLen]; //buffer to store contents
//    System.arraycopy(uncompressed, offset + 2, t, 0, recordLen); //copy correct flow block from uncompressed to t object/array
//    showRecord(t); //decode flow record
//    offset = offset + 2 + recordLen; //set offset to next message
//}

void CGigaFlowClient::GFDataListener()
{
    unsigned long records = 0;

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
//        unsigned char * decompressed = static_cast<unsigned char*>(zmq_msg_data(&zmqMessage));
//        size_t buffLen = zmq_msg_size(&zmqMessage);

        std::vector<unsigned char> decompressed;//(data, data + dataLen);//(chunk_sz);
        if (!decompress(zmq_msg_data(&zmqMessage), zmq_msg_size(&zmqMessage), decompressed))
            continue;

        size_t buffLen = decompressed.size();
        std::cout << "Decompressed sz " << buffLen << std::endl;

        if (buffLen < 2) // make sure we have enough bytes
            continue;

        unsigned short recNo = readShort(decompressed, 0);
        unsigned short offset = 2; // normally, we will use sizeof(short). But the data comes from a Java program, so harcode it
        std::cout << "Rec no: " << recNo << std::endl;
        for(unsigned i = 0; i < recNo; ++i) {
            if (offset + 2 > buffLen) // the buffer is malformed
                break;

            unsigned short recLen = readShort(decompressed, offset);
            offset += 2;

            if (offset + recLen > buffLen) // the buffer is malformed
                continue;

            const GigaFlow::Data::GFRecord * gfr = GigaFlow::Data::GetGFRecord(decompressed.data() + offset);

            if (m_pfnMessageHandler)
                m_pfnMessageHandler(m_pOrsDataManager, m_sGFAddress, gfr);

            offset += recLen;

//            bytes += zmq_msg_size(&zmqMessage);
//            ++messCount;
            if ((++records % 1000) == 0) {
                std::cout << ".";
                std::cout.flush();
            }
        }

	}
}

#include <zlib.h>

/* Decompress from file source to file dest until stream ends or EOF.
   inf() returns Z_OK on success, Z_MEM_ERROR if memory could not be
   allocated for processing, Z_DATA_ERROR if the deflate data is
   invalid or incomplete, Z_VERSION_ERROR if the version of zlib.h and
   the version of the library linked do not match, or Z_ERRNO if there
   is an error reading or writing the files. */
int inf(FILE *source, FILE *dest)
{
    const unsigned chunk_sz = 16384;
    int ret;
    unsigned have;
    z_stream strm;
    unsigned char in[chunk_sz];
    unsigned char out[chunk_sz];

    /* allocate inflate state */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    ret = inflateInit(&strm);
    if (ret != Z_OK)
        return ret;

    /* decompress until deflate stream ends or end of file */
    do {
        strm.avail_in = fread(in, 1, chunk_sz, source);
        if (ferror(source)) {
            (void)inflateEnd(&strm);
            return Z_ERRNO;
        }
        if (strm.avail_in == 0)
            break;
        strm.next_in = in;

        /* run inflate() on input until output buffer not full */
        do {
            strm.avail_out = chunk_sz;
            strm.next_out = out;
            ret = inflate(&strm, Z_NO_FLUSH);
            assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
            switch (ret) {
            case Z_NEED_DICT:
                ret = Z_DATA_ERROR;     /* and fall through */
            case Z_DATA_ERROR:
            case Z_MEM_ERROR:
                (void)inflateEnd(&strm);
                return ret;
            }
            have = chunk_sz - strm.avail_out;
            if (fwrite(out, 1, have, dest) != have || ferror(dest)) {
                (void)inflateEnd(&strm);
                return Z_ERRNO;
            }
        } while (strm.avail_out == 0);

        /* done when inflate() says it's done */
    } while (ret != Z_STREAM_END);

    /* clean up and return */
    (void)inflateEnd(&strm);
    return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}

static const unsigned chunk_sz = 300 *  // ~300 bytes per flow
                                10000; // ~10.000 records per message

/* report a zlib or i/o error */
void zerr(int ret)
{
    fputs("zpipe: ", stderr);
    switch (ret) {
    case Z_ERRNO:
        if (ferror(stdin))
            fputs("error reading stdin\n", stderr);
        if (ferror(stdout))
            fputs("error writing stdout\n", stderr);
        break;
    case Z_STREAM_ERROR:
        fputs("invalid compression level\n", stderr);
        break;
    case Z_DATA_ERROR:
        fputs("invalid or incomplete deflate data\n", stderr);
        break;
    case Z_MEM_ERROR:
        fputs("out of memory\n", stderr);
        break;
    case Z_VERSION_ERROR:
        fputs("zlib version mismatch!\n", stderr);
        break;
    default:
        std::cerr << "Error: " << ret << std::endl;
    }
}

// decompress data into decompressed vector
bool decompress(void* data, size_t datalen, std::vector<unsigned char> &decompressed)
{
    z_stream zstr;
    zstr.zalloc = Z_NULL;
    zstr.zfree = Z_NULL;
    zstr.opaque = Z_NULL;
    zstr.avail_in = static_cast<unsigned int>(datalen);
    zstr.next_in = static_cast<Bytef*>(data);

    int ret = inflateInit(&zstr);
    if (ret != Z_OK) {
        zerr(ret);
        return false;
    }

    unsigned char outChunk[chunk_sz];

    do {
        zstr.avail_out = chunk_sz;
        zstr.next_out = outChunk;

        ret = inflate(&zstr, Z_NO_FLUSH);
        if (ret != Z_OK && ret != Z_STREAM_END) {
            zerr(ret);
            inflateEnd(&zstr);
            return false;
        }
        decompressed.insert(decompressed.end(), outChunk, outChunk + chunk_sz - zstr.avail_out);
    } while(zstr.avail_out == 0 && ret != Z_STREAM_END);

    inflateEnd(&zstr);

    return true;
}
