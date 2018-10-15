#include <connection.h>

#include <helper.h>
#include <exception.h>

const int RMA_CONNECTION = RMA2_CONN_PHYSICAL;
const int RRA_BIT = RMA2_CONN_RRA;
const int RRA_CONNECTION = RMA_CONNECTION | RRA_BIT;

Connection::~Connection()
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


Connection::Connection(RMA2_Nodeid node, bool rra)
        : node(node), gp_buffer(1), trace_data(1), hicann_config(1)
{
    status = rma2_open(&port);
    throw_on_error<ConnectionFailed>(status, "Failed to open port!");
    vpid = rma2_get_vpid(port);

    int options = rra? RRA_CONNECTION : RMA_CONNECTION;
    status = rma2_connect(port, node, vpid, RMA2_Connection_Options(options), &handle);
    throw_on_error<ConnectionFailed>(status, "Failed to connect!");

    if (!rra)
    {
        return;
    }

    status = rma2_post_get_qw_direct(port, handle, gp_buffer.address(), 8, 0x8000, RMA2_COMPLETER_NOTIFICATION, RMA2_CMD_DEFAULT);
    throw_on_error<FailedToRead>(status, "Failed to query driver", node, 0x8000);
    wait_for_notification(port);

    auto driver = uint32_t(gp_buffer.data()[0]);
    if (driver != 0xcafebabe)
    {
        throw NodeIsNoFcp(node, driver);
    }
}

