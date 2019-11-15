#include "gf_generated.h"
#include "flatbuffers/flatbuffers.h"

#include <string>
#include <thread>
#include <functional>

class CGigaFlowClient {
    // GigaFlow's IP:PORT
    std::string m_sGigaFlowAddress;

    // 0MQ Context
    void *m_zmqContext;

    // 0MQ Subscribe Socket
    void *m_zmqSubSocket;

    // GigaFlow client listener
    std::thread m_gfListener;

    // ZMQ client Queue size
    int m_dZMQQueueSz;

    // maintains the thread running state
    bool m_bTerminate;

    std::function<void(const GigaFlow::Data::GFRecord *gfr)> m_pfnMessageHandler;
public:
    CGigaFlowClient(const std::string &gigaFlowAddress, int queueSz, std::function<void(const GigaFlow::Data::GFRecord *gfr)> messageHandler);
    virtual ~CGigaFlowClient();
    CGigaFlowClient(const CGigaFlowClient &) = delete;
    int InitializeSockets();
    int StartListener();
    void CloseConnection();
    bool Connected() const;
private:
    void GFDataHandler();
};
