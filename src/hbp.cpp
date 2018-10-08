#include <hbp.h>

#include <iostream>
#include <sstream>

#include <rma.h>
#include <exception.h>

Connection& HBP::connect(RMA2_Nodeid node)
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

RegisterFile HBP::register_file(RMA2_Nodeid node)
{
    return RegisterFile{connect(node)};
}

JTag HBP::jtag(RMA2_Nodeid node)
{
    return JTag{connect(node)};
}

Fpga HBP::fpga(RMA2_Nodeid node)
{
    return Fpga{connect(node)};
}





