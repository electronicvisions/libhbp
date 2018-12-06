/**
 * This is a generated file - do not change it
 * 06.12.2018 19:39:55.276149 
 */

#pragma once

#include <cinttypes>

#include <extoll/rma.h>


namespace extoll {
namespace library {
namespace rf {

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
struct Reset {
    union {
        struct {
            bool core: 1;
            bool hicann: 1;
            bool arq: 1;
        };
        uint64_t raw;
    };

    const static RMA2_NLA ADDRESS = 0x0;
    const static bool READABLE = true;
    const static bool WRITABLE = true;
};
static_assert(sizeof(Reset) == sizeof(uint64_t), "sizeof register file 'Reset' != sizeof uint64_t");
static_assert(std::is_trivial<Reset>::value, "'Reset' is not trivial");
static_assert(std::has_trivial_copy_constructor<Reset>::value, "'Reset' has no trivial copy constructor");

struct JtagCmd {
    union {
        struct {
            uint64_t type: 3;
            uint64_t length: 10;
            bool pause: 1;
            bool execute: 1;
        };
        uint64_t raw;
    };

    enum Type {
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
static_assert(std::has_trivial_copy_constructor<JtagCmd>::value, "'JtagCmd' has no trivial copy constructor");

struct JtagStatus {
    union {
        struct {
            bool clock_enabled: 1;
            bool paused: 1;
        };
        uint64_t raw;
    };

    const static RMA2_NLA ADDRESS = 0x408;
    const static bool READABLE = true;
    const static bool WRITABLE = false;
};
static_assert(sizeof(JtagStatus) == sizeof(uint64_t), "sizeof register file 'JtagStatus' != sizeof uint64_t");
static_assert(std::is_trivial<JtagStatus>::value, "'JtagStatus' is not trivial");
static_assert(std::has_trivial_copy_constructor<JtagStatus>::value, "'JtagStatus' has no trivial copy constructor");

struct JtagSend {
    union {
        struct {
            uint64_t data: 64;
        };
        uint64_t raw;
    };

    const static RMA2_NLA ADDRESS = 0x480;
    const static bool READABLE = true;
    const static bool WRITABLE = true;
};
static_assert(sizeof(JtagSend) == sizeof(uint64_t), "sizeof register file 'JtagSend' != sizeof uint64_t");
static_assert(std::is_trivial<JtagSend>::value, "'JtagSend' is not trivial");
static_assert(std::has_trivial_copy_constructor<JtagSend>::value, "'JtagSend' has no trivial copy constructor");

struct JtagReceive {
    union {
        struct {
            uint64_t data: 64;
        };
        uint64_t raw;
    };

    const static RMA2_NLA ADDRESS = 0x500;
    const static bool READABLE = true;
    const static bool WRITABLE = false;
};
static_assert(sizeof(JtagReceive) == sizeof(uint64_t), "sizeof register file 'JtagReceive' != sizeof uint64_t");
static_assert(std::is_trivial<JtagReceive>::value, "'JtagReceive' is not trivial");
static_assert(std::has_trivial_copy_constructor<JtagReceive>::value, "'JtagReceive' has no trivial copy constructor");

struct HicannIfState {
    union {
        struct {
            uint64_t channel_status: 8;
            uint64_t crc_count: 8;
            uint64_t systime: 14;
        };
        uint64_t raw;
    };

    const static RMA2_NLA ADDRESS = 0x800;
    const static bool READABLE = true;
    const static bool WRITABLE = false;
};
static_assert(sizeof(HicannIfState) == sizeof(uint64_t), "sizeof register file 'HicannIfState' != sizeof uint64_t");
static_assert(std::is_trivial<HicannIfState>::value, "'HicannIfState' is not trivial");
static_assert(std::has_trivial_copy_constructor<HicannIfState>::value, "'HicannIfState' has no trivial copy constructor");

struct HicannIfRxConfig {
    union {
        struct {
            uint64_t data: 64;
        };
        uint64_t raw;
    };

