#ifndef LIBHBP_CPP_FPGA_H
#define LIBHBP_CPP_FPGA_H

#include <extoll/register_file.h>

namespace extoll {
namespace library {


//! All configuration values for the partner host configuration.
//! A default set of configuration values can be obtained from
//! Fpga::default_partner_host_parameters
//! Changing these values can lead to misconfiguration of the remote Fpga
struct PartnerHostConfiguration
{
	//! The node id of the local extoll node
	RMA2_Nodeid local_node;
	//! The protection domain id (currently not used)
	uint16_t protection_domain_id;
	//! The virtual process id of the communication
	RMA2_VPID vpid;
	//! The Rra mode (currently only the bit at index 2 is used to indicate translation enabled)
	uint8_t mode;

	//! The network logical address of the Fpga config response buffer
	uint64_t config_put_address;

	//! Configuration values concerning the ring-buffers
	struct Ringbuffer
	{
		//! The start address of the memory region
		uint64_t start_address;
		//! The capacity in bytes
		uint32_t capacity;
		//! The threshold that determines the "nearly full" state on the Fpga
		uint32_t threshold;
		//! A flag whether to reset the internal counters (default is false)
		bool reset_counter;

		//! the timeout until a notification is send in cycles (default is 200)
		uint32_t timeout;
		//! the number of packets sent until a notification is sent
		uint32_t frequency;
	};

	//! The ringbuffer configuration for the Trace-Pulse data ringbuffer
	Ringbuffer trace;
	//! The ringbuffer configuration for the Hicann config ringbuffer
	Ringbuffer hicann;
};

//! This class provides a low-level interface for sending Fpga config packets.
//! This class should be instantiated through the factory functions in Extoll
class Fpga : protected RegisterFile
{
	const static RMA2_NLA CONFIG_ADDRESS = 0x0c1bull << 48ull;

public:
	//! Flags for all modules that can be reset on the Fpga
	enum class Reset : uint8_t
	{
		None = 0,                            //! Clears all reset bits
		Core = 1,                            //! Resets the core logic
		Hicann = 2,                          //! Resets the Hicanns
		Arq = 4,                             //! Resets the AutomaticResponseRequester
		PulseMem = 8,                        //! Resets the pulse memory RAM
		All = Core | Hicann | Arq | PulseMem //! Sets all reset bits
	};

	//! The Fpga config commands flags
	enum class Config : uint64_t
	{
		//! Do nothing
		None = 0,
		//! Clear the playback memory RAM
		ClearPlaybackMemory = 0x80000000,
		//! Clear the trace-pulse memory RAM
		ClearTraceMemory = 0x40000000,
		//! Start the experiment
		StartExperiment = 0x20000000,
		//! Start recording trace-pulse data
		StartTrace = 0x10000000,
		//! Stop recording trace-pulse data
		StopTrace = 0x8000000,
		//! Application Specific (unknown)
		StartReadingTracedPulses = 0x4000000,
		//! Application Specific (unknown)
		StartReadingTracedConfigPackets = 0x2000000,
		//! Enable loopback mode for trace-pulse data
		FpgaPulseLoopback = 0x1000000,
		//! Application Specific (unknown)
		PlaybackTimestampReplacement = 0x800000,
		//! Indicates that the following two bits are valid
		ValidSystemTimeSettings = 0x400000,
		//! Starts the system time counter
		StartSystemTimeCounter = 0x200000,
		//! Synchronizes the timer globally
		GlobalModeForSystemTimeCounter = 0x100000,
		//! Application Specific (unknown)
		UseSstSql = 0x80000,
		All = 0xfff80000, //! Everything
	};

	using RegisterFile::RegisterFile;

	//! Sets all reset flags and unsets them again
	void reset(Reset = All);
	//! Only sets the reset flags.
	void reset_set_only(Reset = All);

	//! Create the default partner host configuration parameters.
	//! These parameters can be used with configure_partner_host
	PartnerHostConfiguration default_partner_host_parameters();
	//! Configure the partner host on the Fpga with default values
	void configure_partner_host();
	//! Configure the partner host on the Fpga with specific settings
	void configure_partner_host(const PartnerHostConfiguration&);

	//! Send a config packet
	uint64_t send(Config);
	//! Read the config response after a config packet has been send
	uint64_t config_response() const;

	//! Convenience alias
	const static Reset Core = Reset::Core;
	//! Convenience alias
	const static Reset Hicann = Reset::Hicann;
	//! Convenience alias
	const static Reset Arq = Reset::Arq;
	//! Convenience alias
	const static Reset All = Reset::All;
	//! Convenience alias
	const static Reset PulseMem = Reset::PulseMem;
	//! Convenience alias
	const static Reset None = Reset::None;
};

}
}

extoll::library::Fpga::Config operator|(
    extoll::library::Fpga::Config, extoll::library::Fpga::Config);
extoll::library::Fpga::Reset operator|(extoll::library::Fpga::Reset, extoll::library::Fpga::Reset);
bool operator&(extoll::library::Fpga::Config, extoll::library::Fpga::Config);
bool operator&(extoll::library::Fpga::Reset, extoll::library::Fpga::Reset);

#endif // LIBHBP_CPP_FPGA_H
