#ifndef LIBHBP_CPP_CONNECTION_H
#define LIBHBP_CPP_CONNECTION_H

#include <extoll/rma.h>
#include <extoll/buffer.h>

namespace extoll {
namespace library {

//! \brief Encapsulates the various handles needed for the `librma2` to represent a connection.
//!
//! Extoll keeps track of all Connections internally.
struct Endpoint
{
    //! A single connection to a remote node
    struct Connection
    {
        //! The network node
        RMA2_Port port = nullptr;
        //! The handle
        RMA2_Handle handle = nullptr;
        //! The virtual process id
        RMA2_VPID vpid = RMA2_VPID_ANY;

        //! The status of the last `librma2` function call
        RMA2_ERROR status = RMA2_SUCCESS;

        //! Open a single connection to the remote node.
        //! The connection type is selected here (Rra or Rma without Rra)
        //! \throws ConnectionFailed if an error happens inside `librma2`
        explicit Connection(RMA2_Nodeid, bool rra);
        //! This class is not copyable
        Connection(const Connection&) = delete;
        //! This class is not copy-assignable
        Connection& operator=(const Connection&) = delete;
        //! Closes all `librma2` resources
        ~Connection();
    };

    //! The node id of the remote node
    RMA2_Nodeid node;
    //! A remote register file connection
    Connection rra;
    //! A remote memory access connection
    Connection rma;

    //! A general purpose physical buffer
    PhysicalBuffer gp_buffer;
    //! The trace-pulse data ringbuffer
    RingBuffer trace_data;
    //! The hicann config ringbuffer
    RingBuffer hicann_config;

    //! \deprecated Use Fpga::config_response instead
    uint64_t fpga_config_response() const;
    //! The address of the Fpga config response memory
    RMA2_NLA fpga_config_address() const;

    //! Opens a connection to a remote node.
    //! \throws ConnectionFailed if there is an error inside `librma2`
    //! \throws FailedToWrite if the write test failed
    //! \throws FailedToRead if the read test failed
    explicit Endpoint(RMA2_Nodeid);
    //! This class is not copyable
    Endpoint(const Endpoint&) = delete;
    //! This class is not copy-assignable
    Endpoint& operator=(const Endpoint&) = delete;

    //! Performs a read test of a register.
    //! The test fails if no notification is received or the actually received
    //! value does not match the expected
    //! \throws FailedToRead if the test failed
    //! \throws ConnectionFailed if the notification timed out
    void perform_read_test(RMA2_NLA address, uint64_t expected);
    //! Performs a write test of a register.
    //! The test fails if no notification is received
    //! \throws FailedToWrite if the test failed
    //! \throws ConnectionFailed if the notification timed out
    void perform_write_test(RMA2_NLA address, uint64_t value);
};

}}

#endif //LIBHBP_CPP_CONNECTION_H
