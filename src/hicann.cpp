#include <extoll/hicann.h>

#include <bitset>
#include <iostream>

using namespace extoll::library;

union Config
{
    struct
    {
        uint64_t value : 32;
        uint64_t address : 15;
        bool read : 1;
        bool write : 1;
        bool tag : 1;
        uint64_t : 10;
        uint64_t hicann : 3;

    } data;
    uint64_t raw = 0;
};

static_assert(sizeof(Config) == 8, "Alignment error!");

Hicann::Hicann(Endpoint& connection, uint8_t number)
    : RegisterFile(connection), _number(number) {}

void Hicann::write(uint16_t address, uint32_t value)
{
    Endpoint::Connection& rma = _connection.rma;

    Config payload;
    payload.data.value = value;
    payload.data.address = address & 0x7fffu;
    payload.data.write = true;
    payload.data.tag = false;
    payload.data.hicann = _number & 7u;

    rma2_post_immediate_put(rma.port, rma.handle, 8, payload.raw, CONFIG_ADDRESS, RMA2_COMPLETER_NOTIFICATION, RMA2_CMD_DEFAULT);
    wait_for_rma_notification();
}

void Hicann::send(uint64_t data)
{
    auto& rma = _connection.rma;

    rma2_post_immediate_put(rma.port, rma.handle, 8, data, CONFIG_ADDRESS, RMA2_COMPLETER_NOTIFICATION, RMA2_CMD_DEFAULT);

    wait_for_rma_notification();
}


uint32_t Hicann::read(uint16_t address)
{
    Endpoint::Connection& rma = _connection.rma;

    Config payload;
    payload.data.address = address & 0x7fffu;
    payload.data.read = false;
    payload.data.tag = false;
    payload.data.hicann = _number & 7u;

    {
        //WATCH_STATUS
        //WATCH_ERRORS

        rma2_post_immediate_put(rma.port, rma.handle, 8, payload.raw, CONFIG_ADDRESS, RMA2_COMPLETER_NOTIFICATION, RMA2_CMD_DEFAULT);
        wait_for_rma_notification();
    }

    usleep(10000);

    return uint32_t(_connection.hicann_config[0]);
}

uint64_t Hicann::receive()
{
    // TODO: look up in the ringbuffer
    // TODO: wait for notifications

    return _connection.hicann_config[0];
}
