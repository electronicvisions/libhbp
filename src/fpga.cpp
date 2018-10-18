#include <fpga.h>

#include <chrono>
#include <thread>
#include <array>

#include <utility/watch.h>

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

void Fpga::configure_partner_host()
{
    const static uint32_t default_timeout = 125000;
    const static uint32_t default_frequency = (1024 * 4 / 512 - 5);

    const Endpoint::Connection& rma = connection.rma;

    RMA2_Nodeid local_node = rma2_get_nodeid(rma.port);
    write_noblock<HostEndpoint>({local_node, rma.vpid, 0, 1 << 2});
    write_noblock<TraceRingbufferStart>({connection.trace_data.address()});
    write_noblock<TraceRingbufferCapacity>({connection.trace_data.byte_size(), true});
    write_noblock<ConfigResponse>({connection.gp_buffer.address() + 512});
    write_noblock<HicannRingbufferStart>({connection.hicann_config.address()});
    write_noblock<HicannRingbufferCapacity>({connection.hicann_config.byte_size(), true});
    write_noblock<TraceNotificationBehaviour>({default_timeout, default_frequency});
    write_noblock<HicannNotificationBehaviour>({default_timeout, default_frequency});

    wait_for_n_notifications(8);
}

void Fpga::send(Fpga::Config config)
{
    const Endpoint::Connection& rma = connection.rma;

    {
        WATCH_STATUS
        WATCH_ERRORS

        connection.gp_buffer.data()[0] = 0xdeadbeef;
        auto payload = static_cast<uint64_t>(config);
        rma2_post_immediate_put(rma.port, rma.handle, 8, payload, CONFIG_ADDRESS, RMA2_COMPLETER_NOTIFICATION, RMA2_CMD_DEFAULT);
        std::cout << "GP:   " << std::hex << connection.gp_buffer.data()[0] << "\n";
        wait_for_rma_notification();
    }
}

Fpga::Config operator|(Fpga::Config flags, Fpga::Config bit)
{
    return static_cast<Fpga::Config>(
        static_cast<uint64_t>(flags) | static_cast<uint64_t>(bit)
    );
}

bool operator&(Fpga::Reset flags, Fpga::Reset bit)
{
    return static_cast<uint8_t>(bit) & static_cast<uint8_t>(flags);
}
