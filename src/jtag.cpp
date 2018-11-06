#include <extoll/jtag.h>

#include <extoll/register_files.h>
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


JTag::JTag(Endpoint& connection)
    : RegisterFile(connection)
{
    if (read<ID>() != 0x14849434)
    {
        throw NodeHasNoHicann(connection.node);
    }
}
