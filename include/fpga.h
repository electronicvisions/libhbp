#ifndef LIBHBP_CPP_FPGA_H
#define LIBHBP_CPP_FPGA_H

#include <register_file.h>


class Fpga : protected RegisterFile
{
public:
    enum class Reset
    {
        None = 0,
        Core = 1,
        Hicann = 2,
        Arq = 4,
        All = Core | Hicann | Arq
    };

    enum class Config : uint32_t
    {
        None = 0,
        ClearPlaybackMemory = 1 << 19,
        ClearTraceMemory = 1 << 20,
        StartExperiment = 1 << 21,
        StartTrace = 1 << 22,
        StopTrace = 1 << 23,
        StartReadingTracedPulses = 1 << 24,
        StartReadingTracedConfigPackets = 1 << 25,
        FpgaPulseLoopback = 1 << 26,
        PlaybackTimestampReplacement = 1 << 27,
        ValidSystemTimeSettings = 1 << 28,
        StartSystemTimeCounter = 1 << 29,
        GlobalModeForSystemTimeCounter = 1 << 30,
        UseSstSql = 1ul << 31ul,
        All = 0xfff80000,
    };

    using RegisterFile::RegisterFile;

    void reset(Reset = All);
    void reset_set_only(Reset = All);
    void configure_partner_host();

    void send(Config);

    const static Reset Core = Reset::Core;
    const static Reset Hicann = Reset::Hicann;
    const static Reset Arq = Reset::Arq;
    const static Reset All = Reset::All;
    const static Reset None = Reset::None;
};

bool operator&(Fpga::Reset, Fpga::Reset);


#endif //LIBHBP_CPP_FPGA_H
