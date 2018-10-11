#include <register_files.h>

#include <bitset>

#define BIT(data, position) bool((data >> position) & 0x1)

using rf::JtagCmd;

std::ostream& operator<<(std::ostream& out, JtagCmd::Type type)
{
    switch (type)
    {
    case JtagCmd::Type::Reset:
        return out << "reset";
    case JtagCmd::Type::DisableClock:
        return out << "disable-clock";
    case JtagCmd::Type::DR:
        return out << "data-register";
    case JtagCmd::Type::EnableClock:
        return out << "enable-clock";
    case JtagCmd::Type::IR:
        return out << "instruction-register";
    default:
        return out << static_cast<int>(type);
    }
}

rf::TraceRingbufferCapacity::TraceRingbufferCapacity(uint32_t capacity, bool init)
    : capacity(capacity),
    start_change_counter(),
    capacity_change_counter(0),
    init(init) {}

rf::HicannRingbufferCapacity::HicannRingbufferCapacity(uint32_t capacity, bool init)
        : capacity(capacity),
          start_change_counter(),
          capacity_change_counter(0),
          init(init) {}
