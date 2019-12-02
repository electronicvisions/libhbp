#include <extoll/register_file.h>

#include <sstream>
#include <iostream>

#include <extoll/exception.h>
#include <extoll/helper.h>

using namespace extoll::library;

RegisterFile::RegisterFile(Endpoint& connection)
    : _connection(connection), _status(RMA2_SUCCESS)
{
}

uint64_t RegisterFile::read_noblock(RMA2_NLA address) const
{
    _status = rma2_post_get_qw(_connection.rra.port, _connection.rra.handle,
    _connection.gp_buffer.region(), 0, 8, address, RMA2_COMPLETER_NOTIFICATION, RMA2_CMD_DEFAULT);
    throw_on_error<FailedToRead>(_status, _connection.node, address);

    usleep(1000);

    return _connection.gp_buffer[0];
}

uint64_t RegisterFile::read(RMA2_NLA address) const
{
    _status = rma2_post_get_qw(
            _connection.rra.port,
            _connection.rra.handle,
            _connection.gp_buffer.region(),
            0, 8, address,
            RMA2_COMPLETER_NOTIFICATION, RMA2_CMD_DEFAULT);

    throw_on_error<FailedToRead>(_status, _connection.node, address);
    wait_for_notification();

    return _connection.gp_buffer[0];
}

void RegisterFile::write_noblock(RMA2_NLA address, uint64_t value)
{
    _status = rma2_post_immediate_put(
            _connection.rra.port,
            _connection.rra.handle,
            8, value, address,
            RMA2_COMPLETER_NOTIFICATION, RMA2_CMD_DEFAULT
            );
    throw_on_error<FailedToWrite>(_status, _connection.node, address);
}

void RegisterFile::write(RMA2_NLA address, uint64_t value)
{
    write_noblock(address, value);
    wait_for_notification();
}

void RegisterFile::wait_for_notification() const
{
    ::wait_for_notification(_connection.rra.port);
}

void RegisterFile::wait_for_n_notifications(int n) const
{
    ::wait_for_n_notifications(_connection.rra.port, n);
}

void RegisterFile::wait_for_rma_notification(bool dump) const
{
    RMA2_Notification* notification;
    rma2_noti_get_block(_connection.rma.port, &notification);

    if (dump)
    {
        rma2_noti_dump(notification);
    }

    rma2_noti_free(_connection.rma.port, notification);
}

bool RegisterFile::probe() const
{
    RMA2_Notification* notification;

    if (rma2_noti_probe(_connection.rra.port, &notification) == RMA2_SUCCESS)
    {
        std::cout << "There is an RRA notification\n";
        rma2_noti_dump(notification);
        rma2_noti_free(_connection.rra.port, notification);
        return true;
    }
    if (rma2_noti_probe(_connection.rma.port, &notification) == RMA2_SUCCESS)
    {
        std::cout << "There is an RMA notification\n";
        rma2_noti_dump(notification);
        rma2_noti_free(_connection.rma.port, notification);
        return true;
    }
    return false;
}
