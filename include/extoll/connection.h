#ifndef LIBHBP_CPP_CONNECTION_H
#define LIBHBP_CPP_CONNECTION_H

#include <extoll/rma.h>
#include <extoll/buffer.h>

namespace extoll {
namespace library {

struct Endpoint
{
    struct Connection
    {
        RMA2_Port port;
        RMA2_Handle handle;
        RMA2_VPID vpid;

        RMA2_ERROR status = RMA2_SUCCESS;

        explicit Connection(RMA2_Nodeid, bool);
        Connection(const Connection&) = delete;
        Connection& operator=(const Connection&) = delete;
        ~Connection();
    };

    RMA2_Nodeid node;
    Connection rra;
    Connection rma;

    PhysicalBuffer gp_buffer;
    PhysicalBuffer trace_data;
    PhysicalBuffer hicann_config;

    uint64_t fpga_config_response() const;
    RMA2_NLA fpga_config_address() const;

    explicit Endpoint(RMA2_Nodeid);
    Endpoint(const Endpoint&) = delete;
    Endpoint& operator=(const Endpoint&) = delete;

    void perform_read_test(RMA2_NLA, uint64_t);
    void perform_write_test(RMA2_NLA, uint64_t);
};

}}

#endif //LIBHBP_CPP_CONNECTION_H