    const static RMA2_NLA ADDRESS = 0x808;
    const static bool READABLE = true;
    const static bool WRITABLE = false;
};
static_assert(sizeof(HicannIfRxConfig) == sizeof(uint64_t), "sizeof register file 'HicannIfRxConfig' != sizeof uint64_t");
static_assert(std::is_trivial<HicannIfRxConfig>::value, "'HicannIfRxConfig' is not trivial");
static_assert(std::has_trivial_copy_constructor<HicannIfRxConfig>::value, "'HicannIfRxConfig' has no trivial copy constructor");

struct HicannIfRxPulse {
    union {
        struct {
            uint64_t data: 24;
        };
        uint64_t raw;
    };

    const static RMA2_NLA ADDRESS = 0x810;
    const static bool READABLE = true;
    const static bool WRITABLE = false;
};
static_assert(sizeof(HicannIfRxPulse) == sizeof(uint64_t), "sizeof register file 'HicannIfRxPulse' != sizeof uint64_t");
static_assert(std::is_trivial<HicannIfRxPulse>::value, "'HicannIfRxPulse' is not trivial");
static_assert(std::has_trivial_copy_constructor<HicannIfRxPulse>::value, "'HicannIfRxPulse' has no trivial copy constructor");

struct HicannIfConfig {
    union {
        struct {
            bool start_link: 1;
            bool loopback_enable: 1;
            bool auto_init: 1;
            bool init_master: 1;
            bool use_timestamp: 1;
            bool auto_limit: 1;
            bool pulse_protocol: 1;
            bool config_protocol: 1;
            uint64_t heap_mode: 8;
            uint64_t limit: 11;
            bool dc_coding: 1;
        };
        uint64_t raw;
    };

    const static RMA2_NLA ADDRESS = 0x818;
    const static bool READABLE = true;
    const static bool WRITABLE = true;
};
static_assert(sizeof(HicannIfConfig) == sizeof(uint64_t), "sizeof register file 'HicannIfConfig' != sizeof uint64_t");
static_assert(std::is_trivial<HicannIfConfig>::value, "'HicannIfConfig' is not trivial");
static_assert(std::has_trivial_copy_constructor<HicannIfConfig>::value, "'HicannIfConfig' has no trivial copy constructor");

struct HicannIfControls {
    union {
        struct {
            bool tx_hicann_pulse_enable: 1;
            bool tx_hicann_config_enable: 1;
            bool routing_data_enable: 1;
            bool channel_reset: 1;
            bool crc_count_reset: 1;
        };
        uint64_t raw;
    };

    const static RMA2_NLA ADDRESS = 0x820;
    const static bool READABLE = false;
    const static bool WRITABLE = true;
};
static_assert(sizeof(HicannIfControls) == sizeof(uint64_t), "sizeof register file 'HicannIfControls' != sizeof uint64_t");
static_assert(std::is_trivial<HicannIfControls>::value, "'HicannIfControls' is not trivial");
static_assert(std::has_trivial_copy_constructor<HicannIfControls>::value, "'HicannIfControls' has no trivial copy constructor");

struct HicannIfTxData {
    union {
        struct {
            uint64_t data: 64;
        };
        uint64_t raw;
    };

    const static RMA2_NLA ADDRESS = 0x828;
    const static bool READABLE = true;
    const static bool WRITABLE = true;
};
static_assert(sizeof(HicannIfTxData) == sizeof(uint64_t), "sizeof register file 'HicannIfTxData' != sizeof uint64_t");
static_assert(std::is_trivial<HicannIfTxData>::value, "'HicannIfTxData' is not trivial");
static_assert(std::has_trivial_copy_constructor<HicannIfTxData>::value, "'HicannIfTxData' has no trivial copy constructor");

struct HicannPacketGen {
    union {
        struct {
            uint64_t count: 25;
            bool error: 1;
            bool enable: 1;
        };
        uint64_t raw;
    };

    const static RMA2_NLA ADDRESS = 0x830;
    const static bool READABLE = true;
    const static bool WRITABLE = true;
};
static_assert(sizeof(HicannPacketGen) == sizeof(uint64_t), "sizeof register file 'HicannPacketGen' != sizeof uint64_t");
static_assert(std::is_trivial<HicannPacketGen>::value, "'HicannPacketGen' is not trivial");
static_assert(std::has_trivial_copy_constructor<HicannPacketGen>::value, "'HicannPacketGen' has no trivial copy constructor");

struct HicannChannel {
    union {
        struct {
            uint64_t number: 3;
        };
        uint64_t raw;
    };

