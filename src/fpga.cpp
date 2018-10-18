#include <fpga.h>

#include <chrono>
#include <thread>
#include <array>

using namespace rf;

constexpr static const RMA2_NLA WATCH_STATUS_ADDRESSES[8] = {
        0x1000, 0x1008, 0x1010, 0x1018,
        0x1020, 0x1028, 0x1030, 0x1040
};
constexpr static const RMA2_NLA WATCH_ERROR_ADDRESSES[7] = {
        0x1050, 0x1058, 0x1060, 0x1068, 0x1070, 0x1078, 0x1080
};
constexpr static const char * const WATCH_STATUS_NAMES[8] {
        "RRA put commands     ", "RRA get commands     ",
        "RMA put commands     ", "RMA Noti put commands",
        "Playback data packets", "FPGA config packets  ",
        "HICANN config packets", "Pulse data packets   ",
};
constexpr static const char * const WATCH_ERROR_NAMES[7] {
        "Error: Invalid commands    ", "Error: Invalid types       ",
        "Error: Invalid payload size", "Error: Fields error        ",
        "Error: Fields mode         ", "Error: Invalid RRA         ",
        "Error: Undefined host      "
};

struct _Watch
{
    RegisterFile& rf;
    size_t registers;
    const RMA2_NLA* addresses;
    const char* const* const names;
    std::array<uint64_t, 8> before;


    _Watch(size_t registers, const RMA2_NLA* addresses, const char* const* const names, RegisterFile& rf)
        : rf(rf), registers(registers), addresses(addresses), names(names), before()
    {
        for (size_t i = 0; i < registers; ++i)
        {
            before[i] = rf.read(addresses[i]);
        }
    }

    ~_Watch()
    {
        for (size_t i = 0; i < 8; ++i)
        {
            auto now = rf.read(addresses[i]);
            if (now != before[i])
            {
                std::cout << names[i] << ": " << before[i] << "->" << now << "\n";
            }
        }
    }
};

#define WATCH_STATUS _Watch _s_(8, WATCH_STATUS_ADDRESSES, WATCH_STATUS_NAMES, *this);
#define WATCH_ERRORS _Watch _e_(7, WATCH_ERROR_ADDRESSES, WATCH_ERROR_NAMES, *this);


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

    RMA2_Nodeid local_node = rma2_get_nodeid(rma.port);
    write_noblock<HostEndpoint>({local_node, rma.vpid, 0, 1 << 2});
    write_noblock<TraceRingbufferStart>({rma.trace_data.address()});
    write_noblock<TraceRingbufferCapacity>({rma.trace_data.byte_size(), true});
    write_noblock<ConfigResponse>({rma.gp_buffer.address() + 512});
    write_noblock<HicannRingbufferStart>({rma.hicann_config.address()});
    write_noblock<HicannRingbufferCapacity>({rma.hicann_config.byte_size(), true});
    write_noblock<TraceNotificationBehaviour>({default_timeout, default_frequency});
    write_noblock<HicannNotificationBehaviour>({default_timeout, default_frequency});

    wait_for_n_notifications(8);
}

Fpga::Fpga(Endpoint& endpoint)
    : RegisterFile(endpoint.rra), rma(endpoint.rma) {}

void Fpga::send(Fpga::Config config)
{
    {
        WATCH_STATUS
        WATCH_ERRORS

        rma.gp_buffer.data()[0] = 0xdeadbeef;
        auto payload = static_cast<uint64_t>(config);
        rma2_post_immediate_put(rma.port, rma.handle, 8, payload, CONFIG_ADDRESS, RMA2_COMPLETER_NOTIFICATION, RMA2_CMD_DEFAULT);
        wait_for_rma_notification();
    }



    RMA2_ERROR status = RMA2_NO_NOTI;
    while (status == RMA2_NO_NOTI)
    {
        std::cout << "GP:   " << std::hex << rma.gp_buffer.data()[0] << "\n";
        usleep(500 * 1000);

        RMA2_Notification* notification;
        status = rma2_noti_probe(rma.port, &notification);
        rma2_noti_free(rma.port, notification);
    }
    std::cout << "DONE\n";
    std::cout << "GP:   " << std::hex << rma.gp_buffer.data()[0] << "\n";
}

void Fpga::wait_for_rma_notification()
{
    RMA2_Notification* notification;
    rma2_noti_get_block(rma.port, &notification);
    rma2_noti_free(rma.port, notification);
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
