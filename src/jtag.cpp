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

    RegisterFile::write<JtagSend>({0});
    RegisterFile::write<JtagCmd>({Cmd::DR, 64, false, true});
    wait_until_finished();

    return RegisterFile::read(JtagReceive::ADDRESS);
}

void JTag::write(Writable write_command, uint64_t value)
{
    RegisterFile::write<JtagSend>({value});
    RegisterFile::write<JtagCmd>({Cmd::DR, 64, false, true});
    wait_until_finished();

    RegisterFile::write<JtagSend>({static_cast<uint8_t>(write_command)});
    RegisterFile::write<JtagCmd>({Cmd::IR, 6, false, true});
    wait_until_finished();
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

uint64_t JTag::read_write(jtag::ReadWrite command, uint64_t data)
{
    RegisterFile::write<JtagSend>({static_cast<uint8_t>(command)});
    RegisterFile::write<JtagCmd>({Cmd::IR, 6, false, true});
    wait_until_finished();

    RegisterFile::write(JtagSend::ADDRESS, data);
    RegisterFile::write<JtagCmd>({Cmd::DR, 64, false, true});
    wait_until_finished();

    return RegisterFile::read(JtagReceive::ADDRESS);
}

JTag::JTag(Connection& connection)
    : RegisterFile(connection)
{
    if (read(ID) != 0x14849434)
    {
        throw NodeHasNoHicann(connection.node);
    }
}
