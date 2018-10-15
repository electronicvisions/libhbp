#ifndef LIBHBP_CPP_CONNECTION_H
#define LIBHBP_CPP_CONNECTION_H

#include <rma.h>
#include <physical_buffer.h>

struct Connection
{
    RMA2_Port port;
    RMA2_Handle handle;
    RMA2_Nodeid node;
    RMA2_VPID vpid;

    PhysicalBuffer gp_buffer;
    PhysicalBuffer trace_data;
    PhysicalBuffer hicann_config;

    RMA2_ERROR status = RMA2_SUCCESS;

    explicit Connection(RMA2_Nodeid, bool);
    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;
    ~Connection();
};


#endif //LIBHBP_CPP_CONNECTION_H
