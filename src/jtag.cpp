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
    RegisterFile::write<JtagCmd>({Cmd::Reset, 6*8, false, true});
    wait_until_finished();
}

void JTag::set_bypass()
{
    RegisterFile::write(JtagSend::ADDRESS, 0xffffffffffff);
    RegisterFile::write<JtagCmd>({Cmd::IR, 6*8, false, true});
    wait_until_finished();
}

void JTag::shift_command(uint64_t command)
{
    RegisterFile::write(JtagSend::ADDRESS, command);
    RegisterFile::write<JtagCmd>({JtagCmd::IR, 6 * _hicanns, false, true});
    wait_until_finished();
}

void JTag::set_command(uint64_t command)
{
    uint64_t combined = 0;
    for (size_t i = 0; i < _hicanns; ++i)
    {
        combined = (combined << 6) | command;
    }
    shift_command(combined);
}

void JTag::set_command(uint64_t command, uint8_t hicann)
{
    uint64_t inverted = (0x3f ^ command);
    uint64_t shifted = inverted << (6 * (_hicanns - 1 - hicann));
    command = ~shifted;

    shift_command(command);
}

void JTag::set_data(uint64_t data, uint16_t length, uint8_t hicann)
{
    length += _hicanns - 1;
    data = data << (_hicanns - 1 - hicann);

    RegisterFile::write(JtagSend::ADDRESS, data);
    RegisterFile::write<JtagCmd>({JtagCmd::DR, length, false, true});
    wait_until_finished();
}

uint64_t JTag::set_get_data(uint64_t data, uint16_t length, uint8_t hicann)
{
    set_data(data, length, hicann);
    return RegisterFile::read(JtagReceive::ADDRESS) >> (_hicanns - 1 - hicann);
}

uint64_t JTag::get_data(uint16_t length, uint8_t hicann)
{
    length += _hicanns - 1;
    RegisterFile::write<JtagCmd>({JtagCmd::DR, length, false, true});
    wait_until_finished();
    return RegisterFile::read(JtagReceive::ADDRESS) >> (_hicanns - 1 - hicann);
}

JTag::JTag(Endpoint& connection)
    : RegisterFile(connection)
{
    set_bypass();

    RegisterFile::write(JtagSend::ADDRESS, 1);
    RegisterFile::write<JtagCmd>({Cmd::DR, 9, false, true});
    wait_until_finished();

    auto shifted = RegisterFile::read(JtagReceive::ADDRESS);
    shifted = (shifted >> 1) & 0xff;

    if (!shifted)
    {
        throw NodeHasNoHicann(connection.node);
    }

    while (shifted)
    {
        ++_hicanns;
        shifted >>= 1;
    }
}


size_t JTag::active_hicanns() const
{
    return _hicanns;
}
