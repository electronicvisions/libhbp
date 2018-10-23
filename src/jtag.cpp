#include <jtag.h>

#include <register_files.h>
#include <exception.h>

using namespace rf;
using namespace jtag;
using Cmd = JtagCmd::Type;

uint64_t JTag::read(Readable read_command)
{
    RegisterFile::write<JtagSend>({static_cast<uint8_t>(read_command)});
    RegisterFile::write<JtagCmd>({Cmd::IR, 6, false, true});
    wait_until_finished();

    auto pattern = RegisterFile::read(JtagReceive::ADDRESS) & 0x3f;
    if (pattern != 0x3d)
    {
        throw JtagIrShiftFailed(connection.node, uint8_t(pattern));
    }

    RegisterFile::write<JtagSend>({0});
    RegisterFile::write<JtagCmd>({Cmd::DR, 64, false, true});
    wait_until_finished();

    return RegisterFile::read(JtagReceive::ADDRESS);
}

void JTag::write(jtag::Writable write_command, uint64_t value, uint16_t shift)
{
    RegisterFile::write<JtagSend>({static_cast<uint8_t>(write_command)});
    RegisterFile::write<JtagCmd>({Cmd::IR, 6, false, true});
    wait_until_finished();

    RegisterFile::write<JtagSend>({value});
    RegisterFile::write<JtagCmd>({Cmd::DR, shift, false, true});
    wait_until_finished();
}


uint64_t JTag::write(jtag::ReadWrite command, uint64_t value, uint16_t shift)
{
    RegisterFile::write<JtagSend>({static_cast<uint8_t>(command)});
    RegisterFile::write<JtagCmd>({Cmd::IR, 6, false, true});
    wait_until_finished();

    RegisterFile::write<JtagSend>({value});
    RegisterFile::write<JtagCmd>({Cmd::DR, shift, false, true});
    wait_until_finished();

    return RegisterFile::read(JtagReceive::ADDRESS);
}


void JTag::wait_until_finished() const
{
    while (RegisterFile::read<JtagCmd>().execute);
}

void JTag::reset()
{
    RegisterFile::write<JtagCmd>({Cmd::Reset, 6, false, true});
    wait_until_finished();
}

std::ostream& operator<<(std::ostream& out, const JTag& jtag)
{
    auto cmd = jtag.RegisterFile::read<JtagCmd>();
    auto status = jtag.RegisterFile::read<JtagStatus>();

    out << "Command: " << cmd.type << " length=" << cmd.length
        << " (pause=" << cmd.pause << ", execute=" << cmd.execute << ")\n";
    out << "Clock  : " << (status.clock_enabled? "enabled" : "disabled") << "\n";
    out << "Paused : " << std::boolalpha << status.paused << '\n';

    return out;
}

void JTag::set_bypass()
{
    RegisterFile::write<JtagSend>({0x3f});
    RegisterFile::write<JtagCmd>({Cmd::IR, 6, false, true});
    wait_until_finished();
}

void JTag::trigger(jtag::Trigger trigger_command)
{
    RegisterFile::write<JtagSend>({static_cast<uint8_t>(trigger_command)});
    RegisterFile::write<JtagCmd>({Cmd::IR, 6, false, true});
    wait_until_finished();
}

JTag::JTag(Endpoint& connection)
    : RegisterFile(connection)
{
    if (read(ID) != 0x14849434)
    {
        throw NodeHasNoHicann(connection.node);
    }
}
