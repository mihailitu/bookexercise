#include "gf_generated.h"
#include "flatbuffers/flatbuffers.h"

#include <string>
#include <thread>
#include <functional>

class CGigaFlowClient {
public:
    using message_handler = std::function<void(const std::string &gfName, const GigaFlow::Data::GFRecord *gfr)>;
    // GigaFlow's tcp://addr:PORT
    std::string m_sGFAddress;
    unsigned m_dGFPort;

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

    message_handler m_pfnMessageHandler;
public:
    CGigaFlowClient(const std::string &gfAddress, unsigned gfPort, int zmqQueueSz, message_handler messageHandler);
    virtual ~CGigaFlowClient();
    int InitializeSockets();
    int StartListener();
    void CloseConnection();
    bool Connected() const;
private:
    void GFDataHandler();
};
