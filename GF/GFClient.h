#include <zmq.hpp>
#include <string>
#include <thread>

class CGigaFlowClient {
public:
    enum class ConnectionState {
        DISCONNECTED,
        CONNECTED,
        ERROR,
    };

private:
    // GigaFlow's IP:PORT
    std::string m_sGigaFlowAddress;

    // 0MQ Context
    zmq::context_t m_pZmqContext;

    // 0MQ Subscribe Socket
    zmq::socket_t m_pZmqSubSocket;

    // GigaFlow client listener
    std::thread m_gfListener;

    // Client connection state
    ConnectionState m_state;

    // ZMQ client Queue size
    int m_dZMQQueueSz;

    bool m_bTerminate;
public:
    CGigaFlowClient(const std::string &gigaFlowAddress, int queueSz);
    virtual ~CGigaFlowClient();
    CGigaFlowClient(const CGigaFlowClient &) = delete;
    void StartListener();
    void CloseConnection();
private:
    void GFDataHandler();
};
