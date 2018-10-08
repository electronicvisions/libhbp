#ifndef LIBHBP_CPP_REGISTER_FILES_H
#define LIBHBP_CPP_REGISTER_FILES_H

#include <cinttypes>
#include <rma.h>

#define REGISTER_FILE(NAME, NLA, FIELDS)\
struct NAME {\
    explicit NAME(uint64_t data);\
    const static RMA2_NLA rf_address = NLA;\
    FIELDS\
};\
namespace traits {\
template <>\
uint64_t rf_to_data(NAME);\
}

#define SIMPLE_REGISTER_FILE(NAME, NLA, TYPE)\
struct NAME {\
    explicit NAME(uint64_t data)\
        : value(TYPE(data)) {}\
    const static RMA2_NLA rf_address = NLA;\
    TYPE value;\
};\
namespace traits {\
template <>\
struct RfResultType<NAME> {\
    using value_type = TYPE;\
};}


namespace traits
{
    template <typename RF>
    struct RfResultType
    {
        using value_type = RF;
    };

    template <typename RF>
    uint64_t rf_to_data(RF rf)
    {
        return uint64_t(rf.value);
    }
}


SIMPLE_REGISTER_FILE(HicannChannel, 0x838, uint8_t)
SIMPLE_REGISTER_FILE(Driver, 0x8000, uint32_t)
SIMPLE_REGISTER_FILE(TraceRingbufferStart, 0x1098, uint64_t)
SIMPLE_REGISTER_FILE(ConfigResponse, 0x10a8, uint64_t)
SIMPLE_REGISTER_FILE(HicannRingbufferStart, 0x10b0, uint64_t)

REGISTER_FILE(Reset, 0x0,
    bool core;
    bool hicann;
    bool arq;
    Reset(bool, bool, bool);
)

REGISTER_FILE(Info, 0x8008,
    uint32_t guid;
    uint16_t node_id;
)

REGISTER_FILE(HostEndpoint, 0x1090,
    uint16_t node_id;
    uint16_t protection_domain;
    uint16_t vpid;
    uint8_t mode;
    HostEndpoint(uint16_t, uint16_t, uint16_t, uint8_t);
)

REGISTER_FILE(TraceRingbufferCapacity, 0x10a0,
    uint32_t capacity;
    uint8_t start_change_counter = 0;
    uint8_t capacity_change_counter = 0;
    bool init;
    TraceRingbufferCapacity(uint32_t, bool);
)

REGISTER_FILE(HicannRingbufferCapacity, 0x10b8,
    uint32_t capacity;
    uint8_t start_change_counter = 0;
    uint8_t capacity_change_counter = 0;
    bool init;
    HicannRingbufferCapacity(uint32_t, bool);
)

REGISTER_FILE(TraceNotificationBehaviour, 0x10c0,
    uint32_t timeout;
    uint32_t frequency;
    TraceNotificationBehaviour(uint32_t, uint32_t);
)

REGISTER_FILE(HicannNotificationBehaviour, 0x10c8,
    uint32_t timeout;
    uint32_t frequency;
    HicannNotificationBehaviour(uint32_t, uint32_t);
)

#undef REGISTER_FILE
#undef SIMPLE_REGISTER_FILE

namespace rf
{
enum class Readable
{
    Driver = 0x8000,
    Info = 0x8008
};

enum class ReadWrite
{
    HicannChannel = 0x838
};

enum class Writable
{

};
}

#endif //LIBHBP_CPP_REGISTER_FILES_H