    const static RMA2_NLA ADDRESS = 0x838;
    const static bool READABLE = true;
    const static bool WRITABLE = true;
};
static_assert(sizeof(HicannChannel) == sizeof(uint64_t), "sizeof register file 'HicannChannel' != sizeof uint64_t");
static_assert(std::is_trivial<HicannChannel>::value, "'HicannChannel' is not trivial");
static_assert(std::has_trivial_copy_constructor<HicannChannel>::value, "'HicannChannel' has no trivial copy constructor");

struct ArqTimings {
    union {
        struct {
            uint64_t master_timeout: 10;
            uint64_t target_timeout: 10;
            uint64_t arbiter_delay: 5;
            bool bit: 1;
        };
        uint64_t raw;
    };

    const static RMA2_NLA ADDRESS = 0x840;
    const static bool READABLE = true;
    const static bool WRITABLE = true;
};
static_assert(sizeof(ArqTimings) == sizeof(uint64_t), "sizeof register file 'ArqTimings' != sizeof uint64_t");
static_assert(std::is_trivial<ArqTimings>::value, "'ArqTimings' is not trivial");
static_assert(std::has_trivial_copy_constructor<ArqTimings>::value, "'ArqTimings' has no trivial copy constructor");

struct HostEndpoint {
    union {
        struct {
            uint64_t node_id: 16;
            uint64_t protection_domain: 16;
            uint64_t vpid: 10;
            uint64_t mode: 6;
        };
        uint64_t raw;
    };

    const static RMA2_NLA ADDRESS = 0x1090;
    const static bool READABLE = true;
    const static bool WRITABLE = true;
};
static_assert(sizeof(HostEndpoint) == sizeof(uint64_t), "sizeof register file 'HostEndpoint' != sizeof uint64_t");
static_assert(std::is_trivial<HostEndpoint>::value, "'HostEndpoint' is not trivial");
static_assert(std::has_trivial_copy_constructor<HostEndpoint>::value, "'HostEndpoint' has no trivial copy constructor");

struct TraceRingbufferStart {
    union {
        struct {
            uint64_t address: 64;
        };
        uint64_t raw;
    };

    const static RMA2_NLA ADDRESS = 0x1098;
    const static bool READABLE = true;
    const static bool WRITABLE = true;
};
static_assert(sizeof(TraceRingbufferStart) == sizeof(uint64_t), "sizeof register file 'TraceRingbufferStart' != sizeof uint64_t");
static_assert(std::is_trivial<TraceRingbufferStart>::value, "'TraceRingbufferStart' is not trivial");
static_assert(std::has_trivial_copy_constructor<TraceRingbufferStart>::value, "'TraceRingbufferStart' has no trivial copy constructor");

struct TraceRingbufferCapacity {
    union {
        struct {
            uint64_t capacity: 32;
            uint64_t start_change_counter: 8;
            uint64_t capacity_change_counter: 8;
            bool init: 1;
        };
        uint64_t raw;
    };

    const static RMA2_NLA ADDRESS = 0x10a0;
    const static bool READABLE = true;
    const static bool WRITABLE = true;
};
static_assert(sizeof(TraceRingbufferCapacity) == sizeof(uint64_t), "sizeof register file 'TraceRingbufferCapacity' != sizeof uint64_t");
static_assert(std::is_trivial<TraceRingbufferCapacity>::value, "'TraceRingbufferCapacity' is not trivial");
static_assert(std::has_trivial_copy_constructor<TraceRingbufferCapacity>::value, "'TraceRingbufferCapacity' has no trivial copy constructor");

struct ConfigResponse {
    union {
        struct {
            uint64_t address: 64;
        };
        uint64_t raw;
    };

    const static RMA2_NLA ADDRESS = 0x10a8;
    const static bool READABLE = true;
    const static bool WRITABLE = true;
};
static_assert(sizeof(ConfigResponse) == sizeof(uint64_t), "sizeof register file 'ConfigResponse' != sizeof uint64_t");
static_assert(std::is_trivial<ConfigResponse>::value, "'ConfigResponse' is not trivial");
static_assert(std::has_trivial_copy_constructor<ConfigResponse>::value, "'ConfigResponse' has no trivial copy constructor");

struct HicannRingbufferStart {
    union {
        struct {
            uint64_t address: 64;
        };
        uint64_t raw;
    };

