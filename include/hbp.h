#ifndef LIBHBP_CPP_HBP_H
#define LIBHBP_CPP_HBP_H

#include <cstdint>
#include <map>
#include <vector>

#include <rma.h>
#include <register_file.h>
#include <fpga.h>
#include <jtag.h>
#include <hicann.h>
#include <connection.h>


class HBP
{
private:
    std::map<RMA2_Nodeid, Endpoint> connections;
public:
    RegisterFile register_file(RMA2_Nodeid node);
    JTag jtag(RMA2_Nodeid node);
    Fpga fpga(RMA2_Nodeid node);
    Hicann hicann(RMA2_Nodeid node, int8_t number);

private:
    Endpoint& connect(RMA2_Nodeid node);

    friend class RegisterFile;
};

#endif //LIBHBP_CPP_HBP_H
