#include <jtag.h>

#include <register_files.h>
#include <exception.h>

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
    RegisterFile::write(JtagSend::ADDRESS, 0x3f);
    RegisterFile::write<JtagCmd>({Cmd::IR, 6, false, true});
    wait_until_finished();
}


JTag::JTag(Endpoint& connection)
    : RegisterFile(connection)
{
    if (read<ID>() != 0x14849434)
    {
        throw NodeHasNoHicann(connection.node);
    }
}
