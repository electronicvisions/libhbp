/**
 * This is a generated file - do not change it
 * 2019-03-22 18:08:08.864341
 */

#pragma once

#include <cinttypes>

#include <extoll/rma.h>


namespace extoll {
namespace library {
namespace rf {

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"


struct Reset
{
    union
    {
        struct
        {
            
            bool core : 1;
            bool hicann : 1;
            bool arq : 1;
            bool pulse_mem : 1;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x0;
    const static bool READABLE = true;
    const static bool WRITABLE = true;
};

static_assert(sizeof(Reset) == sizeof(uint64_t), "sizeof register file 'Reset' != sizeof uint64_t");
static_assert(std::is_trivial<Reset>::value, "'Reset' is not trivial");

struct JtagCmd
{
    union
    {
        struct
        {
            
            uint64_t type : 3;
            uint64_t length : 10;
            bool pause : 1;
            bool execute : 1;
        };
        uint64_t raw;
    };


    enum Type
    {
    
        Reset = 0,
        IR = 1,
        DR = 2,
        EnableClock = 4,
        DisableClock = 5,
    };

    const static RMA2_NLA ADDRESS = 0x400;
    const static bool READABLE = true;
    const static bool WRITABLE = true;
};

static_assert(sizeof(JtagCmd) == sizeof(uint64_t), "sizeof register file 'JtagCmd' != sizeof uint64_t");
static_assert(std::is_trivial<JtagCmd>::value, "'JtagCmd' is not trivial");

struct JtagStatus
{
    union
    {
        struct
        {
            
            bool clock_enabled : 1;
            bool paused : 1;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x408;
    const static bool READABLE = true;
    const static bool WRITABLE = false;
};

static_assert(sizeof(JtagStatus) == sizeof(uint64_t), "sizeof register file 'JtagStatus' != sizeof uint64_t");
static_assert(std::is_trivial<JtagStatus>::value, "'JtagStatus' is not trivial");

struct JtagSend
{
    union
    {
        struct
        {
            
            uint64_t data : 64;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x480;
    const static bool READABLE = true;
    const static bool WRITABLE = true;
};

static_assert(sizeof(JtagSend) == sizeof(uint64_t), "sizeof register file 'JtagSend' != sizeof uint64_t");
static_assert(std::is_trivial<JtagSend>::value, "'JtagSend' is not trivial");

struct JtagReceive
{
    union
    {
        struct
        {
            
            uint64_t data : 64;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x500;
    const static bool READABLE = true;
    const static bool WRITABLE = false;
};

static_assert(sizeof(JtagReceive) == sizeof(uint64_t), "sizeof register file 'JtagReceive' != sizeof uint64_t");
static_assert(std::is_trivial<JtagReceive>::value, "'JtagReceive' is not trivial");

struct HicannIfState
{
    union
    {
        struct
        {
            
            uint64_t channel_status : 8;
            uint64_t crc_count : 8;
            uint64_t systime : 14;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x800;
    const static bool READABLE = true;
    const static bool WRITABLE = false;
};

static_assert(sizeof(HicannIfState) == sizeof(uint64_t), "sizeof register file 'HicannIfState' != sizeof uint64_t");
static_assert(std::is_trivial<HicannIfState>::value, "'HicannIfState' is not trivial");

struct HicannIfRxConfig
{
    union
    {
        struct
        {
            
            uint64_t data : 64;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x808;
    const static bool READABLE = true;
    const static bool WRITABLE = false;
};

static_assert(sizeof(HicannIfRxConfig) == sizeof(uint64_t), "sizeof register file 'HicannIfRxConfig' != sizeof uint64_t");
static_assert(std::is_trivial<HicannIfRxConfig>::value, "'HicannIfRxConfig' is not trivial");

struct HicannIfRxPulse
{
    union
    {
        struct
        {
            
            uint64_t data : 24;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x810;
    const static bool READABLE = true;
    const static bool WRITABLE = false;
};

static_assert(sizeof(HicannIfRxPulse) == sizeof(uint64_t), "sizeof register file 'HicannIfRxPulse' != sizeof uint64_t");
static_assert(std::is_trivial<HicannIfRxPulse>::value, "'HicannIfRxPulse' is not trivial");

struct HicannIfConfig
{
    union
    {
        struct
        {
            
