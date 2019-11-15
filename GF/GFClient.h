// #include <zmq.hpp>
#include <string>
#include <thread>

class CGigaFlowClient {
    // GigaFlow's IP:PORT
    std::string m_sGigaFlowAddress;

//    // 0MQ Context
//    zmq::context_t m_zmqContext;

//    // 0MQ Subscribe Socket
//    zmq::socket_t m_zmqSubSocket;

    // 0MQ Context
    void *m_zmqContext;

    // 0MQ Subscribe Socket
    void *m_zmqSubSocket;

    // GigaFlow client listener
    std::thread m_gfListener;

    // ZMQ client Queue size
    int m_dZMQQueueSz;

    bool m_bTerminate;
public:
    CGigaFlowClient(const std::string &gigaFlowAddress, int queueSz);
    virtual ~CGigaFlowClient();
    CGigaFlowClient(const CGigaFlowClient &) = delete;
    int InitializeSockets();
    int StartListener();
    void CloseConnection();
    bool Connected() const;
private:
    void GFDataHandler();
};
