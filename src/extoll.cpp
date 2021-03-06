#include <extoll/extoll.h>

#include <cassert>
#include <iostream>
#include <sstream>

#include <extoll/exception.h>
#include <extoll/rma.h>

using namespace extoll::library;

Endpoint& Extoll::connect(RMA2_Nodeid node)
{
	auto it = connections.find(node);

	if (it == connections.end()) {
		connections.emplace(std::piecewise_construct, std::make_tuple(node), std::make_tuple(node));
	}

	return connections.find(node)->second;
}

RegisterFile Extoll::register_file(RMA2_Nodeid node)
{
	return RegisterFile{connect(node)};
}

JTag Extoll::jtag(RMA2_Nodeid node)
{
	return JTag{connect(node)};
}

Fpga Extoll::fpga(RMA2_Nodeid node)
{
	return Fpga{connect(node)};
}

Hicann Extoll::hicann(RMA2_Nodeid node, int8_t number)
{
	assert(number >= 0 && number <= 7);

	return Hicann{connect(node), uint8_t(number)};
}

RingBuffer& Extoll::hicann_config(RMA2_Nodeid node)
{
	return connect(node).hicann_config;
}

RingBuffer& Extoll::trace_pulse(RMA2_Nodeid node)
{
	return connect(node).trace_data;
}


std::unique_ptr<Extoll> Extoll::instance = nullptr;

Extoll& Extoll::Instance()
{
	if (!instance) {
		// C++11 does not have std::make_unique
		instance.reset(new Extoll());
	}

	return *instance;
}
