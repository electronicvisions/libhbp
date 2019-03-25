#ifndef LIBHBP_CPP_FPGA_H
#define LIBHBP_CPP_FPGA_H

#include <extoll/register_file.h>

namespace extoll {
namespace library {


struct PartnerHostConfiguration
{
    RMA2_Nodeid local_node;
    uint16_t protection_domain_id;
    RMA2_VPID vpid;
    uint8_t mode;

    uint64_t config_put_address;

    struct Ringbuffer
    {
        uint64_t start_address;
        uint32_t capacity;
        uint32_t threshold;
        bool reset_counter;

        uint32_t timeout;
        uint32_t frequency;
    };

    Ringbuffer trace;
    Ringbuffer hicann;
};

class Fpga : protected RegisterFile
{
    const static RMA2_NLA CONFIG_ADDRESS = 0x0c1bull << 48ull;
public:
    enum class Reset
    {
        None = 0,
        Core = 1,
        Hicann = 2,
        Arq = 4,
        PulseMem = 8,
        All = Core | Hicann | Arq | PulseMem
    };

    enum class Config : uint64_t
    {
        None = 0,
        ClearPlaybackMemory = 0x80000000,
        ClearTraceMemory = 0x40000000,
        StartExperiment = 0x20000000,
        StartTrace = 0x10000000,
        StopTrace = 0x8000000,
        StartReadingTracedPulses = 0x4000000,
        StartReadingTracedConfigPackets = 0x2000000,
        FpgaPulseLoopback = 0x1000000,
        PlaybackTimestampReplacement = 0x800000,
        ValidSystemTimeSettings = 0x400000,
        StartSystemTimeCounter = 0x200000,
        GlobalModeForSystemTimeCounter = 0x100000,
        UseSstSql = 0x80000,
        All = 0xfff80000,
    };

    using RegisterFile::RegisterFile;

    void reset(Reset = All);
    void reset_set_only(Reset = All);

    PartnerHostConfiguration default_partner_host_parameters();
    void configure_partner_host();
    void configure_partner_host(const PartnerHostConfiguration&);

    void send(Config);
    uint64_t config_response() const;

    const static Reset Core = Reset::Core;
    const static Reset Hicann = Reset::Hicann;
    const static Reset Arq = Reset::Arq;
    const static Reset All = Reset::All;
    const static Reset None = Reset::None;
};

}}

extoll::library::Fpga::Config operator|(extoll::library::Fpga::Config, extoll::library::Fpga::Config);
extoll::library::Fpga::Reset operator|(extoll::library::Fpga::Reset, extoll::library::Fpga::Reset);
bool operator&(extoll::library::Fpga::Config, extoll::library::Fpga::Config);
bool operator&(extoll::library::Fpga::Reset, extoll::library::Fpga::Reset);

#endif //LIBHBP_CPP_FPGA_H
