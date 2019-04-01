#ifndef LIBHBP_CPP_JTAG_H
#define LIBHBP_CPP_JTAG_H

#include <bitset>

#include <extoll/register_file.h>
#include <extoll/jtag_definitions.h>
#include <extoll/exception.h>

namespace extoll {
namespace library {

//! \brief This class provides Jtag access on-top of the register file interface
//!
//! This class should be instantiated through the factory functions in Extoll.
//! A Jtag connection can only be established when there is at least one Hicann
//! connected to the Fpga.
class JTag : protected RegisterFile
{

public:
    //! \brief Create a Jtag interface from a given Endpoint
    //!
    //! This constructor should not be used directly. Use the factory functions
    //! in Extoll instead.
    //! \throws NodeHasNoHicann when the Fpga is not connected to any Hicann
    explicit JTag(Endpoint&);
    //! This class is not copyable
    JTag(const JTag&) = delete;
    //! This class is movable
    JTag(JTag&&) noexcept = default;
    //! This class is not copy-assignable
    JTag& operator=(const JTag&) = delete;

    //! Resets the TAP controller on the hardware site
    void reset();
    //! \brief Sets all Hicanns into bypass mode
    //!
    //! This is a low-level interface, handle with care!
    void set_bypass();

    //! \brief Selects the specified command register on all Hicanns
    //!
    //! This is a low-level interface, handle with care!
    void set_command(uint64_t command);
    //! \brief Selects the specified command on the specified Hicann and sets all others into bypass mode
    //!
    //! This is a low-level interface, handle with care!
    void set_command(uint64_t command, uint8_t hicann);

    //! \brief Writes the data to the specified Hicann.
    //!
    //! This is a low-level interface, handle with care!
    void set_data(uint64_t data, uint16_t length, uint8_t hicann);
    //! \brief Writes the data to the specified Hicann and reads the result.
    //!
    //! This is a low-level interface, handle with care!
    uint64_t set_get_data(uint64_t, uint16_t length, uint8_t hicann);
    //! \brief Reads data from the specified Hicann.
    //!
    //! This is a low-level interface, handle with care!
    uint64_t get_data(uint16_t length, uint8_t hicann);

    //! \brief Read a command from the specified Hicann.
    //!
    //! This only works on read-only Jtag registers
    //! \code
    //! std::cout << jtag.read<RxData>(0).raw << std::endl;
    //! \endcode
    template <typename JR>
    typename std::enable_if<JR::READABLE && !JR::WRITABLE, uint64_t>::type
    read(uint8_t hicann);

    //! \brief Write a command to the specified Hicann.
    //!
    //! This only works on write-only Jtag registers
    //! \code
    //! jtag.write<TxData>({1}, 0);
    //! \endcode
    template <typename JR>
    typename std::enable_if<JR::WRITABLE && !JR::READABLE, void>::type
    write(uint64_t, uint8_t hicann);

    //! \brief Write a command to the specified Hicann and read the result.
    //!
    //! This only works on read-write Jtag registers
    //! \code
    //! std::cout << jtag.write<IBias>({1}, 0) << std::endl;
    //! \endcode
    template <typename JR>
    typename std::enable_if<JR::WRITABLE && JR::READABLE, uint64_t>::type
    write(uint64_t, uint8_t hicann);

    //! \deprecated
    template <typename JR>
    void trigger();
    //! \brief Trigger a command on the specified Hicann.
    //!
    //! \code
    //! jtag.trigger<StartLink>(0);
    //! \endcode
    template <typename JR>
    void trigger(uint8_t hicann);

    //! \brief The number of Hicanns connected to the Fpga
    //!
    //! This number will always be larger than one and smaller than nine.
    size_t active_hicanns() const;
private:
    void wait_until_finished() const;
    void shift_command(uint64_t command);
    uint64_t shift_data_out(uint16_t length, uint8_t hicann);

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
