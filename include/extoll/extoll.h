#ifndef LIBHBP_CPP_HBP_H
#define LIBHBP_CPP_HBP_H

#include <cstdint>
#include <map>
#include <memory>
#include <vector>

#include <extoll/connection.h>
#include <extoll/fpga.h>
#include <extoll/hicann.h>
#include <extoll/jtag.h>
#include <extoll/register_file.h>
#include <extoll/rf_definitions.h>
#include <extoll/rma.h>

namespace extoll {
namespace library {

//! The connection pool that cashes all connections and provides access to all common functionality.
//! This class keeps a map of all open connections indexed by the remote node id.
//! Like this connections can be re-used across all hardware interfaces.
//! Furthermore, the class provides factory functions for the most common functionality:
//! - register file access with `register_file`
//! - Jtag access with `jtag`
//! - higher-level Fpga access with `fpga`
//! - higher-level Hicann access with `hicann`
//! - buffer access with `hicann_config` and `trace_pulse`
//!
//! Note, that all connections obtained through this object are only valid until this
//! object is deleted. Using any connection after the deletion is undefined behavior.
class Extoll
{
private:
	std::map<RMA2_Nodeid, Endpoint> connections;

	static std::unique_ptr<Extoll> instance;

public:
	//! Creates a new register file access object (RegisterFile).
	//! Using the object after the parent Extoll object was deleted is undefined behavior
	//! \throws ConnectionFailed if there is an error inside `librma2`
	//! \throws NodeIsNoFpga if the remote node is not an HBP communication Fpga
	RegisterFile register_file(RMA2_Nodeid node);
	//! Creates a new jtag access object (JTag).
	//! Using the object after the parent Extoll object was deleted is undefined behavior
	//! \throws ConnectionFailed if there is an error inside `librma2`
	//! \throws NodeIsNoFpga if the remote node is not an HBP communication Fpga
	//! \throws NodeHasNoHicann if the Fpga is not connected to any Hicann
	JTag jtag(RMA2_Nodeid node);
	//! Creates a new Fpga access object (Fpga).
	//! Using the object after the parent Extoll object was deleted is undefined behavior
	//! \throws ConnectionFailed if there is an error inside `librma2`
	//! \throws NodeIsNoFpga if the remote node is not an HBP communication Fpga
	Fpga fpga(RMA2_Nodeid node);
	//! Creates a new Hicann access object (Hicann).
	//! Using the object after the parent Extoll object was deleted is undefined behavior
	//! \throws ConnectionFailed if there is an error inside `librma2`
	//! \throws NodeIsNoFpga if the remote node is not an HBP communication Fpga
	Hicann hicann(RMA2_Nodeid node, int8_t number);
	//! A reference to the Hicann config ringbuffer.
	//! Using the object after the parent Extoll object was deleted is undefined behavior
	//! \throws ConnectionFailed if there is an error inside `librma2`
	//! \throws NodeIsNoFpga if the remote node is not an HBP communication Fpga
	RingBuffer& hicann_config(RMA2_Nodeid node);
	//! A reference to the Trace-Pulse data ringbuffer.
	//! Using the object after the parent Extoll object was deleted is undefined behavior
	//! \throws ConnectionFailed if there is an error inside `librma2`
	//! \throws NodeIsNoFpga if the remote node is not an HBP communication Fpga
	RingBuffer& trace_pulse(RMA2_Nodeid node);
	//! Connect to a remote Extoll node based on its node id.
	//! The connection may be cashed.
	//! Using the object after the parent Extoll object was deleted is undefined behavior
	//! \throws ConnectionFailed if there is an error inside `librma2`
	//! \throws NodeIsNoFpga if the remote node is not an HBP communication Fpga
	Endpoint& connect(RMA2_Nodeid node);

	//! A reference to the globals Extoll object.
	//! This global object should be preferred over creating many local
	//! Extoll objects since connections are not reused across different instances
	//! of this class and the tear-down is very expensive (time-wise).
	static Extoll& Instance();

	//! The magic payload type constant identifying Hicann config packets
	const static uint16_t HICANN_CONFIG = uint16_t(rf::TestControlType::HicannConfig);
	//! The magic payload type constant identifying Trace-Pulse data packets
	const static uint16_t TRACE_PULSE = uint16_t(rf::TestControlType::TracePulse);

private:
	friend class RegisterFile;
};

}
}

#endif // LIBHBP_CPP_HBP_H
