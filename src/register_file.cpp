#include <register_file.h>

#include <sstream>
#include <iostream>

#include <exception.h>
#include <helper.h>



RegisterFile::RegisterFile(Endpoint& connection)
    : connection(connection), status(RMA2_SUCCESS)
{
}

uint64_t RegisterFile::read(RMA2_NLA address) const
{
    status = rma2_post_get_qw_direct(
            connection.rra.port,
            connection.rra.handle,
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
            connection.rra.port,
            connection.rra.handle,
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
    ::wait_for_notification(connection.rra.port);
}

void RegisterFile::wait_for_n_notifications(int n) const
{
    ::wait_for_n_notifications(connection.rra.port, n);
}

void RegisterFile::wait_for_rma_notification() const
{
    RMA2_Notification* notification;
    rma2_noti_get_block(connection.rma.port, &notification);

    rma2_noti_dump(notification);

    rma2_noti_free(connection.rma.port, notification);
}