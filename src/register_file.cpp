#include <register_file.h>

#include <sstream>
#include <iostream>

#include <exception.h>
#include <helper.h>



RegisterFile::RegisterFile(const Connection& connection)
    : connection(connection), status(RMA2_SUCCESS)
{
}

uint64_t RegisterFile::read(RMA2_NLA address) const
{
    status = rma2_post_get_qw_direct(
            connection.port,
            connection.handle,
            connection.gp_buffer.address(),
            8, address,
            RMA2_COMPLETER_NOTIFICATION, RMA2_CMD_DEFAULT);
    throw_on_error<FailedToRead>(status, connection.node, address);
    wait_for_notification();

    return connection.gp_buffer.data()[0];
}

void RegisterFile::write_noblock(RMA2_NLA address, uint64_t value)
{
    status = rma2_post_immediate_put(
            connection.port,
            connection.handle,
            8, value, address,
            RMA2_COMPLETER_NOTIFICATION, RMA2_CMD_DEFAULT
            );
    throw_on_error<FailedToWrite>(status, connection.node, address);
}

void RegisterFile::write(RMA2_NLA address, uint64_t value)
{
    write_noblock(address, value);
    wait_for_notification();
}

void RegisterFile::wait_for_notification() const
{
    ::wait_for_notification(connection.port);
}

void RegisterFile::wait_for_n_notifications(int n) const
{
    ::wait_for_n_notifications(connection.port, n);
}
