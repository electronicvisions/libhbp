#ifndef LIBHBP_NOTIFICATION_POLLER
#define LIBHBP_NOTIFICATION_POLLER

#include <atomic>
#include <thread>

#include <extoll/rma.h>

namespace extoll {
namespace library {

class NotificationPoller
{
private:
    RMA2_Port rma;
    std::atomic<uint64_t> rma_responses{0};
    std::atomic<uint64_t> hicann_packets{0};
    std::atomic<uint64_t> trace_packets{0};
    std::thread thread;
    bool running;

    void poll_notifications();
public:
    NotificationPoller(RMA2_Port rma);
    ~NotificationPoller();

    uint64_t consume_packets(uint64_t type);
    void consume_response();
};

}
}

#endif
