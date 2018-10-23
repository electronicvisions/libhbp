#ifndef LIBHBP_CPP_CONNECTION_H
#define LIBHBP_CPP_CONNECTION_H

#include <rma.h>
#include <physical_buffer.h>

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

    Connection rra;
    Connection rma;

    RMA2_Nodeid node;

    PhysicalBuffer gp_buffer;
    PhysicalBuffer trace_data;
    PhysicalBuffer hicann_config;

    uint64_t fpga_config_response() const;
    RMA2_NLA fpga_config_address() const;

    explicit Endpoint(RMA2_Nodeid);
    Endpoint(const Endpoint&) = delete;
    Endpoint& operator=(const Endpoint&) = delete;
};


#endif //LIBHBP_CPP_CONNECTION_H
