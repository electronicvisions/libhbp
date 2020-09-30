#include "helper/util.h"

#include <extoll/fpga.h>

using extoll::library::Fpga;

TEST_CASE("Fpga Reset", "[unused][static]")
{
    CHECK((Fpga::Core & Fpga::All));
    CHECK((Fpga::Hicann & Fpga::All));
    CHECK((Fpga::PulseMem & Fpga::All));
    CHECK((Fpga::Arq & Fpga::All));
}

TEST_CASE("Fpga Config", "[unused][static]")
{
    CHECK((Fpga::Config::ClearPlaybackMemory & Fpga::Config::All));
    CHECK((Fpga::Config::ClearTraceMemory & Fpga::Config::All));
    CHECK((Fpga::Config::FpgaPulseLoopback & Fpga::Config::All));
    CHECK((Fpga::Config::GlobalModeForSystemTimeCounter & Fpga::Config::All));
    CHECK((Fpga::Config::PlaybackTimestampReplacement & Fpga::Config::All));
    CHECK((Fpga::Config::StartExperiment & Fpga::Config::All));
    CHECK((Fpga::Config::StartReadingTracedConfigPackets & Fpga::Config::All));
    CHECK((Fpga::Config::StartReadingTracedPulses & Fpga::Config::All));
    CHECK((Fpga::Config::StartSystemTimeCounter & Fpga::Config::All));
    CHECK((Fpga::Config::StartTrace & Fpga::Config::All));
    CHECK((Fpga::Config::StopTrace & Fpga::Config::All));
    CHECK((Fpga::Config::UseSstSql & Fpga::Config::All));
    CHECK((Fpga::Config::ValidSystemTimeSettings & Fpga::Config::All));
}

TEST_CASE("Fpga methods", "[unused]")
{
    auto node = GENERATE(hicann_nodes());
    auto fpga = EX.fpga(node);

    CHECK(fpga.config_response() == 0);
}

template <typename E, typename... Args>
bool do_throw(Args... args)
{
    throw E(args...);
    return false;
}

TEST_CASE("Exceptions", "[unused][static]")
{
    using namespace extoll::library;

    CHECK_THROWS(do_throw<FailedToRead>(RMA2_NODEID_ANY, RMA2_ANY_NLA));
    CHECK_THROWS(do_throw<FailedToWrite>(RMA2_NODEID_ANY, RMA2_ANY_NLA));
    CHECK_THROWS(do_throw<JtagIrShiftFailed>(RMA2_NODEID_ANY, uint8_t(0)));
}
