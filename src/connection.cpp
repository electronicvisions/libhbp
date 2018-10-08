#include <connection.h>

#include <helper.h>
#include <exception.h>

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


Connection::Connection(RMA2_Nodeid node)
        : node(node), gp_buffer(1), trace_data(1), hicann_config(1)
{
    status = rma2_open(&port);
    throw_on_error<ConnectionFailed>(status, "Failed to open port!");
    vpid = rma2_get_vpid(port);
    status = rma2_connect(port, node, vpid, RMA2_Connection_Options(RMA2_CONN_PHYSICAL | RMA2_CONN_RRA), &handle);
    throw_on_error<ConnectionFailed>(status, "Failed to connect!");

    status = rma2_post_get_qw_direct(port, handle, gp_buffer.address(), 8, 0x8000, RMA2_COMPLETER_NOTIFICATION, RMA2_CMD_DEFAULT);
    throw_on_error<FailedToRead>(status, "Failed to query driver", node, 0x8000);
    wait_for_notification(port);

    auto driver = uint32_t(gp_buffer.data()[0]);
    if (driver != 0xcafebabe)
    {
        throw NodeIdNoPcb(node, driver);
    }
}

