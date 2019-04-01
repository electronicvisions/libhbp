#ifndef LIBHBP_CPP_EXCEPTION_H
#define LIBHBP_CPP_EXCEPTION_H

#include <stdexcept>
#include <bitset>

#include <extoll/rma.h>

namespace extoll {
namespace library {

//! \brief The base class for all exceptions in this library
//!
//! Only its child classes will be instantiated.
struct RmaError : std::runtime_error
{
    using runtime_error::runtime_error;
};

//! This exception indicates that a connection to a remote Fpga could not be established.
struct ConnectionFailed : RmaError
{
    using RmaError::RmaError;
};

//! \brief This exception indicates that a user-space buffer could not be registered with the extoll driver
//!
//! This can occur if two many regions are already registered with the driver
struct FailedToRegisterRegion : RmaError
{
    //! Creates an exception
    FailedToRegisterRegion();
};

//! \brief This exception indicates that a remote register file access has failed.
//!
//! Only its child classes will be instantiated.
struct RraError : RmaError
{
    //! Creates an exception from a message, a node id and a network logical address
    RraError(std::string, RMA2_Nodeid, RMA2_NLA);

    //! The node id of the node that caused the error
    RMA2_Nodeid node;
    //! The register file address that was accessed
    RMA2_NLA address;
};

//! \brief This exception indicates that the user tried to receive a Hicann config packet when nothing was sent.
//!
//! This can happen if the user did not send a read command previously or if the hardware has a bug.
struct HicannResponseTimedOut : RmaError
{
    //! Creates an exception
    HicannResponseTimedOut();
};

//! This exception indicates that a remote register file access read command failed
struct FailedToRead : RraError
{
    using RraError::RraError;
    //! Creates an exception from a node id and a network logical address
    FailedToRead(RMA2_Nodeid node, RMA2_NLA address);
};

//! This exception indicates that a remote register file access write command failed
struct FailedToWrite : RraError
{
    using RraError::RraError;
    //! Creates an exception from a node id and a network logical address
    FailedToWrite(RMA2_Nodeid node, RMA2_NLA address);
};

//! This exception occurs when the user tries to connect to a remote node that is not an HBP communication Fpga
struct NodeIsNoFpga : ConnectionFailed
{
    //! Creates an exception from a node id and an incorrect observed driver version
    NodeIsNoFpga(RMA2_Nodeid node, uint32_t driver);

    //! The node id of the node that couldn't be connected
    const RMA2_Nodeid node;
    //! \brief The driver version of the remote node.
    //!
    //! The value is `0xcafebabe` for valid HBP communication Fpgas
    const uint32_t driver;
};

//! This exception occurs when the user creates a JTag access object although the remote Fpga is not connected to any Hicann
struct NodeHasNoHicann : ConnectionFailed
{
    //! Creates an exception from a node id
    explicit NodeHasNoHicann(RMA2_Nodeid node);

    //! The node id of the node that has not Hicanns.
    const RMA2_Nodeid node;
};

//! This exception occurs when an internal Jtag instruction register shift failed
struct JtagIrShiftFailed : std::runtime_error
{
    //! Creates an exception from a node id and a pattern
    JtagIrShiftFailed(RMA2_Nodeid, uint8_t);

    //! The node id of the node that caused the error
    const RMA2_Nodeid node;
    //! The pattern that was observed instead of the expected
    const std::bitset<6> pattern;
};

}}

#endif //LIBHBP_CPP_EXCEPTION_H
