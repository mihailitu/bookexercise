#include "GFClient.h"
#include "flatbuffers/flatbuffers.h"
#include "gf_generated.h"
#include <iostream>
#include <fstream>

CGigaFlowClient::CGigaFlowClient(const std::string &gigaFlowAddress, int queueSz):
    m_zmqContext(), m_zmqSubSocket(m_zmqContext, ZMQ_SUB),
    m_dZMQQueueSz(queueSz)
{
    m_sGigaFlowAddress = gigaFlowAddress;
}

CGigaFlowClient::~CGigaFlowClient()
{
    CloseConnection();
}

void CGigaFlowClient::StartListener()
{
    if (!m_zmqSubSocket.connected())
        return;
    try {
        m_zmqSubSocket.setsockopt(ZMQ_SUBSCRIBE, "", 0);
        m_zmqSubSocket.setsockopt(ZMQ_RCVHWM, &m_dZMQQueueSz, sizeof(m_dZMQQueueSz));
        m_zmqSubSocket.connect(m_sGigaFlowAddress);
    } catch(...){
        std::cout << "StartListener error\n";
        return;
    };

    m_gfListener = std::thread(&CGigaFlowClient::GFDataHandler, this);
}

bool CGigaFlowClient::Connected() const
{
    return m_zmqSubSocket.connected();
}

void CGigaFlowClient::CloseConnection()
{
    m_bTerminate = true;

    if (m_gfListener.joinable())
        m_gfListener.join();

    try {
        m_zmqSubSocket.disconnect(m_sGigaFlowAddress);
    } catch(...) {
        std::cout << "CloseConnection error\n";
    }
}

void CGigaFlowClient::GFDataHandler()
{
    std::cout << "started DataHandler\n";

    m_bTerminate = false;
    unsigned messCount = 0;
    unsigned long long bytes = 0;
    while(!m_bTerminate) {
        zmq::message_t message;
        if (!m_zmqSubSocket.recv(&message, ZMQ_DONTWAIT))
            continue;
        std::cout << "receiving... ";
        bytes += message.size();
        std::cout << message.size() << '\n';
        ++messCount;
    }
    std::cout << "Listener ended. Received " << messCount << " sizing " << bytes << " bytes!\n";
}