            bool start_link : 1;
            bool loopback_enable : 1;
            bool auto_init : 1;
            bool init_master : 1;
            bool use_timestamp : 1;
            bool auto_limit : 1;
            bool pulse_protocol : 1;
            bool config_protocol : 1;
            uint64_t heap_mode : 8;
            uint64_t limit : 11;
            bool dc_coding : 1;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x818;
    const static bool READABLE = true;
    const static bool WRITABLE = true;
};

static_assert(sizeof(HicannIfConfig) == sizeof(uint64_t), "sizeof register file 'HicannIfConfig' != sizeof uint64_t");
static_assert(std::is_trivial<HicannIfConfig>::value, "'HicannIfConfig' is not trivial");

struct HicannIfControls
{
    union
    {
        struct
        {
            
            bool tx_hicann_pulse_enable : 1;
            bool tx_hicann_config_enable : 1;
            bool routing_data_enable : 1;
            bool channel_reset : 1;
            bool crc_count_reset : 1;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x820;
    const static bool READABLE = false;
    const static bool WRITABLE = true;
};

static_assert(sizeof(HicannIfControls) == sizeof(uint64_t), "sizeof register file 'HicannIfControls' != sizeof uint64_t");
static_assert(std::is_trivial<HicannIfControls>::value, "'HicannIfControls' is not trivial");

struct HicannIfTxData
{
    union
    {
        struct
        {
            
            uint64_t data : 64;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x828;
    const static bool READABLE = true;
    const static bool WRITABLE = true;
};

static_assert(sizeof(HicannIfTxData) == sizeof(uint64_t), "sizeof register file 'HicannIfTxData' != sizeof uint64_t");
static_assert(std::is_trivial<HicannIfTxData>::value, "'HicannIfTxData' is not trivial");

struct HicannPacketGen
{
    union
    {
        struct
        {
            
            uint64_t count : 25;
            bool error : 1;
            bool enable : 1;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x830;
    const static bool READABLE = true;
    const static bool WRITABLE = true;
};

static_assert(sizeof(HicannPacketGen) == sizeof(uint64_t), "sizeof register file 'HicannPacketGen' != sizeof uint64_t");
static_assert(std::is_trivial<HicannPacketGen>::value, "'HicannPacketGen' is not trivial");

struct HicannChannel
{
    union
    {
        struct
        {
            
            uint64_t number : 3;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x838;
    const static bool READABLE = true;
    const static bool WRITABLE = true;
};

static_assert(sizeof(HicannChannel) == sizeof(uint64_t), "sizeof register file 'HicannChannel' != sizeof uint64_t");
static_assert(std::is_trivial<HicannChannel>::value, "'HicannChannel' is not trivial");

struct ArqTimings
{
    union
    {
        struct
        {
            
            uint64_t master_timeout : 10;
            uint64_t target_timeout : 10;
            uint64_t arbiter_delay : 5;
            bool bit : 1;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x840;
    const static bool READABLE = true;
    const static bool WRITABLE = true;
};

static_assert(sizeof(ArqTimings) == sizeof(uint64_t), "sizeof register file 'ArqTimings' != sizeof uint64_t");
static_assert(std::is_trivial<ArqTimings>::value, "'ArqTimings' is not trivial");

struct TestControlEnable
{
    union
    {
        struct
        {
            
            bool enable : 1;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0xc00;
    const static bool READABLE = true;
    const static bool WRITABLE = true;
};

static_assert(sizeof(TestControlEnable) == sizeof(uint64_t), "sizeof register file 'TestControlEnable' != sizeof uint64_t");
static_assert(std::is_trivial<TestControlEnable>::value, "'TestControlEnable' is not trivial");

struct TestControlConfig
{
    union
    {
        struct
        {
            
            uint64_t quad_words : 8;
            uint64_t pause_time : 8;
            bool count_up : 1;
            bool start : 1;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0xc08;
    const static bool READABLE = true;
    const static bool WRITABLE = true;
};

static_assert(sizeof(TestControlConfig) == sizeof(uint64_t), "sizeof register file 'TestControlConfig' != sizeof uint64_t");
static_assert(std::is_trivial<TestControlConfig>::value, "'TestControlConfig' is not trivial");

struct TestControlData
{
    union
    {
        struct
        {
            
