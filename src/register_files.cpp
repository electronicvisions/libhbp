#include <register_files.h>

#define BIT(data, position) bool((data >> position) & 0x1)

Info::Info(uint64_t data)
        : guid(uint32_t(data & 0xffffff)), node_id(uint16_t(data >> 24)) {}

Reset::Reset(uint64_t data)
        : core(BIT(data, 0)), hicann(BIT(data, 1)), arq(BIT(data, 2)) {}

Reset::Reset(bool core, bool hicann, bool arq)
        : core(core), hicann(hicann), arq(arq) {}

HostEndpoint::HostEndpoint(uint16_t node_id, uint16_t protection_domain,
                               uint16_t vpid, uint8_t mode)
        : node_id(node_id), protection_domain(protection_domain), vpid(vpid), mode(mode) {}

TraceRingbufferCapacity::TraceRingbufferCapacity(uint32_t capacity, bool init)
        : capacity(capacity), init(init) {}

HicannRingbufferCapacity::HicannRingbufferCapacity(uint32_t capacity, bool init)
        : capacity(capacity), init(init) {}

TraceNotificationBehaviour::TraceNotificationBehaviour(uint32_t timeout, uint32_t frequency)
        : timeout(timeout), frequency(frequency) {}

HicannNotificationBehaviour::HicannNotificationBehaviour(uint32_t timeout, uint32_t frequency)
        : timeout(timeout), frequency(frequency) {}

template<>
uint64_t traits::rf_to_data(Reset rf)
{
    return uint64_t(rf.core) | uint64_t(rf.hicann << 1) | uint64_t(rf.arq << 2);
}

template <>
uint64_t traits::rf_to_data<HostEndpoint>(HostEndpoint rf)
{
    return rf.node_id
           | (uint64_t(rf.vpid) << 16ull)
           | (uint64_t(rf.protection_domain) << 32ull)
           | (uint64_t(rf.mode) << 42ull);
}

template <>
uint64_t traits::rf_to_data(HicannRingbufferCapacity rf)
{
    return uint64_t(rf.capacity) | (uint64_t(rf.init) << 48ull);
}
template <>
uint64_t traits::rf_to_data(TraceRingbufferCapacity rf)
{
    return uint64_t(rf.capacity) | (uint64_t(rf.init) << 48ull);
}

template <>
uint64_t traits::rf_to_data(TraceNotificationBehaviour rf)
{
    return uint64_t(rf.timeout) | (uint64_t(rf.frequency) << 32ull);
}

template <>
uint64_t traits::rf_to_data(HicannNotificationBehaviour rf)
{
    return uint64_t(rf.timeout) | (uint64_t(rf.frequency) << 32ull);
}