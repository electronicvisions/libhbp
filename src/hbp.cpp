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

RegisterFile HBP::rra(RMA2_Nodeid node)
{
    return RegisterFile{connect(node)};
}

JTag HBP::jtag(RMA2_Nodeid node)
{
    return JTag{connect(node)};
}

void HBP::configure_partner_host_for(RMA2_Nodeid node)
{
    auto rf = rra(node);
    auto& connection = connect(node);

    std::array<uint64_t, 8> config = {0, 0, 0, 0, 0, 0, 0, 0};

    config[0] = rma2_get_nodeid(connection.port)
            | (connection.vpid << 16ull)
            | (0ull << 32ull)
            | ((1ull << 2ull) << 48ull);
    config[1] = connection.trace_data.address();
    config[2] = connection.trace_data.byte_size()
            | (1ull << 48ull);
    config[3] = connection.gp_buffer.address() + 512;
    config[4] = connection.hicann_config.address();
    config[5] = connection.hicann_config.byte_size()
            | (1ull << 48ull);
    config[6] = 125000
            | ((1024ull * 4ull / 512ull - 5ull) << 32ull);
    config[7] = 124000
            | ((1024ull * 4ull / 512ull - 5ull) << 32ull);

    for (size_t i = 0; i < 8; ++i)
    {
        RMA2_NLA address = 0x1090 + i * 8;
        rf.set_noblock(config[i], address);
    }

    for (size_t i = 0; i < 8; ++i)
    {
        rf.wait_for_notification();
    }
}





