#ifndef LIBHBP_CPP_HICANN_H
#define LIBHBP_CPP_HICANN_H

#include <extoll/register_file.h>
#include <extoll/rf_definitions.h>


namespace extoll {
namespace library {

//! This class provides a low-level interface for sending Hicann config packets.
//! This class should be instantiated through the factory functions in Extoll
class Hicann : public RegisterFile
{
    const static RMA2_NLA CONFIG_ADDRESS = RMA2_NLA(rf::TestControlType::HicannConfig) << 48ull;

    uint8_t _number;
public:
    //! Create a Hicann config interface from a given Endpoint and a Hicann.
    //! This constructor should not be used directly. Use the factory functions
    //! in Extoll instead.
    Hicann(Endpoint&, uint8_t);

    //! \deprecated
    void write(uint16_t address, uint32_t data);
    //! \deprecated
    uint32_t read(uint16_t address);

    //! \deprecated
    void send(uint64_t data);
    //! \deprecated
    uint64_t receive();
};

}}

#endif //LIBHBP_CPP_HICANN_H
