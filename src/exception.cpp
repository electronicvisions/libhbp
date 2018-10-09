#include <exception.h>

#include <utility>

NodeIsNoFcp::NodeIsNoFcp(RMA2_Nodeid node, uint32_t driver)
    : ConnectionFailed("Connection to PCB failed, because node is not a PCB!"),
    node(node), driver(driver) {}

RraError::RraError(std::string msg, RMA2_Nodeid node, RMA2_NLA address)
    : RmaError(msg),
    node(node), address(address) {}

FailedToRead::FailedToRead(RMA2_Nodeid node, RMA2_NLA address)
    : RraError("Failed to read!", node, address) {}

FailedToWrite::FailedToWrite(RMA2_Nodeid node, RMA2_NLA address)
    : RraError("Failed to write!", node, address) {}
