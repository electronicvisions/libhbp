#ifndef LIBHBP_CPP_HBP_H
#define LIBHBP_CPP_HBP_H

#include <cstdint>
#include <map>
#include <vector>

#include <extoll/rma.h>
#include <extoll/register_file.h>
#include <extoll/fpga.h>
#include <extoll/jtag.h>
#include <extoll/hicann.h>
#include <extoll/connection.h>

namespace extoll {
namespace library {

class Extoll
{
private:
    std::map<RMA2_Nodeid, Endpoint> connections;
public:
    RegisterFile register_file(RMA2_Nodeid node);
    JTag jtag(RMA2_Nodeid node);
    Fpga fpga(RMA2_Nodeid node);
    Hicann hicann(RMA2_Nodeid node, int8_t number);
    Endpoint& connect(RMA2_Nodeid node);
    ~Extoll();
private:


    friend class RegisterFile;
};

}}

#endif //LIBHBP_CPP_HBP_H
