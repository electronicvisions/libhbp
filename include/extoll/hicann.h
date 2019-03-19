#ifndef LIBHBP_CPP_HICANN_H
#define LIBHBP_CPP_HICANN_H

#include <extoll/register_file.h>
#include <extoll/hbp_def.h>


namespace extoll {
namespace library {

class Hicann : public RegisterFile
{
    const static RMA2_NLA CONFIG_ADDRESS = RMA2_NLA(rf::TestControlType::HicannConfig) << 48ull;

    uint8_t _number;


    void clear(PhysicalBuffer&, size_t=0);
    void diff(PhysicalBuffer&, size_t=0);
public:
    Hicann(Endpoint&, uint8_t);

    void write(uint16_t address, uint32_t data);
    uint32_t read(uint16_t address);

    void send(uint64_t data);
    uint64_t receive();

    void clear_all();
    void diff_all();
};

}}

#endif //LIBHBP_CPP_HICANN_H
