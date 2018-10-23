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

NodeHasNoHicann::NodeHasNoHicann(RMA2_Nodeid node)
    : ConnectionFailed("Connection to HICANN failed, because node has not HICANNs"),
    node(node) {}

JtagIrShiftFailed::JtagIrShiftFailed(RMA2_Nodeid node, uint8_t pattern)
    : std::runtime_error("JTAG IR shift failed"), node(node), pattern(pattern) {}
