#include <future>
#include <chrono>

#include <extoll/register_file.h>

#include "helper/util.h"
#include "helper/application_protocol.h"

using extoll::library::Fpga;
using namespace extoll::library::rf;
using namespace extoll::library::jtag;


struct TestModeGuard
{
    extoll::library::RegisterFile& rf;

    explicit TestModeGuard(extoll::library::RegisterFile& rf_)
        : rf(rf_)
    {
        rf.write<TestControlEnable>({true});
    }

    ~TestModeGuard()
    {
        rf.write<TestControlEnable>({false});
    }

    bool enabled()
    {
        return rf.read<TestControlEnable>().enable;
    }

    void type(TestControlType::Type value)
    {
        rf.write<TestControlType>({{{value & 0xffffu}}});
    }

    void run(uint64_t dummy_value, uint8_t count, uint8_t pause, bool count_up)
    {
        rf.write<TestControlData>({dummy_value});
        rf.write<TestControlConfig>({count, pause, count_up, true});
    }

    void wait()
    {
        while(rf.read<TestControlConfig>().start)
        {
            usleep(1000);
        }
    }
};


TEST_CASE("Partner Host configuration terminates", "[fpga]")
{
    auto node = GENERATE(hicann_nodes());
    CAPTURE(node);

    auto fpga = EX.fpga(node);

    auto future = std::async(std::launch::async, [&]() {
        fpga.configure_partner_host();
    });

    std::chrono::seconds timeout(1);
    REQUIRE(future.wait_for(timeout) == std::future_status::ready);

}

TEST_CASE("Can enable TestMode", "[al]")
{
    auto node = GENERATE(hicann_nodes());
    CAPTURE(node);

    auto rf = EX.register_file(node);

    {
        TestModeGuard tm{rf};
        CHECK(tm.enabled());
    }
}


TEST_CASE("Receives Hicann Config", "[al]")
{
    auto node = GENERATE(hicann_nodes());
    CAPTURE(node);
    auto rf = EX.register_file(node);
    auto fpga = EX.fpga(node);
    auto& hicann_config = EX.hicann_config(node);
    const size_t packets = 255;
    fpga.configure_partner_host();
    uint64_t undefined_host = rf.read(InvalidHost::ADDRESS);
    size_t overshot = 0;
    {
        TestModeGuard tm{rf};
        tm.type(TestControlType::HicannConfig);

        for (size_t test_run = 0; test_run < 100; ++test_run)
        {
            CAPTURE(test_run);
            REQUIRE(hicann_config.size() == 0);
            uint64_t dummy_value = 0xfff00ffffff00fff;
            tm.run(dummy_value, packets, 100, true);
            for (size_t packet = 0; packet < packets; ++packet)
            {
                CHECK(hicann_config.get() == dummy_value++);
            }
            tm.wait();
            try
            {
                while (true)
                {
                    hicann_config.get();
                    ++overshot;
                }
            }
            catch(...)
            {

            }
            hicann_config.notify();
        }
    }
    while (rf.probe());
    undefined_host = rf.read(InvalidHost::ADDRESS) - undefined_host;
    REQUIRE(undefined_host == 0);
    REQUIRE(overshot == 0);
}


TEST_CASE("Receives Hicann Config Jtag", "[.][al]")
{
    auto node = GENERATE(hicann_nodes());
    CAPTURE(node);
    auto jtag = EX.jtag(node);
    auto rf = EX.register_file(node);
    auto& hicann_config = EX.hicann_config(node);
    auto hicann = EX.hicann(node, 0);

    jtag.write<ArqControl>(2u | (2u << 16u), 0);
    auto received = rf.read(HicannConfigReceived::ADDRESS);
    hicann.send(0xcafe);

    CHECK(hicann_config.get() == 0xcafe);
    CHECK(rf.read(HicannConfigReceived::ADDRESS) == (received + 1));
}