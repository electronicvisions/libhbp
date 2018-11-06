#ifndef LIBHBP_CPP_JTAG_H
#define LIBHBP_CPP_JTAG_H

#include <bitset>

#include <register_file.h>
#include <jtag_registers.h>
#include "exception.h"

namespace extoll {
namespace library {

class JTag : protected RegisterFile
{

public:
    explicit JTag(Endpoint&);

    void reset();
    void set_bypass();
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
    using namespace rf;

    RegisterFile::write<JtagSend>({pattern.to_ullong()});
    RegisterFile::write<JtagCmd>({JtagCmd::Type::DR, length, false, true});
    wait_until_finished();

    return RegisterFile::read(JtagReceive::ADDRESS);
}

template <typename JR>
typename std::enable_if<JR::READABLE && !JR::WRITABLE, uint64_t>::type
JTag::read()
{
    using namespace rf;

    RegisterFile::write(JtagSend::ADDRESS, JR::ADDRESS);
    RegisterFile::write<JtagCmd>({JtagCmd::IR, 6, false, true});
    wait_until_finished();

    RegisterFile::write(JtagSend::ADDRESS, 0);
    RegisterFile::write<JtagCmd>({JtagCmd::DR, JR::SIZE, false, true});
    wait_until_finished();

    return RegisterFile::read(JtagReceive::ADDRESS) & JR::MASK;
}

template<typename JR>
typename std::enable_if<JR::WRITABLE && !JR::READABLE, void>::type
JTag::write(uint64_t value)
{
    using namespace rf;

    RegisterFile::write(JtagSend::ADDRESS, JR::ADDRESS);
    RegisterFile::write<JtagCmd>({JtagCmd::IR, 6, false, true});
    wait_until_finished();

    RegisterFile::write(JtagSend::ADDRESS, value & JR::MASK);
    RegisterFile::write<JtagCmd>({JtagCmd::DR, JR::SIZE, false, true});
    wait_until_finished();
}

template <typename JR>
typename std::enable_if<JR::WRITABLE && JR::READABLE, uint64_t>::type
JTag::write(uint64_t value)
{
    using namespace rf;

    RegisterFile::write(JtagSend::ADDRESS, JR::ADDRESS);
    RegisterFile::write<JtagCmd>({JtagCmd::IR, 6, false, true});
    wait_until_finished();

    RegisterFile::write(JtagSend::ADDRESS, value & JR::MASK);
    RegisterFile::write<JtagCmd>({JtagCmd::DR, JR::SIZE, false, true});
    wait_until_finished();

    return RegisterFile::read(JtagReceive::ADDRESS) & JR::MASK;
}

template<typename JR>
void JTag::trigger()
{
    static_assert(JR::TRIGGER, "JTAG register is not a trigger!");

    using namespace rf;

    RegisterFile::write(JtagSend::ADDRESS, JR::ADDRESS);
    RegisterFile::write<JtagCmd>({JtagCmd::IR, 6, false, true});
    wait_until_finished();


}

}}

#endif