            uint64_t data : 64;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0xc10;
    const static bool READABLE = true;
    const static bool WRITABLE = true;
};

static_assert(sizeof(TestControlData) == sizeof(uint64_t), "sizeof register file 'TestControlData' != sizeof uint64_t");
static_assert(std::is_trivial<TestControlData>::value, "'TestControlData' is not trivial");

struct TestControlType
{
    union
    {
        struct
        {
            
            uint64_t type : 16;
        };
        uint64_t raw;
    };


    enum Type : uint16_t
    {
    
        TracePulse = 3237,
        FpgaConfig = 3099,
        HicannConfig = 10779,
    };

    const static RMA2_NLA ADDRESS = 0xc18;
    const static bool READABLE = true;
    const static bool WRITABLE = true;
};

static_assert(sizeof(TestControlType) == sizeof(uint64_t), "sizeof register file 'TestControlType' != sizeof uint64_t");
static_assert(std::is_trivial<TestControlType>::value, "'TestControlType' is not trivial");

struct TraceBufferStart
{
    union
    {
        struct
        {
            
            uint64_t data : 64;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x1000;
    const static bool READABLE = true;
    const static bool WRITABLE = true;
};

static_assert(sizeof(TraceBufferStart) == sizeof(uint64_t), "sizeof register file 'TraceBufferStart' != sizeof uint64_t");
static_assert(std::is_trivial<TraceBufferStart>::value, "'TraceBufferStart' is not trivial");

struct TraceBufferSize
{
    union
    {
        struct
        {
            
            uint64_t data : 32;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x1008;
    const static bool READABLE = true;
    const static bool WRITABLE = true;
};

static_assert(sizeof(TraceBufferSize) == sizeof(uint64_t), "sizeof register file 'TraceBufferSize' != sizeof uint64_t");
static_assert(std::is_trivial<TraceBufferSize>::value, "'TraceBufferSize' is not trivial");

struct TraceBufferFullThreshold
{
    union
    {
        struct
        {
            
            uint64_t data : 32;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x1010;
    const static bool READABLE = true;
    const static bool WRITABLE = true;
};

static_assert(sizeof(TraceBufferFullThreshold) == sizeof(uint64_t), "sizeof register file 'TraceBufferFullThreshold' != sizeof uint64_t");
static_assert(std::is_trivial<TraceBufferFullThreshold>::value, "'TraceBufferFullThreshold' is not trivial");

struct TraceBufferCounter
{
    union
    {
        struct
        {
            
            uint64_t start_address : 16;
            uint64_t size : 16;
            uint64_t threshold : 16;
            uint64_t wraps : 16;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x1018;
    const static bool READABLE = true;
    const static bool WRITABLE = false;
};

static_assert(sizeof(TraceBufferCounter) == sizeof(uint64_t), "sizeof register file 'TraceBufferCounter' != sizeof uint64_t");
static_assert(std::is_trivial<TraceBufferCounter>::value, "'TraceBufferCounter' is not trivial");

struct TraceBufferCounterReset
{
    union
    {
        struct
        {
            
            bool reset : 1;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x1020;
    const static bool READABLE = false;
    const static bool WRITABLE = true;
};

static_assert(sizeof(TraceBufferCounterReset) == sizeof(uint64_t), "sizeof register file 'TraceBufferCounterReset' != sizeof uint64_t");
static_assert(std::is_trivial<TraceBufferCounterReset>::value, "'TraceBufferCounterReset' is not trivial");

struct TraceBufferCurrentAddress
{
    union
    {
        struct
        {
            
            uint64_t data : 64;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x1028;
    const static bool READABLE = true;
    const static bool WRITABLE = false;
};

static_assert(sizeof(TraceBufferCurrentAddress) == sizeof(uint64_t), "sizeof register file 'TraceBufferCurrentAddress' != sizeof uint64_t");
static_assert(std::is_trivial<TraceBufferCurrentAddress>::value, "'TraceBufferCurrentAddress' is not trivial");

struct TraceBufferEndAddress
{
    union
    {
        struct
        {
            
