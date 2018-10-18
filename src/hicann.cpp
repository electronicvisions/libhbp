#include <hicann.h>

#include <bitset>
#include <iostream>
#include <utility/watch.h>

union Config
{
    struct
    {
        uint64_t value : 32;
        uint64_t address : 15;
        bool read : 1;
        bool write : 1;
        bool tag : 1;
        uint64_t : 9;
        uint64_t hicann : 3;

    } data;
    uint64_t raw = 0;
};

static_assert(sizeof(Config) == 8, "Alignment error!");

Hicann::Hicann(Endpoint& connection)
    : RegisterFile(connection) {}

void Hicann::write(uint16_t address, uint32_t value)
{
    Endpoint::Connection& rma = connection.rma;

    Config payload;
    payload.data.value = value;
    payload.data.address = address;
    payload.data.write = true;
    payload.data.tag = true;
    payload.data.hicann = 1;

    std::cout << "bits: " << std::bitset<64>(payload.raw) << "\n";

    {
        WATCH_STATUS
        WATCH_ERRORS

        rma2_post_immediate_put(rma.port, rma.handle, 8, payload.raw, CONFIG_ADDRESS, RMA2_COMPLETER_NOTIFICATION, RMA2_CMD_DEFAULT);
        wait_for_rma_notification();
    }
}

uint32_t Hicann::read(uint16_t address)
{
    Endpoint::Connection& rma = connection.rma;

    Config payload;
    payload.data.address = address;
    payload.data.read = true;
    payload.data.tag = true;
    payload.data.hicann = 1;

    {
        WATCH_STATUS
        WATCH_ERRORS

        rma2_post_immediate_put(rma.port, rma.handle, 8, payload.raw, CONFIG_ADDRESS, RMA2_COMPLETER_NOTIFICATION, RMA2_CMD_DEFAULT);
        wait_for_rma_notification();
    }

    usleep(1000000);

    for (size_t i = 0; i < connection.hicann_config.byte_size(); ++i)
    {
        auto v = connection.hicann_config.data()[i];
        if (v == 42)
        {
            std::cout << i << ": " << connection.hicann_config.data()[i] << "\n";
        }

    }

    return uint32_t(connection.hicann_config.data()[0]);
}
