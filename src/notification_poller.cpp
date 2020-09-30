#include <extoll/notification_poller.h>

#include <extoll/extoll.h>

#include <chrono>
#include <iostream>

using namespace extoll::library;

NotificationPoller::NotificationPoller(RMA2_Port p) :
    rma{p}, running{true}, thread{&NotificationPoller::poll_notifications, this}, mutex{}, cv{}
{}

NotificationPoller::~NotificationPoller()
{
	running.store(false);
	thread.join();
}

void NotificationPoller::poll_notifications()
{
	while (running) {
		RMA2_Notification* notification;
		RMA2_ERROR status = rma2_noti_probe(rma, &notification);

		if (status != RMA2_SUCCESS) {
			usleep(100);
			continue;
		}

		RMA2_Class cls = rma2_noti_get_notiput_class(notification);
		uint64_t payload = rma2_noti_get_notiput_payload(notification) & 0xffffffff;
		rma2_noti_free(rma, notification);
		{
			std::lock_guard<std::mutex> lock{mutex};

			switch (cls) {
				case 0xca:
					trace_packets += payload;
					break;
				case 0xa1:
					hicann_packets += payload;
					break;
				case 0x7:
					++fpga_response;
					break;
				case 0:
					++rma_responses;
					break;
				default:
					std::cerr << "Unknown notification class: " << uint16_t(cls) << "\n";
					throw std::runtime_error("Unknown notification class");
			}
		}
		cv.notify_all();
	}
}


bool NotificationPoller::consume_response(std::chrono::milliseconds timeout)
{
	std::unique_lock<std::mutex> lock{mutex};

	if (rma_responses > 0) {
		--rma_responses;
		return true;
	}

	cv.wait_for(lock, timeout, [this] { return this->rma_responses > 0; });
	if (rma_responses > 0) {
		--rma_responses;
		return true;
	}
	return false;
}

bool NotificationPoller::consume_fpga_response(std::chrono::milliseconds timeout)
{
	std::unique_lock<std::mutex> lock{mutex};

	if (fpga_response > 0) {
		--fpga_response;
		return true;
	}

	cv.wait_for(lock, timeout, [this] { return this->fpga_response > 0; });
	if (fpga_response > 0) {
		--fpga_response;
		return true;
	}
	return false;
}

uint64_t NotificationPoller::consume_packets(uint64_t type, std::chrono::milliseconds timeout)
{
	uint64_t* packets = nullptr;
	switch (type) {
		case Extoll::HICANN_CONFIG:
			packets = &hicann_packets;
			break;
		case Extoll::TRACE_PULSE:
			packets = &trace_packets;
			break;
		default:
			return 0;
	}

	std::unique_lock<std::mutex> lock{mutex};


	uint64_t tmp = *packets;
	if (tmp > 0) {
		*packets = 0;
		return tmp;
	}

	cv.wait_for(lock, timeout, [packets] { return *packets > 0; });
	tmp = *packets;

	*packets = 0;
	return tmp;
}
