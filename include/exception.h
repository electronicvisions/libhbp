#ifndef LIBHBP_CPP_EXCEPTION_H
#define LIBHBP_CPP_EXCEPTION_H

#include <stdexcept>

#include <rma.h>


struct RmaError : std::runtime_error
{
    using runtime_error::runtime_error;
};

struct ConnectionFailed : RmaError
{
    using RmaError::RmaError;
};

struct RraError : RmaError
{
    RraError(std::string, RMA2_Nodeid, RMA2_NLA);

    RMA2_Nodeid node;
    RMA2_NLA address;
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

struct IoctlError : std::runtime_error
{
    using runtime_error::runtime_error;
};

struct NodeIsNoFcp : ConnectionFailed
{
    NodeIsNoFcp(RMA2_Nodeid node, uint32_t driver);

    const RMA2_Nodeid node;
    const uint32_t driver;
};

struct NodeHasNoHicann : ConnectionFailed
{
    explicit NodeHasNoHicann(RMA2_Nodeid node);

    const RMA2_Nodeid node;
};

#endif //LIBHBP_CPP_EXCEPTION_H
