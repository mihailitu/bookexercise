#include "GFClient.h"
#include "flatbuffers/flatbuffers.h"
#include "gf_generated.h"
#include <iostream>
#include <fstream>

CGigaFlowClient::CGigaFlowClient(const std::string &gigaFlowAddress, int queueSz):
    m_pZmqContext(), m_pZmqSubSocket(m_pZmqContext, ZMQ_SUB), m_state(ConnectionState::DISCONNECTED),
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
    if (m_state != ConnectionState::DISCONNECTED) {
        return;
    }

    try {
        m_pZmqSubSocket.setsockopt(ZMQ_SUBSCRIBE, "", 0);
        m_pZmqSubSocket.setsockopt(ZMQ_RCVHWM, &m_dZMQQueueSz, sizeof(m_dZMQQueueSz));
    } catch(...){
        std::cout << "StartListener error\n";
        m_state = ConnectionState::ERROR;
        return;
    };

    m_gfListener = std::thread(&CGigaFlowClient::GFDataHandler, this);
}

void CGigaFlowClient::CloseConnection()
{
    m_bTerminate = true;

    m_gfListener.join();

    try {
        m_pZmqSubSocket.close();
        m_pZmqContext.close();
    } catch(...) {
        std::cout << "CloseConnection error\n";
    }
    m_state = ConnectionState::DISCONNECTED;
}

void CGigaFlowClient::GFDataHandler()
{
    std::cout << "started DataHandler\n";

    try {
        m_pZmqSubSocket.connect(m_sGigaFlowAddress);
    } catch(...) {
        m_state = ConnectionState::ERROR;
        std::cout << "DataHandler error\n";
        return;
    }

    m_state = ConnectionState::CONNECTED;
    m_bTerminate = false;
    unsigned messCount = 0;
    unsigned long long bytes = 0;
    while(!m_bTerminate) {
        std::cout << "receiving... ";
        zmq::message_t message;
        m_pZmqSubSocket.recv(&message);

        bytes += message.size();
        std::cout << message.size() << '\n';
        ++messCount;
    }
    std::cout << "Listener ended. Received " << messCount << " sizing " << bytes << " bytes!\n";
}

//std::string current_time() {
//    char timebuffer[100];
//    std::time_t t = std::time(nullptr);
//    std::size_t tlen = std::strftime(timebuffer, sizeof(timebuffer), "%Y.%m.%d-%H-%M-%S", std::localtime(&t));
//    if (tlen == 0)
//        return "";
//    return std::string(timebuffer, tlen);
//}

//int main (/*int argc, char *argv[]*/)
//{
//    zmq::context_t context = zmq::context_t(1);

//    //  Connect our subscriber socket
//    // zmq::socket_t subSocket = zmq::socket_t(context, ZMQ_PULL);
//    // subSocket.setsockopt(ZMQ_IDENTITY, "Hello", 5);
//    zmq::socket_t subSocket = zmq::socket_t(context, ZMQ_SUB);
//    subSocket.setsockopt(ZMQ_SUBSCRIBE, "", 0);
//    subSocket.connect("tcp://office13.anuview.net:5555");
//    // subSocket.connect("tcp://77.95.160.93:5555");

//    std::string fName = "GFR_" + current_time() + ".txt";
//    std::ofstream out(fName);
//    if(!out.is_open()) {
//        std::cout << "Cannot create " << fName << '\n';
//        return -1;
//    }

//    std::cout << "Start receiving. ";
//    std::cout.flush();
//    unsigned records = 0;
//    unsigned long bytes = 0;
//    auto start = std::chrono::high_resolution_clock::now();
//    std::vector<GigaFlowRecord> rawRecords;
//    // rawRecords.resize(N);
//    //  Get updates, expect random Ctrl-C death
//    while (true) {
//        zmq::message_t receiveMessage;
//        subSocket.recv(&receiveMessage);

//        flatbuffers::FlatBufferBuilder fbb;
//        GigaFlow::Data::GFRecordBuilder gfb(fbb);

//        auto gfr = GigaFlow::Data::GetGFRecord(receiveMessage.data());
//        // GigaFlowRecord gfrecord = recreate_record(gfr);

//        // rawRecords.push_back(gfrecord);
//        // recreate_record(gfr);
//        write_gf_record(out, gfr);
//        bytes += receiveMessage.size();
//        // Show progress for each 1000 records
        
//        if ((++records % 1000) == 0) {
//            std::cout << records << '\n';
//        }
//    }
//    auto end = std::chrono::high_resolution_clock::now();
//    auto duration = std::chrono::duration_cast<std::chrono::seconds>( end - start ).count();
//    std::cout << "Done in " << duration << " seconds\n";
//    std::cout << "Received " << records << " records summing " << bytes << "bytes\n";

//    out.close();
//    return 0;
//}
