#include <connection.h>

#include <chrono>

#include <helper.h>
#include <exception.h>

const int RMA_CONNECTION = RMA2_CONN_DEFAULT;
const int RRA_BIT = RMA2_CONN_RRA;
const int RRA_CONNECTION = RMA_CONNECTION | RRA_BIT;

Endpoint::Connection::~Connection()
{
    if (this->port != nullptr)
    {
        if (this->handle != nullptr)
        {
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

    int options = rra? RRA_CONNECTION : RMA_CONNECTION;
    status = rma2_connect(port, node, vpid, RMA2_Connection_Options(options), &handle);
    throw_on_error<ConnectionFailed>(status, "Failed to connect!");
}

static void wait_with_timeout(RMA2_Port port, std::chrono::duration<double> timeout)
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

Endpoint::Endpoint(RMA2_Nodeid node)
    : rra(node, true), rma(node, false),
    gp_buffer(rra.port, 1), trace_data(rma.port, 1), hicann_config(rma.port, 1)
{
    RMA2_ERROR status = rma2_post_get_qw(rra.port, rra.handle, gp_buffer.region(), 0, 8, 0x8000, RMA2_COMPLETER_NOTIFICATION, RMA2_CMD_DEFAULT);

    throw_on_error<FailedToRead>(status, "Failed to query driver", node, 0x8000);
    std::chrono::milliseconds timeout(1);
    wait_with_timeout(rra.port, timeout);

    auto driver = gp_buffer.at<uint32_t>(0);
    if (driver != 0xcafebabe)
    {
        throw NodeIsNoFcp(node, driver);
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
