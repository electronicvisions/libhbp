#ifndef LIBHBP_CPP_REGISTER_FILES_H
#define LIBHBP_CPP_REGISTER_FILES_H

#include <cinttypes>
#include <iostream>
#include <bitset>
#include <typeinfo>

#include <extoll/rma.h>

namespace extoll {
namespace library {
#define ADDRESS(VALUE) \
    const static RMA2_NLA ADDRESS = VALUE
#define READ_WRITE(READ, WRITE) \
    const static bool READABLE = READ;\
    const static bool WRITABLE = WRITE
#define ASSERT_SIZE(NAME) static_assert(sizeof(NAME) <= 8," " #NAME " is too big!")
#define DEPRECATED __attribute__ ((deprecated))

namespace rf
{
template<typename RF>
uint64_t rf_to_data(const RF& rf)
{
    uint64_t data = 0;
    memcpy(&data, &rf, sizeof(RF));
    return data;
}

template<typename RF>
RF data_to_rf(uint64_t data)
{
    RF rf;
    memcpy(&rf, &data, sizeof(RF));
    return rf;
}

/// Addresses starting @0x0
/// FPGA reset register file

struct Reset
{
    bool core : 1;
    bool hicann : 1;
    bool arq : 1;
    ADDRESS(0x0);
    READ_WRITE(true, true);
};
ASSERT_SIZE(Reset);

/// Addresses starting @0x400
/// JTAG control register files

struct JtagCmd
{
    enum Type
    {
        Reset = 0,
        IR = 1,
        DR = 2,
        EnableClock = 4,
        DisableClock = 5
    };

    uint64_t type : 3;
    uint64_t length : 10;
    bool pause : 1;
    bool execute : 1;
    ADDRESS(0x400);
    READ_WRITE(true, true);
};
ASSERT_SIZE(JtagCmd);

struct JtagStatus
{
    bool clock_enabled : 1;
    bool paused : 1;
    ADDRESS(0x408);
    READ_WRITE(true, false);
};
ASSERT_SIZE(JtagStatus);

struct JtagSend
{
    uint64_t data;
    ADDRESS(0x480);
    READ_WRITE(true, true);
};
ASSERT_SIZE(JtagSend);

struct JtagReceive
{
    uint64_t data;
    ADDRESS(0x500);
    READ_WRITE(true, false);
};
ASSERT_SIZE(JtagReceive);

/// Addresses starting @0x800
/// HICANN control register files

struct HicannChannel
{
    uint64_t number : 3;
    ADDRESS(0x838);
    READ_WRITE(true, true);
};
ASSERT_SIZE(HicannChannel);

struct DEPRECATED ArqTimings
{
    uint64_t master_timeout : 10;
    uint64_t target_timeout : 10;
    uint64_t arbiter_delay : 5;
    bool bit : 1;
    ADDRESS(0x840);
    READ_WRITE(true, true);
};

/// Addresses starting @1090
/// Partner host configuration register files

struct HostEndpoint
{
    uint64_t node_id : 16;
    uint64_t protection_domain : 16;
    uint64_t vpid : 10;
    uint64_t mode : 6;
    ADDRESS(0x1090);
    READ_WRITE(true, true);


};
ASSERT_SIZE(HostEndpoint);

struct TraceRingbufferStart
{
    uint64_t address;
    ADDRESS(0x1098);
    READ_WRITE(true, true);
};
ASSERT_SIZE(TraceRingbufferStart);

struct TraceRingbufferCapacity
{
    uint64_t capacity : 32;
    uint64_t start_change_counter : 8;
    uint64_t capacity_change_counter : 8;
    bool init : 1;
    ADDRESS(0x10a0);
    READ_WRITE(true, true);

    TraceRingbufferCapacity(uint32_t, bool);
};
ASSERT_SIZE(TraceRingbufferCapacity);

struct ConfigResponse
{
    uint64_t address;
    ADDRESS(0x10a8);
    READ_WRITE(true, true);
};
ASSERT_SIZE(ConfigResponse);

struct HicannRingbufferStart
{
    uint64_t address;
    ADDRESS(0x10b0);
    READ_WRITE(true, true);
};
ASSERT_SIZE(HicannRingbufferStart);

struct HicannRingbufferCapacity
{
    uint64_t capacity : 32;
    uint64_t start_change_counter : 8;
    uint64_t capacity_change_counter : 8;
    bool init : 1;
    ADDRESS(0x10b8);
    READ_WRITE(true, true);

    HicannRingbufferCapacity(uint32_t, bool);
};
ASSERT_SIZE(HicannRingbufferCapacity);

struct TraceNotificationBehaviour
{
    uint64_t timeout : 32;
    uint64_t freq : 32;
    ADDRESS(0x10c0);
    READ_WRITE(true, true);
};
ASSERT_SIZE(TraceNotificationBehaviour);

struct HicannNotificationBehaviour
{
    uint64_t timeout : 32;
    uint64_t freq : 32;
    ADDRESS(0x10c8);
    READ_WRITE(true, true);
};
ASSERT_SIZE(HicannNotificationBehaviour);

/// Info register files
/// Addresses starting @0x8000

struct Driver
{
    uint32_t version;
    ADDRESS(0x8000);
    READ_WRITE(true, false);
};
ASSERT_SIZE(Driver);

struct Info
{
    uint64_t guid : 24;
    uint64_t node_id : 16;
    ADDRESS(0x8008);
    READ_WRITE(true, false);
};
ASSERT_SIZE(Info);

}

std::ostream& operator<<(std::ostream&, rf::JtagCmd::Type);

#undef ADDRESS
#undef READ_WRITE
#undef ASSERT_SIZE

}}

#endif
