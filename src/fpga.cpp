#include <extoll/fpga.h>

#include <iostream>
#include <chrono>
#include <thread>
#include <array>
#include <cassert>
#include <bitset>


using namespace extoll::library;
using namespace rf;


void Fpga::reset(Reset resets)
{
    reset_set_only(resets);
    reset_set_only(Reset::None);
    std::this_thread::sleep_for(std::chrono::microseconds(120));
}

void Fpga::reset_set_only(Reset resets)
{
    RegisterFile::write(rf::Reset::ADDRESS, static_cast<uint64_t>(resets));
}


template <typename T>
static void cmp(RegisterFile* reg, T& rf)
{
    uint64_t r = reg->read(T::ADDRESS);

    if (r != rf.raw)
    {
        auto d = rf.raw;
        std::cout << std::hex << T::ADDRESS << " FAIL\n";
        std::cout << "IS  : " << std::bitset<64>(d) << "\n";
        std::cout << "MUST: " << std::bitset<64>(r) << "\n";
        std::cout << "DIFF: " << std::bitset<64>(d ^ r) << "\n\n";
    }
}

void Fpga::configure_partner_host()
{
    const uint32_t default_timeout = 200;
    const uint32_t default_frequency =
            (_connection.hicann_config.byte_size() / 512 - 8);

    const Endpoint::Connection& rma = _connection.rma;

    auto trace_counter = read<TraceBufferCounter>();
    auto hicann_counter = read<HicannBufferCounter>();

    RMA2_Nodeid local_node = rma2_get_nodeid(rma.port);
    write_noblock<HostEndpoint>({{{local_node, 0, rma.vpid & 0x3ffu, 1 << 2}}});
    write_noblock<ConfigResponse>({{{_connection.fpga_config_address()}}});

    write_noblock<TraceBufferStart>({{{_connection.trace_data.address()}}});
    write_noblock<TraceBufferSize>({{{_connection.trace_data.byte_size()}}});

    write_noblock<HicannBufferStart>({{{_connection.hicann_config.address()}}});
    write_noblock<HicannBufferSize>({{{_connection.hicann_config.byte_size()}}});

    write_noblock<TraceNotificationBehaviour>({{{default_timeout, default_frequency}}});
    write_noblock<HicannNotificationBehaviour>({{{default_timeout, default_frequency}}});

    write_noblock<TraceBufferInit>({{{true}}});
    write_noblock<HicannBufferInit>({{{true}}});
    wait_for_n_notifications(10);

    // poll Ringbuffer Address changes
    while (RegisterFile::read<TraceBufferInit>().start) {{{ usleep(1000); }}}
    while (RegisterFile::read<HicannBufferInit>().start) {{{ usleep(1000); }}}

    HostEndpoint he{{{local_node, 0, rma.vpid & 0x3ffu, 1 << 2}}};
    cmp(this, he);

    TraceBufferStart trs{{{_connection.trace_data.address()}}};
    cmp(this, trs);

    auto r = read(TraceBufferSize::ADDRESS) & 0xffffffff;
    assert(r == _connection.trace_data.byte_size());

    ConfigResponse cr{{{_connection.fpga_config_address()}}};
    cmp(this, cr);

    HicannBufferStart hrs{{{_connection.hicann_config.address()}}};
    cmp(this, hrs);

    r = read(HicannBufferSize::ADDRESS) & 0xffffffff;
    assert(r == _connection.hicann_config.byte_size());

    TraceNotificationBehaviour tnb{{{default_timeout, default_frequency}}};
    cmp(this, tnb);

    HicannNotificationBehaviour hnb{{{default_timeout, default_frequency}}};
    cmp(this, hnb);

    auto end_address = _connection.trace_data.address(_connection.trace_data.byte_size());
    assert(read(TraceBufferEndAddress::ADDRESS) == end_address);

    end_address = _connection.hicann_config.address(_connection.hicann_config.byte_size());
    assert(read(HicannBufferEndAddress::ADDRESS) == end_address);

    assert(read(TraceBufferCurrentAddress::ADDRESS) == _connection.trace_data.address());
    assert(read(HicannBufferCurrentAddress::ADDRESS) == _connection.hicann_config.address());
    assert(read(TraceBufferFreeSpace::ADDRESS)*8 == _connection.trace_data.byte_size());
    assert(read(HicannBufferFreeSpace::ADDRESS)*8 == _connection.hicann_config.byte_size());

    auto post_trace_counter = read<TraceBufferCounter>();
    auto post_hicann_counter = read<HicannBufferCounter>();
    assert(post_trace_counter.wraps == 0);
    assert(post_hicann_counter.wraps == 0);
    assert((trace_counter.size + 1) == post_trace_counter.size);
    assert((hicann_counter.size + 1) == post_hicann_counter.size);
    assert((trace_counter.start_address + 1) == post_trace_counter.start_address);
    assert((hicann_counter.start_address + 1) == post_hicann_counter.start_address);
}

void Fpga::send(Fpga::Config config)
{
    const Endpoint::Connection& rma = _connection.rma;

    _connection.gp_buffer[512] = 0xdeadbeef;
    auto payload = static_cast<uint64_t>(config);
    rma2_post_immediate_put(rma.port, rma.handle, 8, payload, CONFIG_ADDRESS, RMA2_COMPLETER_NOTIFICATION, RMA2_CMD_DEFAULT);
    wait_for_rma_notification();
    usleep(100000);
    std::cout << "GP:   " << std::hex << _connection.fpga_config_response() << "\n";
}

uint64_t Fpga::config_response() const
{
    return _connection.fpga_config_response();
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
