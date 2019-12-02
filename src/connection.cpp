#include <sys/ioctl.h>
#include <rma2_ioctl.h>


#include <extoll/connection.h>

#include <chrono>
#include <iostream>

#include <extoll/extoll.h>
#include <extoll/helper.h>
#include <extoll/exception.h>
#include <extoll/utility/rng.h>

using namespace extoll::library;

const int RMA_CONNECTION = RMA2_CONN_DEFAULT;
const int RRA_BIT = RMA2_CONN_RRA;
const int RRA_CONNECTION = uint32_t(RMA_CONNECTION) | uint32_t(RRA_BIT);

Endpoint::Connection::~Connection()
{
    if (port != nullptr)
    {
        if (handle != nullptr)
        {
            size_t ignored_notifications = 0;
            RMA2_Notification* notification;
            while (rma2_noti_probe(port, &notification) == RMA2_SUCCESS)
            {
                rma2_noti_free(port, notification);
                ++ignored_notifications;
            }
            if (ignored_notifications)
            {
                std::cerr << "Ignored Notifications: " << ignored_notifications << "\n";
            }
            rma2_disconnect(port, handle);
        }

        rma2_close(port);
    }
}


Endpoint::Connection::Connection(RMA2_Nodeid node, bool rra)
{
    status = rma2_open(&port);
    throw_on_error<ConnectionFailed>(status, "Failed to open port!");
    vpid = rma2_get_vpid(port);

    std::cout << "got vpid " << vpid << " << " << rra << "\n";

    int options = rra? RRA_CONNECTION : RMA_CONNECTION;
    status = rma2_connect(port, node, vpid, RMA2_Connection_Options(options), &handle);
    throw_on_error<ConnectionFailed>(status, "Failed to connect!");
}

static void wait_with_timeout(RMA2_Port port, std::chrono::duration<double> timeout=std::chrono::milliseconds(1))
{
    using namespace std::chrono;

    RMA2_Notification* notification;
    auto start = high_resolution_clock::now();
    high_resolution_clock::time_point end;
    do
    {
        RMA2_ERROR status = rma2_noti_probe(port, &notification);
        if (status == RMA2_SUCCESS)
        {
            rma2_noti_free(port, notification);
            return;
        }

        end = high_resolution_clock::now();
    }
    while(duration_cast<duration<double>>(end - start) < timeout);

    throw ConnectionFailed("No response from node");
}

Endpoint::Endpoint(RMA2_Nodeid n)
    : node(n), rra(n, true), rma(n, false),
    gp_buffer(rra.port, 1),
    trace_data(rma.port, rma.handle, 100, Extoll::TRACE_PULSE),
    hicann_config(rma.port, rma.handle, 100, Extoll::HICANN_CONFIG)
{
    RMA2_ERROR status = rma2_post_get_qw(rra.port, rra.handle, gp_buffer.region(), 0, 8, 0x8000, RMA2_COMPLETER_NOTIFICATION, RMA2_CMD_DEFAULT);
    throw_on_error<FailedToRead>(status, "Failed to query driver", n, 0x8000u);
    wait_with_timeout(rra.port);

    auto driver = gp_buffer.at<uint32_t>(0);
    if (driver != 0xcafebabe)
    {
        throw NodeIsNoFpga(n, driver);
    }

    Rng<uint64_t> rng;
    for (RMA2_NLA address = 0x480; address < 0x500; ++address)
    {
        auto pattern = rng.roll();
        perform_write_test(address, pattern);
        perform_read_test(address, pattern);
    }
}

void Endpoint::perform_write_test(RMA2_NLA address, uint64_t value)
{
    RMA2_ERROR status = rma2_post_immediate_put(rra.port, rra.handle, 8, value, address, RMA2_COMPLETER_NOTIFICATION, RMA2_CMD_DEFAULT);
    throw_on_error<FailedToWrite>(status, "Failed to send write command", node, address);
    wait_with_timeout(rra.port);
}

void Endpoint::perform_read_test(RMA2_NLA address, uint64_t expected)
{
    RMA2_ERROR status = rma2_post_get_qw(rra.port, rra.handle, gp_buffer.region(), 0, 8, address, RMA2_COMPLETER_NOTIFICATION, RMA2_CMD_DEFAULT);
    throw_on_error<FailedToRead>(status, "Failed to send read command", node, address);
    wait_with_timeout(rra.port);

    if (expected != gp_buffer.at<uint64_t>(0))
    {
        throw FailedToRead(node, address);
    }
}

uint64_t Endpoint::fpga_config_response() const
{
    return gp_buffer[512];
}

RMA2_NLA Endpoint::fpga_config_address() const
{
    return gp_buffer.address(512);
}
