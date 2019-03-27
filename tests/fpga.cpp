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
        return rf.read<TestControlEnable>().enable();
    }

    void type(TestControlType::Type value)
    {
        rf.write<TestControlType>({value});
    }

    void run(uint64_t dummy_value, uint8_t count, uint8_t pause, bool count_up)
    {
        rf.write<TestControlData>({dummy_value});
        rf.write<TestControlConfig>({count, pause, count_up});
        rf.write<TestControlStart>({true});
    }

    void wait()
    {
        while(rf.read<TestControlStart>().start())
        {
            usleep(1000);
        }
    }
};


TEST_CASE("Partner Host configuration terminates", "[fpga][partner-host]")
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


TEST_CASE("Partner Host configuration post condiftions hold", "[fpga][partner-host]")
{
    auto node = GENERATE(hicann_nodes());
    CAPTURE(node);

    auto rf = EX.register_file(node);
    auto fpga = EX.fpga(node);

    auto trace_counter = rf.read<TraceBufferCounter>();
    auto hicann_counter = rf.read<HicannBufferCounter>();

    fpga.configure_partner_host();

    auto& trace = EX.trace_pulse(node);
    auto trace_end = trace.address(trace.byte_size());
    CHECK(rf.read<TraceBufferStart>().data() == trace.address());
    CHECK(rf.read<TraceBufferCurrentAddress>().data() == trace.address());
    CHECK(rf.read<TraceBufferSize>().data() == trace.byte_size());
    CHECK(rf.read<TraceBufferFreeSpace>().data() == trace.capacity());
    CHECK(rf.read<TraceBufferEndAddress>().data() == trace_end);

    auto& hicann = EX.hicann_config(node);
    auto hicann_end = hicann.address(hicann.byte_size());
    CHECK(rf.read<HicannBufferStart>().data() == hicann.address());
    CHECK(rf.read<HicannBufferCurrentAddress>().data() == hicann.address());
    CHECK(rf.read<HicannBufferSize>().data()== hicann.byte_size());
    CHECK(rf.read<HicannBufferFreeSpace>().data()== hicann.capacity());
    CHECK(rf.read<HicannBufferEndAddress>().data()== hicann_end);

    auto post_trace_counter = rf.read<TraceBufferCounter>();
    auto post_hicann_counter = rf.read<HicannBufferCounter>();

    CHECK(post_trace_counter.start_address() - trace_counter.start_address() == 1);
    CHECK(post_trace_counter.size() - trace_counter.size() == 1);
    CHECK(post_trace_counter.threshold() - trace_counter.threshold() == 1);
    CHECK(post_trace_counter.wraps() == 0);

    CHECK(post_hicann_counter.start_address() - hicann_counter.start_address() == 1);
    CHECK(post_hicann_counter.size() - hicann_counter.size() == 1);
    CHECK(post_hicann_counter.threshold() - hicann_counter.threshold() == 1);
    CHECK(post_hicann_counter.wraps() == 0);
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
    uint8_t packets = 30;
    fpga.configure_partner_host();
    uint64_t undefined_host = rf.read(InvalidHost::ADDRESS);
    size_t overshot = 0;
    uint64_t sent_packets = 0;
    {
        TestModeGuard tm{rf};
        tm.type(TestControlType::HicannConfig);

        for (size_t test_run = 0; test_run < 20; ++test_run)
        {
            CAPTURE(test_run);
            REQUIRE(hicann_config.size() == 0);
            uint64_t dummy_value = 0xfff00ffffff00fff;
            --packets;
            tm.run(dummy_value, packets, 100, true);
            sent_packets += packets;
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

            auto start = rf.read<HicannBufferStart>().data();
            auto current = rf.read<HicannBufferCurrentAddress>().data();
            auto hardware_sent = (current - start) / 8;
            CHECK(hardware_sent == sent_packets);
            CHECK(rf.read<HicannBufferCounter>().wraps() == 0);
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