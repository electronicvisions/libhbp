#include <extoll/jtag.h>

#include <extoll/hbp_def.h>
#include <extoll/exception.h>

using namespace extoll::library;

using namespace rf;
using namespace jtag;
using Cmd = JtagCmd::Type;


void JTag::wait_until_finished() const
{
    while (RegisterFile::read<JtagCmd>().execute);
}

void JTag::reset()
{
    RegisterFile::write<JtagCmd>({Cmd::Reset, 6, false, true});
    wait_until_finished();
}

void JTag::set_bypass()
{
    RegisterFile::write(JtagSend::ADDRESS, 0x3f);
    RegisterFile::write<JtagCmd>({Cmd::IR, 6, false, true});
    wait_until_finished();
}

void JTag::set_command(uint64_t command)
{
    RegisterFile::write(JtagSend::ADDRESS, command);
    RegisterFile::write<JtagCmd>({JtagCmd::IR, 6, false, true});
    wait_until_finished();
}

void JTag::set_data(uint64_t data, uint16_t length)
{
    RegisterFile::write(JtagSend::ADDRESS, data);
    RegisterFile::write<JtagCmd>({JtagCmd::DR, length, false, true});
    wait_until_finished();
}

uint64_t JTag::set_get_data(uint64_t data, uint16_t length)
{
    set_data(data, length);
    return RegisterFile::read(JtagReceive::ADDRESS);
}

uint64_t JTag::get_data(uint16_t length)
{
    RegisterFile::write<JtagCmd>({JtagCmd::DR, length, false, true});
    wait_until_finished();
    return RegisterFile::read(JtagReceive::ADDRESS);
}

JTag::JTag(Endpoint& connection)
    : RegisterFile(connection)
{
    if (read<ID>() != 0x14849434)
    {
        throw NodeHasNoHicann(connection.node);
    }
}
