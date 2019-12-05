// #pragma once

#include "gf_generated.h"
#include "flatbuffers/flatbuffers.h"

#include <string>
#include <thread>
#include <functional>

class COrsAppDataManager {

};


class CGigaFlowClient {
public:
	using message_handler = std::function<void(COrsAppDataManager *orsDataManager, const std::string &gfName, const GigaFlow::Data::GFRecord *gfr)>;
private:
    // GigaFlow ID
    std::string m_sServerID;

	// GigaFlow's tcp://addr:PORT
	std::string m_sGFAddress;
	unsigned m_dGFPort;

	// ZMQ context
	void *m_zmqContext;

	// ZMQ subscriber socket
	void *m_zmqSubSocket;

	// ZMQ CURVE encryption keys
    std::string m_sPublicKey;
    std::string m_sSecretKey;
    std::string m_sServerPublicKey;

	// GigaFlow client listener thread
	std::thread m_gfListener;

	// ZMQ client Queue size - increase client's queue size so it doesn't get behind the server
	// TODO: determine this value from testing with Apex connected with several GigaFlows (5-10) running at 50.000 flows per second
	int m_dZMQQueueSz;

	// maintains the thread running state
	bool m_bTerminate;

	// COrsAppDataManager instance
	COrsAppDataManager *m_pOrsDataManager;

	// GigaFlow data handler
	// To pass a member function as a handler, use:
	// auto fp = std::bind(&ClassName::member_func, class_inst, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	// CGigaFlowClient gfclient(addr, port, queueSz, dataManager, fp);
	message_handler m_pfnMessageHandler;

public:
	/**
	 * @brief CGigaFlowClient constructor
     * @param gfID  - Gigaflow server ID
	 * @param gfAddress  - Gigaflow address string
	 * @param gfPort     - GigaFlow's zmq server port
     * @param gfPublicKey - GigaFlow's public key, used by ZMQ Curve
	 * @param zmqQueueSz - ZMQ client Queue size
	 * @param orsDataManager - COrsAppDataManager instance
	 * @param messageHandler - data handler
	**/
    CGigaFlowClient(const std::string &gfID, const std::string &gfAddress, unsigned gfPort, const std::string &gfPublicKey, int zmqQueueSz,
		COrsAppDataManager *orsDataManager, message_handler messageHandler);
	virtual ~CGigaFlowClient();

	/**
	* @brief StartListener start listener thread
	* @return 0 if succesfull, non-zero otherwise
	**/
	int StartListener();

	/**
	* @brief CloseConnection - close GigaFlow conection. The connection can be restarted
	**/
	void CloseConnection();
private:

	// Connection's thread function
	void GFDataListener();
};
