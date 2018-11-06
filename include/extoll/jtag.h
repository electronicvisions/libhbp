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

    void reset();
    void set_bypass();
    void set_command(uint64_t command);
    void set_data(uint64_t data, uint16_t length);
    uint64_t set_get_data(uint64_t, uint16_t length);
    template <size_t S>
    std::bitset<S> shift_through(const char*, uint16_t length=64);
    template <size_t S>
    std::bitset<S> shift_through(std::bitset<S>, uint16_t length=64);


    template <typename JR>
    typename std::enable_if<JR::READABLE && !JR::WRITABLE, uint64_t>::type read();
    template <typename JR>
    typename std::enable_if<JR::WRITABLE && !JR::READABLE, void>::type write(uint64_t);
    template <typename JR>
    typename std::enable_if<JR::WRITABLE && JR::READABLE, uint64_t>::type write(uint64_t);
    template <typename JR>
    void trigger();


private:
    void wait_until_finished() const;

};

template <size_t S>
std::bitset<S> JTag::shift_through(const char* pattern, uint16_t length)
{
    return shift_through(std::bitset<S>(pattern), length);
}

template <size_t S>
std::bitset<S> JTag::shift_through(std::bitset<S> pattern, uint16_t length)
{
    return set_get_data(pattern.to_ullong(), length);
}

template <typename JR>
typename std::enable_if<JR::READABLE && !JR::WRITABLE, uint64_t>::type
JTag::read()
{
    set_command(JR::ADDRESS);
    return set_get_data(0, JR::SIZE) & JR::MASK;
}

template<typename JR>
typename std::enable_if<JR::WRITABLE && !JR::READABLE, void>::type
JTag::write(uint64_t value)
{
    set_command(JR::ADDRESS);
    set_data(value, JR::SIZE);
}

template <typename JR>
typename std::enable_if<JR::WRITABLE && JR::READABLE, uint64_t>::type
JTag::write(uint64_t value)
{
    set_command(JR::ADDRESS);
    return set_get_data(value, JR::SIZE) & JR::MASK;
}

template<typename JR>
void JTag::trigger()
{
    static_assert(JR::TRIGGER, "JTAG register is not a trigger!");
    set_command(JR::ADDRESS);
}

}}

#endif
