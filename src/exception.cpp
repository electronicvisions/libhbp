#include <extoll/exception.h>

#include <utility>

using namespace extoll::library;

NodeIsNoFpga::NodeIsNoFpga(RMA2_Nodeid n, uint32_t d)
    : ConnectionFailed("Connection to FPGA failed, because node is not an FPGA!"),
    node(n), driver(d) {}

RraError::RraError(std::string msg, RMA2_Nodeid n, RMA2_NLA a)
    : RmaError(msg),
    node(n), address(a) {}

FailedToRead::FailedToRead(RMA2_Nodeid n, RMA2_NLA a)
    : RraError("Failed to read!", n, a) {}

FailedToWrite::FailedToWrite(RMA2_Nodeid n, RMA2_NLA a)
    : RraError("Failed to write!", n, a) {}

NodeHasNoHicann::NodeHasNoHicann(RMA2_Nodeid n)
    : ConnectionFailed("Connection to HICANN failed, because node has no HICANNs"),
    node(n) {}

JtagIrShiftFailed::JtagIrShiftFailed(RMA2_Nodeid n, uint8_t p)
    : std::runtime_error("JTAG IR shift failed"), node(n), pattern(p) {}

FailedToRegisterRegion::FailedToRegisterRegion()
    : RmaError("Failed to register region") {}

HicannResponseTimedOut::HicannResponseTimedOut()
    : RmaError("Hicann response timed out") {}
