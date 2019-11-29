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

#include <zlib.h>

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

void decompress(const void* const data, unsigned datalen)
{
    z_stream zstr;
    zstr.zalloc = Z_NULL;
    zstr.zfree = Z_NULL;
    zstr.opaque = Z_NULL;
    zstr.avail_in = datalen;
    zstr.next_in = (Bytef*)data;

    int ret = inflateInit(&zstr);
    std::vector<char> decompressed;
    const unsigned chunk_sz = 1024;
    char outChunck[chunk_sz];

    do {

    } while(true);

}

void CGigaFlowClient::GFDataListener()
{
    unsigned long records = 0;

    std::cout << "Start listening..." << '\n';
	m_bTerminate = false;
	unsigned messCount = 0;
	unsigned long long bytes = 0;
	zmq_msg_t zmqMessage;

	while (!m_bTerminate) {
		zmq_msg_init(&zmqMessage);
		int rc = zmq_recvmsg(m_zmqSubSocket, &zmqMessage, 0);
        if (rc < 0) {
            std::cout << "recv error" << '\n';
			continue;
        }

        z_stream zstr;

        if ((++records % 1000) == 0) {
            std::cout << ".";
            std::cout.flush();
        }
        flatbuffers::FlatBufferBuilder fbb;
        GigaFlow::Data::GFRecordBuilder gfb(fbb);

        if (m_pfnMessageHandler)
            m_pfnMessageHandler(m_pOrsDataManager, m_sGFAddress, GigaFlow::Data::GetGFRecord(zmq_msg_data(&zmqMessage)));
		bytes += zmq_msg_size(&zmqMessage);
		++messCount;
	}
}