            uint64_t data : 64;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x1030;
    const static bool READABLE = true;
    const static bool WRITABLE = false;
};

static_assert(sizeof(TraceBufferEndAddress) == sizeof(uint64_t), "sizeof register file 'TraceBufferEndAddress' != sizeof uint64_t");
static_assert(std::is_trivial<TraceBufferEndAddress>::value, "'TraceBufferEndAddress' is not trivial");

struct TraceBufferFreeSpace
{
    union
    {
        struct
        {
            
            uint64_t data : 32;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x1038;
    const static bool READABLE = true;
    const static bool WRITABLE = false;
};

static_assert(sizeof(TraceBufferFreeSpace) == sizeof(uint64_t), "sizeof register file 'TraceBufferFreeSpace' != sizeof uint64_t");
static_assert(std::is_trivial<TraceBufferFreeSpace>::value, "'TraceBufferFreeSpace' is not trivial");

struct TraceBufferInit
{
    union
    {
        struct
        {
            
            bool start : 1;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x1040;
    const static bool READABLE = true;
    const static bool WRITABLE = true;
};

static_assert(sizeof(TraceBufferInit) == sizeof(uint64_t), "sizeof register file 'TraceBufferInit' != sizeof uint64_t");
static_assert(std::is_trivial<TraceBufferInit>::value, "'TraceBufferInit' is not trivial");

struct HicannBufferStart
{
    union
    {
        struct
        {
            
            uint64_t data : 64;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x1080;
    const static bool READABLE = true;
    const static bool WRITABLE = true;
};

static_assert(sizeof(HicannBufferStart) == sizeof(uint64_t), "sizeof register file 'HicannBufferStart' != sizeof uint64_t");
static_assert(std::is_trivial<HicannBufferStart>::value, "'HicannBufferStart' is not trivial");

struct HicannBufferSize
{
    union
    {
        struct
        {
            
            uint64_t data : 32;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x1088;
    const static bool READABLE = true;
    const static bool WRITABLE = true;
};

static_assert(sizeof(HicannBufferSize) == sizeof(uint64_t), "sizeof register file 'HicannBufferSize' != sizeof uint64_t");
static_assert(std::is_trivial<HicannBufferSize>::value, "'HicannBufferSize' is not trivial");

struct HicannBufferFullThreshold
{
    union
    {
        struct
        {
            
            uint64_t data : 32;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x1090;
    const static bool READABLE = true;
    const static bool WRITABLE = true;
};

static_assert(sizeof(HicannBufferFullThreshold) == sizeof(uint64_t), "sizeof register file 'HicannBufferFullThreshold' != sizeof uint64_t");
static_assert(std::is_trivial<HicannBufferFullThreshold>::value, "'HicannBufferFullThreshold' is not trivial");

struct HicannBufferCounter
{
    union
    {
        struct
        {
            
            uint64_t start_address : 16;
            uint64_t size : 16;
            uint64_t threshold : 16;
            uint64_t wraps : 16;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x1098;
    const static bool READABLE = true;
    const static bool WRITABLE = false;
};

static_assert(sizeof(HicannBufferCounter) == sizeof(uint64_t), "sizeof register file 'HicannBufferCounter' != sizeof uint64_t");
static_assert(std::is_trivial<HicannBufferCounter>::value, "'HicannBufferCounter' is not trivial");

struct HicannBufferCounterReset
{
    union
    {
        struct
        {
            
            bool reset : 1;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x10a0;
    const static bool READABLE = false;
    const static bool WRITABLE = true;
};

static_assert(sizeof(HicannBufferCounterReset) == sizeof(uint64_t), "sizeof register file 'HicannBufferCounterReset' != sizeof uint64_t");
static_assert(std::is_trivial<HicannBufferCounterReset>::value, "'HicannBufferCounterReset' is not trivial");

struct HicannBufferCurrentAddress
{
    union
    {
        struct
        {
            
            uint64_t data : 64;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x10a8;
    const static bool READABLE = true;
    const static bool WRITABLE = false;
};

static_assert(sizeof(HicannBufferCurrentAddress) == sizeof(uint64_t), "sizeof register file 'HicannBufferCurrentAddress' != sizeof uint64_t");
static_assert(std::is_trivial<HicannBufferCurrentAddress>::value, "'HicannBufferCurrentAddress' is not trivial");

struct HicannBufferEndAddress
{
    union
    {
        struct
        {
            
