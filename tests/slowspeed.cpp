#include "helper/util.h"

using namespace extoll::library;


class SlowspeedGuard
{
    Fpga& fpga;
    JTag& jtag;
    uint8_t hicann;

public:
    SlowspeedGuard(Fpga& f, JTag& j, uint8_t h)
        : fpga(f), jtag(j), hicann(h)
    {
        using namespace jtag;

        fpga.reset_set_only(Fpga::Arq);

        jtag.write<SystemEnable>(0, hicann);
        jtag.write<ArqRxTimeoutValue>(0xa000a, hicann);
        jtag.write<ArqTxTimeoutValue>(0xc800c8, hicann);
        jtag.write<ArqControl>(0x10001, hicann);
        jtag.write<ArqControl>(0, hicann);
    }

    void send(uint64_t command)
    {
        using namespace jtag;

        jtag.write<TestControl>(0xc, hicann);
        jtag.write<TxData>(command, hicann);
        jtag.trigger<StartConfigPackage>(hicann);
        jtag.write<TestControl>(0, hicann);
    }

    uint64_t receive()
    {
        using namespace jtag;

        return jtag.read<RxData>(hicann);
    }

    ~SlowspeedGuard()
    {
        using namespace jtag;

        fpga.reset_set_only(Fpga::None);

        jtag.write<SystemEnable>(1, hicann);
    }
};



TEST_CASE("Fpga survives slowspeed init", "[ss]")
{
    auto node = GENERATE(hicann_nodes());
    CAPTURE(node);
    auto fpga = EX.fpga(node);
    auto j = EX.jtag(node);

    FOR_EACH_HICANN {
        SlowspeedGuard guard(fpga, j, hicann);

        uint32_t address = 1;

        uint64_t write = 0;
        write |= 0xcafeu;
        write |= uint64_t(address) << 32u;
        write |= 1ul << 48u;
        guard.send(write);

        uint64_t read = 0;
        read |= uint64_t(address);
        guard.send(read);

        auto returned = guard.receive();
        std::cout << "HICANN " << int16_t(hicann) << " " << std::hex << returned << "\n";
    }

    auto rf = EX.register_file(node);
    REQUIRE(rf.read<rf::Driver>().version() == 0xcafebabe);
}

