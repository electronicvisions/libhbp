#include <array>
#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <pmap.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <cassert>

#include <extoll/rma.h>

void check(RMA2_ERROR status, const char* code)
{
    if (status != RMA2_SUCCESS)
    {
        char buffer[512];
        rma2_serror(status, buffer, sizeof buffer);
        std::cerr << code << " -> " << buffer << "\n";
        exit(1);
    }
}

void check_fd(int status, const char* code)
{
    if (status < 0)
    {
        std::cerr << code << " -> " << status << "\n";
        exit(1);
    }
}

#define CHECK(x) check(x, #x)

void block(RMA2_Port port)
{
    RMA2_Notification* notification;
    CHECK(rma2_noti_get_block(port, &notification));
    rma2_noti_dump(notification);
    CHECK(rma2_noti_free(port, notification));
}


struct Connection
{
    RMA2_Port port;
    RMA2_Handle handle;
};

Connection setup()
{
    RMA2_Port port;
    CHECK(rma2_open(&port));
    RMA2_Handle handle;
    auto virtual_process_id = rma2_get_vpid(port);
    CHECK(rma2_connect(port, 3, virtual_process_id, RMA2_CONN_RRA, &handle));

    return {port, handle};
}

void teardown(Connection c)
{

    CHECK(rma2_disconnect(c.port, c.handle));
    CHECK(rma2_close(c.port));
}

void virtual_memory(Connection c)
{
    auto buffer = new uint64_t[1024];
    for (int i = 0; i < 1024; ++i)
    {
        buffer[i] = 0xdead;
    }

    RMA2_Region* region;
    CHECK(rma2_register(c.port, buffer, 4096, &region));
    RMA2_NLA nla;
    CHECK(rma2_get_nla(region, 0, &nla));

    std::cout << "Address: " << std::hex << nla << "\n";
    CHECK(rma2_post_get_qw(c.port, c.handle, region, 0, 8, 0x8000, RMA2_ALL_NOTIFICATIONS, RMA2_CMD_DEFAULT));

    block(c.port);
    block(c.port);
    block(c.port);

    usleep(1000000);
 
    std::cout << "Buffer: 0x" << std::hex << buffer[0] << "\n";
    for (int i = 0; i < 1024; ++i)
    {
        if (buffer[i] == 0xcafebabe)
        {
            std::cout << i << ": " << buffer[i] << "\n";
        }
    }
    CHECK(rma2_unregister(c.port, region));
}

#define CHECK_FD(x) check_fd(x, #x)


void physical_memory(Connection c)
{
    auto fd = open("/dev/extoll/pmap", O_RDWR);
    CHECK_FD(fd);

    CHECK_FD(ioctl(fd, PMAP_IOCTL_SET_TYPE, 0));
    CHECK_FD(ioctl(fd, PMAP_IOCTL_SET_SIZE, 4096));

    auto buffer = static_cast<uint64_t*>(mmap(nullptr, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));

    if (reinterpret_cast<std::intptr_t>(buffer) == -1)
    {
        std::cerr << "mmap failed\n";
        exit(1);
    }

    RMA2_NLA nla;
    CHECK_FD(ioctl(fd, PMAP_IOCTL_GET_PADDR, &nla));
    std::cout << "Address: " << std::hex << nla << "\n";

    CHECK(rma2_post_get_qw_direct(c.port, c.handle, nla, 8, 0x8000, RMA2_ALL_NOTIFICATIONS, RMA2_CMD_DEFAULT));

    block(c.port);
    block(c.port);
    block(c.port);

    std::cout << "Buffer: 0x" << std::hex << buffer[0] << "\n";

}


int main(int argc, char** argv)
{
    bool physical = false;
    bool virtual_ = false;

    for (int i = 1; i < argc; ++i)
    {
        if (argv[i][0] == 'p')
        {
            physical = true;
        }
        else if (argv[i][0] == 'v')
        {
            virtual_ = true;
        }
    }

    Connection connection = setup();

    if (virtual_)
    {
        std::cout << "\nVirtual Memory:\n";
        std::cout << "===============\n";

        virtual_memory(connection);
    }

    if (physical)
    {
        std::cout << "\nPhysical Memory:\n";
        std::cout << "================\n";

        physical_memory(connection);
    }

    teardown(connection);
}
