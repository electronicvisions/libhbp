#include <extoll/fpga.h>

#include <chrono>
#include <thread>
#include <array>
#include <cassert>
#include <bitset>

#include <extoll/utility/watch.h>


using namespace extoll::library;
using namespace rf;


void Fpga::reset(Reset resets)
{
    reset_set_only(resets);
    reset_set_only(Reset::None);
    std::this_thread::sleep_for(std::chrono::microseconds(120));
}

void Fpga::reset_set_only(Fpga::Reset resets)
{
    RegisterFile::write<::Reset>({resets & Core, resets & Hicann, resets & Arq});
}


template <typename T>
static void cmp(RegisterFile* reg, T& rf)
{
    uint64_t r = reg->read(T::ADDRESS);

    if (memcmp(&rf, &r, 8) != 0)
    {
        auto d = rf.raw;
        std::cout << std::hex << T::ADDRESS << " FAIL\n";
        std::cout << "IS  : " << std::bitset<64>(d) << "\n";
        std::cout << "MUST: " << std::bitset<64>(r) << "\n";
        std::cout << "      " << std::bitset<64>(d ^ r) << "\n\n";
    }
}

void Fpga::configure_partner_host()
{
    const static uint32_t default_timeout = 125000;
    const static uint32_t default_frequency = (1024 * 4 / 512 - 5);

    const Endpoint::Connection& rma = connection.rma;

    RMA2_Nodeid local_node = rma2_get_nodeid(rma.port);
    write_noblock<HostEndpoint>({local_node, rma.vpid, 0, 1 << 2});
    write_noblock<TraceRingbufferStart>({connection.trace_data.address()});
    write_noblock<TraceRingbufferCapacity>({connection.trace_data.byte_size(), true});
    write_noblock<ConfigResponse>({connection.fpga_config_address()});
    write_noblock<HicannRingbufferStart>({connection.hicann_config.address()});
    write_noblock<HicannRingbufferCapacity>({connection.hicann_config.byte_size(), true});
    write_noblock<TraceNotificationBehaviour>({default_timeout, default_frequency});
    write_noblock<HicannNotificationBehaviour>({default_timeout, default_frequency});

    wait_for_n_notifications(8);

    HostEndpoint he{local_node, rma.vpid, 0, 1 << 2};
    cmp(this, he);

    TraceRingbufferStart trs{connection.trace_data.address()};
    cmp(this, trs);

    auto r = read(TraceRingbufferCapacity::ADDRESS) & 0xffffffff;
    assert(r == connection.trace_data.byte_size());

    ConfigResponse cr{connection.fpga_config_address()};
    cmp(this, cr);

    HicannRingbufferStart hrs{connection.hicann_config.address()};
    cmp(this, hrs);

    r = read(HicannRingbufferCapacity::ADDRESS) & 0xffffffff;
    assert(r == connection.hicann_config.byte_size());

    TraceNotificationBehaviour tnb{default_timeout, default_frequency};
    cmp(this, tnb);

    HicannNotificationBehaviour hnb{default_timeout, default_frequency};
    cmp(this, hnb);
}

void Fpga::send(Fpga::Config config)
{
    const Endpoint::Connection& rma = connection.rma;

    {
        WATCH_STATUS
        WATCH_ERRORS

        connection.gp_buffer[0] = 0xdeadbeef;
        auto payload = static_cast<uint64_t>(config);
        rma2_post_immediate_put(rma.port, rma.handle, 8, payload, CONFIG_ADDRESS, RMA2_COMPLETER_NOTIFICATION, RMA2_CMD_DEFAULT);
        wait_for_rma_notification();
        std::cout << "GP:   " << std::hex << connection.fpga_config_response() << "\n";
    }
}

Fpga::Config operator|(Fpga::Config flags, Fpga::Config bit)
{
    return static_cast<Fpga::Config>(
        static_cast<uint64_t>(flags) | static_cast<uint64_t>(bit)
    );
}

Fpga::Reset operator|(Fpga::Reset flags, Fpga::Reset bit)
{
    return static_cast<Fpga::Reset>(
        static_cast<uint64_t>(flags) | static_cast<uint64_t>(bit)
    );
}

bool operator&(Fpga::Reset flags, Fpga::Reset bit)
{
    return static_cast<uint8_t>(bit) & static_cast<uint8_t>(flags);
}

bool operator&(Fpga::Config flags, Fpga::Config bit)
{
    return static_cast<uint8_t>(bit) & static_cast<uint8_t>(flags);
}