            uint64_t data : 64;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x10b0;
    const static bool READABLE = true;
    const static bool WRITABLE = false;
};

static_assert(sizeof(HicannBufferEndAddress) == sizeof(uint64_t), "sizeof register file 'HicannBufferEndAddress' != sizeof uint64_t");
static_assert(std::is_trivial<HicannBufferEndAddress>::value, "'HicannBufferEndAddress' is not trivial");

struct HicannBufferFreeSpace
{
    union
    {
        struct
        {
            
            uint64_t data : 32;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x10b8;
    const static bool READABLE = true;
    const static bool WRITABLE = false;
};

static_assert(sizeof(HicannBufferFreeSpace) == sizeof(uint64_t), "sizeof register file 'HicannBufferFreeSpace' != sizeof uint64_t");
static_assert(std::is_trivial<HicannBufferFreeSpace>::value, "'HicannBufferFreeSpace' is not trivial");

struct HicannBufferInit
{
    union
    {
        struct
        {
            
            bool start : 1;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x10c0;
    const static bool READABLE = true;
    const static bool WRITABLE = true;
};

static_assert(sizeof(HicannBufferInit) == sizeof(uint64_t), "sizeof register file 'HicannBufferInit' != sizeof uint64_t");
static_assert(std::is_trivial<HicannBufferInit>::value, "'HicannBufferInit' is not trivial");

struct RraPutReceived
{
    union
    {
        struct
        {
            
            uint64_t count : 48;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x1100;
    const static bool READABLE = true;
    const static bool WRITABLE = false;
};

static_assert(sizeof(RraPutReceived) == sizeof(uint64_t), "sizeof register file 'RraPutReceived' != sizeof uint64_t");
static_assert(std::is_trivial<RraPutReceived>::value, "'RraPutReceived' is not trivial");

struct RraGetReceived
{
    union
    {
        struct
        {
            
            uint64_t count : 48;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x1108;
    const static bool READABLE = true;
    const static bool WRITABLE = false;
};

static_assert(sizeof(RraGetReceived) == sizeof(uint64_t), "sizeof register file 'RraGetReceived' != sizeof uint64_t");
static_assert(std::is_trivial<RraGetReceived>::value, "'RraGetReceived' is not trivial");

struct RmaPutReceived
{
    union
    {
        struct
        {
            
            uint64_t count : 48;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x1110;
    const static bool READABLE = true;
    const static bool WRITABLE = false;
};

static_assert(sizeof(RmaPutReceived) == sizeof(uint64_t), "sizeof register file 'RmaPutReceived' != sizeof uint64_t");
static_assert(std::is_trivial<RmaPutReceived>::value, "'RmaPutReceived' is not trivial");

struct RmaNotificationReceived
{
    union
    {
        struct
        {
            
            uint64_t count : 48;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x1118;
    const static bool READABLE = true;
    const static bool WRITABLE = false;
};

static_assert(sizeof(RmaNotificationReceived) == sizeof(uint64_t), "sizeof register file 'RmaNotificationReceived' != sizeof uint64_t");
static_assert(std::is_trivial<RmaNotificationReceived>::value, "'RmaNotificationReceived' is not trivial");

struct PlaybackReceived
{
    union
    {
        struct
        {
            
            uint64_t count : 48;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x1120;
    const static bool READABLE = true;
    const static bool WRITABLE = false;
};

static_assert(sizeof(PlaybackReceived) == sizeof(uint64_t), "sizeof register file 'PlaybackReceived' != sizeof uint64_t");
static_assert(std::is_trivial<PlaybackReceived>::value, "'PlaybackReceived' is not trivial");

struct FpgaConfigReceived
{
    union
    {
        struct
        {
            
            uint64_t count : 48;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x1128;
    const static bool READABLE = true;
    const static bool WRITABLE = false;
};

static_assert(sizeof(FpgaConfigReceived) == sizeof(uint64_t), "sizeof register file 'FpgaConfigReceived' != sizeof uint64_t");
static_assert(std::is_trivial<FpgaConfigReceived>::value, "'FpgaConfigReceived' is not trivial");

struct HicannConfigReceived
{
    union
    {
        struct
        {
            
