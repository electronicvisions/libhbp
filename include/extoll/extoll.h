#ifndef LIBHBP_CPP_HBP_H
#define LIBHBP_CPP_HBP_H

#include <cstdint>
#include <map>
#include <vector>
#include <memory>

#include <extoll/rma.h>
#include <extoll/register_file.h>
#include <extoll/fpga.h>
#include <extoll/jtag.h>
#include <extoll/hicann.h>
#include <extoll/connection.h>
#include <extoll/hbp_def.h>

namespace extoll {
namespace library {

class Extoll
{
private:
    std::map<RMA2_Nodeid, Endpoint> connections;

    static std::unique_ptr<Extoll> instance;
public:
    RegisterFile register_file(RMA2_Nodeid node);
    JTag jtag(RMA2_Nodeid node);
    Fpga fpga(RMA2_Nodeid node);
    Hicann hicann(RMA2_Nodeid node, int8_t number);
    RingBuffer& hicann_config(RMA2_Nodeid node);
    RingBuffer& trace_pulse(RMA2_Nodeid node);
    Endpoint& connect(RMA2_Nodeid node);

    static Extoll& Instance();

    const static uint16_t HICANN_CONFIG = uint16_t(rf::TestControlType::HicannConfig);
    const static uint16_t TRACE_PULSE = uint16_t(rf::TestControlType::TracePulse);
private:


    friend class RegisterFile;
};

}}

#endif //LIBHBP_CPP_HBP_H
