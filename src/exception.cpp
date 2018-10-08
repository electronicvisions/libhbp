#include <exception.h>

#include <utility>

NodeIdNoPcb::NodeIdNoPcb(RMA2_Nodeid node, uint32_t driver)
    : std::runtime_error("Connection to PCB failed, because node is not a PCB!"),
    node(node), driver(driver) {}

IoctlError::IoctlError(std::string msg)
    : std::runtime_error(msg) {}

ConnectionFailed::ConnectionFailed(std::string msg)
    : RmaError(msg) {}

RraError::RraError(std::string msg, RMA2_Nodeid node, RMA2_NLA address)
    : RmaError(msg),
    node(node), address(address) {}

FailedToRead::FailedToRead(RMA2_Nodeid node, RMA2_NLA address)
    : RraError("Failed to read!", node, address) {}

FailedToWrite::FailedToWrite(RMA2_Nodeid node, RMA2_NLA address)
    : RraError("Failed to write!", node, address) {}
