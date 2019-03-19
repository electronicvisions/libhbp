#ifndef LIBHBP_CPP_EXCEPTION_H
#define LIBHBP_CPP_EXCEPTION_H

#include <stdexcept>
#include <bitset>

#include <extoll/rma.h>

namespace extoll {
namespace library {

struct RmaError : std::runtime_error
{
    using runtime_error::runtime_error;
};

struct ConnectionFailed : RmaError
{
    using RmaError::RmaError;
};

struct FailedToRegisterRegion : RmaError
{
    FailedToRegisterRegion();
};

struct RraError : RmaError
{
    RraError(std::string, RMA2_Nodeid, RMA2_NLA);

    RMA2_Nodeid node;
    RMA2_NLA address;
};

struct HicannResponseTimedOut : RmaError
{
    HicannResponseTimedOut();
};

struct FailedToRead : RraError
{
    using RraError::RraError;
    FailedToRead(RMA2_Nodeid node, RMA2_NLA address);
};

struct FailedToWrite : RraError
{
    using RraError::RraError;
    FailedToWrite(RMA2_Nodeid node, RMA2_NLA address);
};


struct NodeIsNoFpga : ConnectionFailed
{
    NodeIsNoFpga(RMA2_Nodeid node, uint32_t driver);

    const RMA2_Nodeid node;
    const uint32_t driver;
};

struct NodeHasNoHicann : ConnectionFailed
{
    explicit NodeHasNoHicann(RMA2_Nodeid node);

    const RMA2_Nodeid node;
};

struct JtagIrShiftFailed : std::runtime_error
{
    JtagIrShiftFailed(RMA2_Nodeid, uint8_t);

    const RMA2_Nodeid node;
    const std::bitset<6> pattern;
};

}}

#endif //LIBHBP_CPP_EXCEPTION_H
