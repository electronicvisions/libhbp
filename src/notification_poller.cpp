#include <extoll/notification_poller.h>

#include <extoll/extoll.h>

#include <iostream>

using namespace extoll::library;

NotificationPoller::NotificationPoller(RMA2_Port p)
    : rma(p), thread(&NotificationPoller::poll_notifications, this), running(true)
{
    
}

NotificationPoller::~NotificationPoller()
{
    running = false;
    thread.join();
}

void NotificationPoller::poll_notifications()
{
    while (running)
    {
        RMA2_Notification* notification;
        RMA2_ERROR status = rma2_noti_probe(rma, &notification);

        if (status != RMA2_SUCCESS)
        {
            usleep(100);
            continue;
        }

        RMA2_Class cls = rma2_noti_get_notiput_class(notification);
        uint64_t payload = rma2_noti_get_notiput_payload(notification) & 0xffffffff;

        switch (cls)
        {
        case 0xca:
            trace_packets.fetch_add(payload);
            break;
        case 0xa1:
            hicann_packets.fetch_add(payload);
            break;
        case 0:
            ++rma_responses;
            break;
        default:
            rma2_noti_free(rma, notification);
            throw std::runtime_error("Unknown noti class");
        }

        rma2_noti_free(rma, notification);
    }
}



void NotificationPoller::consume_response()
{
    // TODO: dont wait on atomic, use condition variable instead
    while (rma_responses.load() == 0)
    {
        usleep(100);   
    }
    --rma_responses;
}

uint64_t NotificationPoller::consume_packets(uint64_t type)
{
    // TODO: block if no packets for given type have arrived (e.g. hicann_packets == 0)
    switch (type)
    {
    case Extoll::HICANN_CONFIG:
        return std::atomic_exchange(&hicann_packets, 0ul);
    case Extoll::TRACE_PULSE:
        return std::atomic_exchange(&trace_packets, 0ul);
    default:
        throw std::runtime_error("No packets");        
    }
}

