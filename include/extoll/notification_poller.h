#ifndef LIBHBP_NOTIFICATION_POLLER
#define LIBHBP_NOTIFICATION_POLLER

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <thread>

#include <extoll/rma.h>

namespace extoll {
namespace library {

class NotificationPoller
{
private:
	RMA2_Port rma;
	uint64_t rma_responses{0};
	uint64_t hicann_packets{0};
	uint64_t trace_packets{0};
	uint64_t fpga_response{0};

	std::atomic<bool> running;
	std::thread thread;
	std::mutex mutex;
	std::condition_variable cv;

	void poll_notifications();

public:
	NotificationPoller(RMA2_Port rma);
	~NotificationPoller();

	uint64_t consume_packets(uint64_t type, std::chrono::milliseconds);
	bool consume_response(std::chrono::milliseconds);
	bool consume_fpga_response(std::chrono::milliseconds);
};

}
}

#endif