            uint64_t count : 48;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x1130;
    const static bool READABLE = true;
    const static bool WRITABLE = false;
};

static_assert(sizeof(HicannConfigReceived) == sizeof(uint64_t), "sizeof register file 'HicannConfigReceived' != sizeof uint64_t");
static_assert(std::is_trivial<HicannConfigReceived>::value, "'HicannConfigReceived' is not trivial");

struct JtagDataReceived
{
    union
    {
        struct
        {
            
            uint64_t count : 48;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x1138;
    const static bool READABLE = true;
    const static bool WRITABLE = false;
};

static_assert(sizeof(JtagDataReceived) == sizeof(uint64_t), "sizeof register file 'JtagDataReceived' != sizeof uint64_t");
static_assert(std::is_trivial<JtagDataReceived>::value, "'JtagDataReceived' is not trivial");

struct NeighbourDataReceived
{
    union
    {
        struct
        {
            
            uint64_t count : 48;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x1140;
    const static bool READABLE = true;
    const static bool WRITABLE = false;
};

static_assert(sizeof(NeighbourDataReceived) == sizeof(uint64_t), "sizeof register file 'NeighbourDataReceived' != sizeof uint64_t");
static_assert(std::is_trivial<NeighbourDataReceived>::value, "'NeighbourDataReceived' is not trivial");

struct CounterReset
{
    union
    {
        struct
        {
            
            bool reset : 1;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x1148;
    const static bool READABLE = false;
    const static bool WRITABLE = true;
};

static_assert(sizeof(CounterReset) == sizeof(uint64_t), "sizeof register file 'CounterReset' != sizeof uint64_t");
static_assert(std::is_trivial<CounterReset>::value, "'CounterReset' is not trivial");

struct InvalidCommand
{
    union
    {
        struct
        {
            
            uint64_t count : 48;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x1150;
    const static bool READABLE = true;
    const static bool WRITABLE = false;
};

static_assert(sizeof(InvalidCommand) == sizeof(uint64_t), "sizeof register file 'InvalidCommand' != sizeof uint64_t");
static_assert(std::is_trivial<InvalidCommand>::value, "'InvalidCommand' is not trivial");

struct InvalidType
{
    union
    {
        struct
        {
            
            uint64_t count : 48;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x1158;
    const static bool READABLE = true;
    const static bool WRITABLE = false;
};

static_assert(sizeof(InvalidType) == sizeof(uint64_t), "sizeof register file 'InvalidType' != sizeof uint64_t");
static_assert(std::is_trivial<InvalidType>::value, "'InvalidType' is not trivial");

struct InvalidPayloadSize
{
    union
    {
        struct
        {
            
            uint64_t count : 48;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x1160;
    const static bool READABLE = true;
    const static bool WRITABLE = false;
};

static_assert(sizeof(InvalidPayloadSize) == sizeof(uint64_t), "sizeof register file 'InvalidPayloadSize' != sizeof uint64_t");
static_assert(std::is_trivial<InvalidPayloadSize>::value, "'InvalidPayloadSize' is not trivial");

struct InvalidFields
{
    union
    {
        struct
        {
            
            uint64_t count : 48;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x1168;
    const static bool READABLE = true;
    const static bool WRITABLE = false;
};

static_assert(sizeof(InvalidFields) == sizeof(uint64_t), "sizeof register file 'InvalidFields' != sizeof uint64_t");
static_assert(std::is_trivial<InvalidFields>::value, "'InvalidFields' is not trivial");

struct InvalidMode
{
    union
    {
        struct
        {
            
            uint64_t count : 48;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x1170;
    const static bool READABLE = true;
    const static bool WRITABLE = false;
};

static_assert(sizeof(InvalidMode) == sizeof(uint64_t), "sizeof register file 'InvalidMode' != sizeof uint64_t");
static_assert(std::is_trivial<InvalidMode>::value, "'InvalidMode' is not trivial");

struct InvalidRraAddress
{
    union
    {
        struct
        {
            
