#include <tests/register_file.h>

#include <bitset>


RegisterFileTest::RegisterFileTest(extoll::library::Extoll& hbp, RMA2_Nodeid node)
    : TestBase(hbp), node(node) {}


void RegisterFileTest::run()
{
    namespace rf = extoll::library::rf;
    namespace jtag = extoll::library::jtag;
    auto rra = hbp.register_file(node);

    auto driver = rra.read<rf::Driver>();
    critical<uint32_t>("driver version", 0xcafebabe, driver.version);

    auto info = rra.read<rf::Info>();
    critical<uint64_t>("node id", node, info.node_id);

    rra.write<rf::JtagSend>({0xdeafcafebeefc0ce});
    auto read = rra.read<rf::JtagSend>();
    critical<uint64_t>("scratch test", read.data, 0xdeafcafebeefc0ce);
}
