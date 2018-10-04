#include <register_file.h>

#include <sstream>
#include <iostream>

#include <exception.h>
#include <helper.h>



RegisterFile::RegisterFile(const Connection& connection)
    : connection(connection), status(RMA2_SUCCESS)
{
}

uint64_t RegisterFile::get(RMA2_NLA address) const
{
    status = rma2_post_get_qw_direct(
            connection.port,
            connection.handle,
            connection.gp_buffer.address(),
            8, address,
            RMA2_COMPLETER_NOTIFICATION, RMA2_CMD_DEFAULT);
    throw_on_error("Failed to read @0x", std::hex, address);
    wait_for_notification();

    return connection.gp_buffer.data()[0];
}

uint64_t RegisterFile::get(rf::Readable read) const
{
    return get(static_cast<RMA2_NLA>(read));
}

uint64_t RegisterFile::get(rf::ReadWrite read) const
{
    return get(static_cast<RMA2_NLA>(read));
}

void RegisterFile::set_noblock(RMA2_NLA address, uint64_t value)
{
    status = rma2_post_immediate_put(
            connection.port,
            connection.handle,
            8, value, address,
            RMA2_COMPLETER_NOTIFICATION, RMA2_CMD_DEFAULT
            );
    throw_on_error("Failed to set @0x", std::hex, address);
}

void RegisterFile::set(RMA2_NLA address, uint64_t value)
{
    set_noblock(address, value);
    wait_for_notification();
}

void RegisterFile::set(rf::ReadWrite address, uint64_t value)
{
    set(static_cast<RMA2_NLA>(address), value);
}

template <typename... Args>
void RegisterFile::throw_on_error(Args... args) const
{
    ::throw_on_error<RMAError>(status, args...);
}

void RegisterFile::wait_for_notification() const
{
    ::wait_for_notification(connection.port);
}

void RegisterFile::wait_for_n_notifications(int n) const
{
    ::wait_for_n_notifications(connection.port, n);
}

