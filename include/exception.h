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
    explicit ConnectionFailed(std::string);
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
    explicit IoctlError(std::string);
};

struct NodeIdNoPcb : std::runtime_error
{
    NodeIdNoPcb(RMA2_Nodeid node, uint32_t driver);

    const RMA2_Nodeid node;
    const uint32_t driver;
};

#endif //LIBHBP_CPP_EXCEPTION_H
