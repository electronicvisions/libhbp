#include <hicann.h>

#include <bitset>
#include <iostream>
#include <utility/watch.h>

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
    : RegisterFile(connection), number(number) {}

void Hicann::write(uint16_t address, uint32_t value)
{
    Endpoint::Connection& rma = connection.rma;

    Config payload;
    payload.data.value = value;
    payload.data.address = address;
    payload.data.write = true;
    payload.data.tag = false;
    payload.data.hicann = number;

    // std::cout << "bits: " << std::bitset<64>(payload.raw) << "\n";

    {
        //WATCH_STATUS
        //WATCH_ERRORS

        rma2_post_immediate_put(rma.port, rma.handle, 8, payload.raw, CONFIG_ADDRESS, RMA2_COMPLETER_NOTIFICATION, RMA2_CMD_DEFAULT);
        wait_for_rma_notification();
    }
}


uint32_t Hicann::read(uint16_t address)
{
    Endpoint::Connection& rma = connection.rma;

    Config payload;
    payload.data.address = address;
    payload.data.read = false;
    payload.data.tag = false;
    payload.data.hicann = number;

    {
        //WATCH_STATUS
        //WATCH_ERRORS

        rma2_post_immediate_put(rma.port, rma.handle, 8, payload.raw, CONFIG_ADDRESS, RMA2_COMPLETER_NOTIFICATION, RMA2_CMD_DEFAULT);
        wait_for_rma_notification();
    }

    usleep(10000);

    return uint32_t(connection.hicann_config[0]);
}

void Hicann::clear(PhysicalBuffer& p, size_t amount)
{
    if (amount == 0 || amount > p.size())
    {
        amount = p.size();
    }

    for (size_t i = 0; i < amount; ++i)
    {
        p[i] = 0xdeadbeef;
    }
}

void Hicann::diff(PhysicalBuffer& p, size_t amount)
{
    if (amount == 0 || amount > p.size())
    {
        amount = p.size();
    }

    size_t unchanged = 0;
    for (size_t i = 0; i < amount; ++i)
    {
        auto v = p[i];
        if (v != 0xdeadbeef)
        {
            if (unchanged != 0)
            {
                std::cout << "unchanged: " << unchanged << "/" << amount << "\n";
                unchanged = 0;
            }
            std::cout << i << ": " << v << "\n";
        }
        else
        {
            ++unchanged;
        }
    }
    if (unchanged != 0)
    {
        std::cout << "unchanged: " << unchanged << "/" << amount << "\n";
    }
}

void Hicann::clear_all()
{
    clear(connection.gp_buffer);
    clear(connection.hicann_config);
    clear(connection.trace_data);
}

void Hicann::diff_all()
{
    diff(connection.gp_buffer);
    diff(connection.hicann_config);
    diff(connection.trace_data);
}
