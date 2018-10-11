#include <jtag.h>

#include <register_files.h>


uint64_t JTag::read(uint8_t read_command)
{
    RegisterFile::write<JtagSend>(read_command);
    RegisterFile::write<JtagCmd>(JtagCmdType::IR, 6, false, true);
    wait_until_finished();

    RegisterFile::write<JtagSend>(0);
    RegisterFile::write<JtagCmd>(JtagCmdType::DR, 64, false, true);
    wait_until_finished();

    return RegisterFile::read<JtagReceive>();
}

uint64_t JTag::read(jtag::Readable read_command)
{
    return JTag::read(static_cast<uint8_t>(read_command));
}

uint64_t JTag::read(jtag::ReadWrite read_command)
{
    return JTag::read(static_cast<uint8_t>(read_command));
}

void JTag::wait_until_finished() const
{
    while (RegisterFile::read<JtagCmd>().execute);
}

void JTag::reset()
{
    RegisterFile::write<JtagCmd>(JtagCmdType::Reset, 6, false, true);
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
    RegisterFile::write<JtagSend>(0x3f);
    RegisterFile::write<JtagCmd>(JtagCmdType::IR, 6, false, true);
    wait_until_finished();
}
