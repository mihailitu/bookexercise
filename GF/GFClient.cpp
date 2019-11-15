#include "GFClient.h"
#include "flatbuffers/flatbuffers.h"
#include "gf_generated.h"
#include <iostream>
#include <fstream>

CGigaFlowClient::CGigaFlowClient(const std::string &gigaFlowAddress, int queueSz):
    // m_zmqContext(), m_zmqSubSocket(m_zmqContext, ZMQ_SUB),
    m_state(ConnectionState::DISCONNECTED),
    m_dZMQQueueSz(queueSz)
{
    m_pZmqContext = nullptr;
    m_pZmqSubSocket = nullptr;
    m_sGigaFlowAddress = gigaFlowAddress;
}

CGigaFlowClient::~CGigaFlowClient()
{
    CloseConnection();
}

int CGigaFlowClient::InitializeSockets()
{
    // Socket to talk to clients
    m_pZmqContext = zmq_ctx_new();
    m_pZmqSubSocket = zmq_socket(m_pZmqContext, ZMQ_SUB);

    int rc = zmq_setsockopt(m_pZmqSubSocket, ZMQ_SUBSCRIBE, nullptr, 0);
    if (rc != 0) {
        return rc;
    }

//    rc = zmq_setsockopt(m_pZmqSubSocket, ZMQ_RCVHWM, &m_dZMQQueueSz, m_dZMQQueueSz);
//    if (rc != 0) {
//        return rc;
//    }

    rc = zmq_connect(m_pZmqSubSocket, m_sGigaFlowAddress.c_str());
    if (rc != 0) {
        return rc;
    }

    return 0;
}

void CGigaFlowClient::StartListener()
{
    if (m_pZmqContext || m_pZmqSubSocket) {
        return;
    }

    if (InitializeSockets() != 0) {
        CloseConnection();
        std::cout << "StartListener error\n";
        return;
    }

    m_gfListener = std::thread(&CGigaFlowClient::GFDataHandler, this);
}

void CGigaFlowClient::CloseConnection()
{
    m_bTerminate = true;

    m_gfListener.join();

    if (m_pZmqSubSocket) {
        zmq_close(m_pZmqSubSocket);
        m_pZmqSubSocket = nullptr;
    }

    // Cleanup the contexts
    if (m_pZmqContext) {
        zmq_ctx_destroy(m_pZmqContext);
        m_pZmqContext = nullptr;
    }

    m_state = ConnectionState::DISCONNECTED;
}

void CGigaFlowClient::GFDataHandler()
{
    std::cout << "started DataHandler\n";
    zmq_msg_t zmqMessage;

    m_state = ConnectionState::CONNECTED;
    m_bTerminate = false;
    unsigned messCount = 0;
    unsigned long long bytes = 0;

    while(!m_bTerminate) {

        zmq_msg_init(&zmqMessage);
        // Receive the message
        int rc = zmq_recvmsg(m_pZmqSubSocket, &zmqMessage, ZMQ_DONTWAIT);
        if( rc == -1) {
            continue;
        }
        std::cout << "receiving... ";
        bytes += zmq_msg_size(&zmqMessage);
        std::cout << zmq_msg_size(&zmqMessage) << '\n';
        ++messCount;
    }
    std::cout << "Listener ended. Received " << messCount << " sizing " << bytes << " bytes!\n";
    CloseConnection();
}


//void CGigaFlowClient::StartListener()
//{
//    if (m_state != ConnectionState::DISCONNECTED) {
//        return;
//    }

//    try {
//        m_zmqSubSocket.setsockopt(ZMQ_SUBSCRIBE, "", 0);
//        m_zmqSubSocket.setsockopt(ZMQ_RCVHWM, &m_dZMQQueueSz, sizeof(m_dZMQQueueSz));
//    } catch(...){
//        std::cout << "StartListener error\n";
//        m_state = ConnectionState::ERROR;
//        return;
//    };

//    m_gfListener = std::thread(&CGigaFlowClient::GFDataHandler, this);
//}

//void CGigaFlowClient::CloseConnection()
//{
//    m_bTerminate = true;

//    m_gfListener.join();

//    try {
//        m_zmqSubSocket.close();
//        m_zmqContext.close();
//    } catch(...) {
//        std::cout << "CloseConnection error\n";
//    }
//    m_state = ConnectionState::DISCONNECTED;
//}

//void CGigaFlowClient::GFDataHandler()
//{
//    std::cout << "started DataHandler\n";

//    try {
//        m_zmqSubSocket.connect(m_sGigaFlowAddress);
//    } catch(...) {
//        m_state = ConnectionState::ERROR;
//        std::cout << "DataHandler error\n";
//        return;
//    }

//    m_state = ConnectionState::CONNECTED;
//    m_bTerminate = false;
//    unsigned messCount = 0;
//    unsigned long long bytes = 0;
//    while(!m_bTerminate) {
//        std::cout << "receiving... ";
//        zmq::message_t message;
//        m_zmqSubSocket.recv(&message);

//        bytes += message.size();
//        std::cout << message.size() << '\n';
//        ++messCount;
//    }
//    std::cout << "Listener ended. Received " << messCount << " sizing " << bytes << " bytes!\n";
//    CloseConnection();
//}
