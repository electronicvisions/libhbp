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
    status = rma2_post_get_qw(
            connection.rra.port,
            connection.rra.handle,
            connection.gp_buffer.region(),
            0, 8, address,
            RMA2_COMPLETER_NOTIFICATION, RMA2_CMD_DEFAULT);

    throw_on_error<FailedToRead>(status, connection.node, address);
    wait_for_notification();

    return connection.gp_buffer[0];
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

void RegisterFile::wait_for_rma_notification(bool dump) const
{
    RMA2_Notification* notification;
    rma2_noti_get_block(connection.rma.port, &notification);

    if (dump)
    {
        rma2_noti_dump(notification);
    }

    rma2_noti_free(connection.rma.port, notification);
}

void RegisterFile::probe() const
{
    RMA2_Notification* notification;

    if (rma2_noti_probe(connection.rra.port, &notification) == RMA2_SUCCESS)
    {
        std::cout << "There is an RRA notification\n";
        rma2_noti_dump(notification);
        rma2_noti_free(connection.rra.port, notification);
    }
    if (rma2_noti_probe(connection.rma.port, &notification) == RMA2_SUCCESS)
    {
        std::cout << "There is an RMA notification\n";
        rma2_noti_dump(notification);
        rma2_noti_free(connection.rma.port, notification);
    }
}