            uint64_t count : 48;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x1178;
    const static bool READABLE = true;
    const static bool WRITABLE = false;
};

static_assert(sizeof(InvalidRraAddress) == sizeof(uint64_t), "sizeof register file 'InvalidRraAddress' != sizeof uint64_t");
static_assert(std::is_trivial<InvalidRraAddress>::value, "'InvalidRraAddress' is not trivial");

struct InvalidHost
{
    union
    {
        struct
        {
            
            uint64_t count : 48;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x1180;
    const static bool READABLE = true;
    const static bool WRITABLE = false;
};

static_assert(sizeof(InvalidHost) == sizeof(uint64_t), "sizeof register file 'InvalidHost' != sizeof uint64_t");
static_assert(std::is_trivial<InvalidHost>::value, "'InvalidHost' is not trivial");

struct ConfigAddressReinit
{
    union
    {
        struct
        {
            
            uint64_t count : 48;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x1188;
    const static bool READABLE = true;
    const static bool WRITABLE = false;
};

static_assert(sizeof(ConfigAddressReinit) == sizeof(uint64_t), "sizeof register file 'ConfigAddressReinit' != sizeof uint64_t");
static_assert(std::is_trivial<ConfigAddressReinit>::value, "'ConfigAddressReinit' is not trivial");

struct HostEndpoint
{
    union
    {
        struct
        {
            
            uint64_t node_id : 16;
            uint64_t protection_domain : 16;
            uint64_t vpid : 10;
            uint64_t mode : 6;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x1190;
    const static bool READABLE = true;
    const static bool WRITABLE = true;
};

static_assert(sizeof(HostEndpoint) == sizeof(uint64_t), "sizeof register file 'HostEndpoint' != sizeof uint64_t");
static_assert(std::is_trivial<HostEndpoint>::value, "'HostEndpoint' is not trivial");

struct ConfigResponse
{
    union
    {
        struct
        {
            
            uint64_t address : 64;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x1198;
    const static bool READABLE = true;
    const static bool WRITABLE = true;
};

static_assert(sizeof(ConfigResponse) == sizeof(uint64_t), "sizeof register file 'ConfigResponse' != sizeof uint64_t");
static_assert(std::is_trivial<ConfigResponse>::value, "'ConfigResponse' is not trivial");

struct TraceNotificationBehaviour
{
    union
    {
        struct
        {
            
            uint64_t timeout : 32;
            uint64_t frequency : 32;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x11a0;
    const static bool READABLE = true;
    const static bool WRITABLE = true;
};

static_assert(sizeof(TraceNotificationBehaviour) == sizeof(uint64_t), "sizeof register file 'TraceNotificationBehaviour' != sizeof uint64_t");
static_assert(std::is_trivial<TraceNotificationBehaviour>::value, "'TraceNotificationBehaviour' is not trivial");

struct HicannNotificationBehaviour
{
    union
    {
        struct
        {
            
            uint64_t timeout : 32;
            uint64_t frequency : 32;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x11a8;
    const static bool READABLE = true;
    const static bool WRITABLE = true;
};

static_assert(sizeof(HicannNotificationBehaviour) == sizeof(uint64_t), "sizeof register file 'HicannNotificationBehaviour' != sizeof uint64_t");
static_assert(std::is_trivial<HicannNotificationBehaviour>::value, "'HicannNotificationBehaviour' is not trivial");

struct Driver
{
    union
    {
        struct
        {
            
            uint64_t version : 64;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x8000;
    const static bool READABLE = true;
    const static bool WRITABLE = false;
};

static_assert(sizeof(Driver) == sizeof(uint64_t), "sizeof register file 'Driver' != sizeof uint64_t");
static_assert(std::is_trivial<Driver>::value, "'Driver' is not trivial");

struct Info
{
    union
    {
        struct
        {
            
            uint64_t guid : 24;
            uint64_t node_id : 16;
        };
        uint64_t raw;
    };



    const static RMA2_NLA ADDRESS = 0x8008;
    const static bool READABLE = true;
    const static bool WRITABLE = false;
};

static_assert(sizeof(Info) == sizeof(uint64_t), "sizeof register file 'Info' != sizeof uint64_t");
static_assert(std::is_trivial<Info>::value, "'Info' is not trivial");


#pragma GCC diagnostic pop


}
}
}