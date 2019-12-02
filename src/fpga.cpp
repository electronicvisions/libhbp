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

PartnerHostConfiguration Fpga::default_partner_host_parameters()
{
    const auto& rma = _connection.rma;
    const auto& trace = _connection.trace_data;
    const auto& hicann = _connection.hicann_config;

    return {
        rma2_get_nodeid(rma.port),
        0,
        rma.vpid,
        1u << 2u,

        _connection.fpga_config_address(),

        {
            trace.address(),
            trace.byte_size(),
            0x7c0,
            false,

            200,
            trace.byte_size() / 512 - 8
        },

        {
            hicann.address(),
            hicann.byte_size(),
            0x7c0,
            false,

            200,
            hicann.byte_size() / 512 - 8
        },
    };
}


void Fpga::configure_partner_host(const PartnerHostConfiguration& config)
{
    using namespace extoll::library::rf;

    write_noblock<HostEndpoint>({
        config.local_node,
        config.protection_domain_id,
        config.vpid & 0x3ffu,
        config.mode & 0x3fu});
    write_noblock<ConfigResponse>({config.config_put_address});

    write_noblock<TraceBufferStart>({config.trace.start_address});
    write_noblock<TraceBufferSize>({config.trace.capacity});
    write_noblock<TraceBufferFullThreshold>({config.trace.threshold});

    write_noblock<HicannBufferStart>({config.hicann.start_address});
    write_noblock<HicannBufferSize>({config.hicann.capacity});
    write_noblock<HicannBufferFullThreshold>({config.hicann.threshold});

    write_noblock<TraceNotificationBehaviour>({config.trace.timeout, config.trace.frequency});
    write_noblock<HicannNotificationBehaviour>({config.hicann.timeout, config.hicann.frequency});

    int notifications = 12;
    if (config.trace.reset_counter)
    {
        write_noblock<TraceBufferCounterReset>({true});
        ++notifications;
    }
    if (config.hicann.reset_counter)
    {
        write_noblock<HicannBufferCounterReset>({true});
        ++notifications;
    }

    write_noblock<TraceBufferInit>({true});
    write_noblock<HicannBufferInit>({true});
    wait_for_n_notifications(notifications);

    while (RegisterFile::read<TraceBufferInit>().start()) { usleep(1000); }
    while (RegisterFile::read<HicannBufferInit>().start()) { usleep(1000); }

    _connection.hicann_config.reset();
    _connection.trace_data.reset();


}

void Fpga::configure_partner_host()
{
    configure_partner_host(default_partner_host_parameters());
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

uint64_t Fpga::config_response_no_wait() const
{
    return _connection.fpga_config_response();
}

uint64_t Fpga::config_response() const
{

    RMA2_Notification* notification;

    for (unsigned int sleep = 1; sleep < 100000; sleep *= 10)
    {
        if (rma2_noti_probe(_connection.rra.port, &notification) == RMA2_SUCCESS)
        {
            // uint64_t payload = rma2_noti_get_notiput_payload(notification);
            // uint16_t cls = rma2_noti_get_notiput_class(notification);
            rma2_noti_free(_connection.rra.port, notification);
            
            return _connection.fpga_config_response();
        }
    }

    throw std::runtime_error("fail");
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
        static_cast<uint8_t>(flags) | static_cast<uint8_t>(bit)
    );
}

bool operator&(Fpga::Reset flags, Fpga::Reset bit)
{
    return (static_cast<uint8_t>(bit) & static_cast<uint8_t>(flags)) != 0;
}

bool operator&(Fpga::Config flags, Fpga::Config bit)
{
    return (static_cast<uint64_t>(bit) & static_cast<uint64_t>(flags)) != 0;
}
