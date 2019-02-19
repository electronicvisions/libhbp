#ifndef LIBHBP_CPP_JTAG_H
#define LIBHBP_CPP_JTAG_H

#include <bitset>

#include <extoll/register_file.h>
#include <extoll/jtag_registers.h>
#include <extoll/exception.h>

namespace extoll {
namespace library {

class JTag : protected RegisterFile
{

public:
    explicit JTag(Endpoint&);
    JTag(const JTag&) = delete;
    JTag(JTag&&) noexcept = default;

    void reset();
    void set_bypass();

    void set_command(uint64_t command);
    void set_command(uint64_t command, uint8_t hicann);

    void set_data(uint64_t data, uint16_t length, uint8_t hicann);
    uint64_t set_get_data(uint64_t, uint16_t length, uint8_t hicann);
    uint64_t get_data(uint16_t length, uint8_t hicann);

    template <typename JR>
    typename std::enable_if<JR::READABLE && !JR::WRITABLE, uint64_t>::type
    read(uint8_t hicann);

    template <typename JR>
    typename std::enable_if<JR::WRITABLE && !JR::READABLE, void>::type
    write(uint64_t, uint8_t hicann);

    template <typename JR>
    typename std::enable_if<JR::WRITABLE && JR::READABLE, uint64_t>::type
    write(uint64_t, uint8_t hicann);

    template <typename JR>
    void trigger();
    template <typename JR>
    void trigger(uint8_t hicann);

    size_t active_hicanns() const;
private:
    void wait_until_finished() const;
    void shift_command(uint64_t command);

    uint8_t _hicanns = 0;
};

template <typename JR>
typename std::enable_if<JR::READABLE && !JR::WRITABLE, uint64_t>::type
JTag::read(uint8_t hicann)
{
    set_command(JR::ADDRESS, hicann);
    return get_data(JR::SIZE, hicann) & JR::MASK;
}

template<typename JR>
typename std::enable_if<JR::WRITABLE && !JR::READABLE, void>::type
JTag::write(uint64_t value, uint8_t hicann)
{
    set_command(JR::ADDRESS, hicann);
    set_data(value, JR::SIZE, hicann);
}

template <typename JR>
typename std::enable_if<JR::WRITABLE && JR::READABLE, uint64_t>::type
JTag::write(uint64_t value, uint8_t hicann)
{
    set_command(JR::ADDRESS, hicann);
    return set_get_data(value, JR::SIZE, hicann) & JR::MASK;
}

template<typename JR>
void JTag::trigger()
{
    using extoll::library::rf::JtagCmd;
    static_assert(JR::TRIGGER, "JTAG register is not a trigger!");
    set_command(JR::ADDRESS);
    RegisterFile::write<JtagCmd>({JtagCmd::DR, 1, false, true});
    wait_until_finished();
}

template<typename JR>
void JTag::trigger(uint8_t hicann)
{
    using extoll::library::rf::JtagCmd;
    static_assert(JR::TRIGGER, "JTAG register is not a trigger!");
    set_command(JR::ADDRESS, hicann);
    RegisterFile::write<JtagCmd>({JtagCmd::DR, 1, false, true});
    wait_until_finished();
}

}}

#endif
