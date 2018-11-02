#include <extoll.h>

#include <iostream>
#include <sstream>

#include <rma.h>
#include <exception.h>
#include <cassert>

Endpoint& Extoll::connect(RMA2_Nodeid node)
{
    auto it = connections.find(node);

    if (it == connections.end())
    {
        connections.emplace(
                std::piecewise_construct,
                std::make_tuple(node),
                std::make_tuple(node)
                );
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
