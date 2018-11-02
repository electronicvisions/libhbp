#include <tests/register_file.h>

#include <bitset>

RegisterFileTest::RegisterFileTest(Extoll& hbp, RMA2_Nodeid node)
    : TestBase(hbp), node(node) {}


void RegisterFileTest::run()
{
    auto rf = hbp.register_file(node);

    auto driver = rf.read<rf::Driver>();
    critical<uint32_t>("driver version", 0xcafebabe, driver.version);

    auto info = rf.read<rf::Info>();
    critical<uint64_t>("node id", node, info.node_id);

    rf.write<rf::JtagSend>({0xdeafcafebeefc0ce});
    auto read = rf.read<rf::JtagSend>();
    critical<uint64_t>("scratch test", read.data, 0xdeafcafebeefc0ce);
}