    const static RMA2_NLA ADDRESS = 0x10b0;
    const static bool READABLE = true;
    const static bool WRITABLE = true;
};
static_assert(sizeof(HicannRingbufferStart) == sizeof(uint64_t), "sizeof register file 'HicannRingbufferStart' != sizeof uint64_t");
static_assert(std::is_trivial<HicannRingbufferStart>::value, "'HicannRingbufferStart' is not trivial");
static_assert(std::has_trivial_copy_constructor<HicannRingbufferStart>::value, "'HicannRingbufferStart' has no trivial copy constructor");

struct HicannRingbufferCapacity {
    union {
        struct {
            uint64_t capacity: 32;
            uint64_t start_change_counter: 8;
            uint64_t capacity_change_counter: 8;
            bool init: 1;
        };
        uint64_t raw;
    };

    const static RMA2_NLA ADDRESS = 0x10b8;
    const static bool READABLE = true;
    const static bool WRITABLE = true;
};
static_assert(sizeof(HicannRingbufferCapacity) == sizeof(uint64_t), "sizeof register file 'HicannRingbufferCapacity' != sizeof uint64_t");
static_assert(std::is_trivial<HicannRingbufferCapacity>::value, "'HicannRingbufferCapacity' is not trivial");
static_assert(std::has_trivial_copy_constructor<HicannRingbufferCapacity>::value, "'HicannRingbufferCapacity' has no trivial copy constructor");

struct TraceNotificationBehaviour {
    union {
        struct {
            uint64_t timeout: 32;
            uint64_t frequency: 32;
        };
        uint64_t raw;
    };

    const static RMA2_NLA ADDRESS = 0x10c0;
    const static bool READABLE = true;
    const static bool WRITABLE = true;
};
static_assert(sizeof(TraceNotificationBehaviour) == sizeof(uint64_t), "sizeof register file 'TraceNotificationBehaviour' != sizeof uint64_t");
static_assert(std::is_trivial<TraceNotificationBehaviour>::value, "'TraceNotificationBehaviour' is not trivial");
static_assert(std::has_trivial_copy_constructor<TraceNotificationBehaviour>::value, "'TraceNotificationBehaviour' has no trivial copy constructor");

struct HicannNotificationBehaviour {
    union {
        struct {
            uint64_t timeout: 32;
            uint64_t frequency: 32;
        };
        uint64_t raw;
    };

    const static RMA2_NLA ADDRESS = 0x10c8;
    const static bool READABLE = true;
    const static bool WRITABLE = true;
};
static_assert(sizeof(HicannNotificationBehaviour) == sizeof(uint64_t), "sizeof register file 'HicannNotificationBehaviour' != sizeof uint64_t");
static_assert(std::is_trivial<HicannNotificationBehaviour>::value, "'HicannNotificationBehaviour' is not trivial");
static_assert(std::has_trivial_copy_constructor<HicannNotificationBehaviour>::value, "'HicannNotificationBehaviour' has no trivial copy constructor");

struct Driver {
    union {
        struct {
            uint64_t version: 64;
        };
        uint64_t raw;
    };

    const static RMA2_NLA ADDRESS = 0x8000;
    const static bool READABLE = true;
    const static bool WRITABLE = false;
};
static_assert(sizeof(Driver) == sizeof(uint64_t), "sizeof register file 'Driver' != sizeof uint64_t");
static_assert(std::is_trivial<Driver>::value, "'Driver' is not trivial");
static_assert(std::has_trivial_copy_constructor<Driver>::value, "'Driver' has no trivial copy constructor");

struct Info {
    union {
        struct {
            uint64_t guid: 24;
            uint64_t node_id: 16;
        };
        uint64_t raw;
    };

    const static RMA2_NLA ADDRESS = 0x8008;
    const static bool READABLE = true;
    const static bool WRITABLE = false;
};
static_assert(sizeof(Info) == sizeof(uint64_t), "sizeof register file 'Info' != sizeof uint64_t");
static_assert(std::is_trivial<Info>::value, "'Info' is not trivial");
static_assert(std::has_trivial_copy_constructor<Info>::value, "'Info' has no trivial copy constructor");

#pragma GCC diagnostic pop
}}}
