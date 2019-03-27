#include <array>
#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <pmap.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

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
    else
    {
        // std::cout << code << "\n";
    }
}

void check_fd(int status, const char* code)
{
    if (status < 0)
    {
        std::cerr << code << " -> " << status << "\n";
        exit(1);
    }
    else
    {
        // std::cout << code << "\n";
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
    auto vpid = rma2_get_vpid(port);
    CHECK(rma2_connect(port, 2, vpid, RMA2_CONN_RRA, &handle));

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
    auto offset = 0x1000u - (nla & 0xfffu);
    CHECK(rma2_get_nla(region, offset, &nla));
    auto offset32 = uint32_t(offset);

    std::cout << "Address: " << std::hex << nla << "\n";
    //CHECK(rma2_post_get_qw_direct(c.port, c.handle, nla, 8, 0x8000, RMA2_COMPLETER_NOTIFICATION, RMA2_CMD_DEFAULT));
    CHECK(rma2_post_get_qw(c.port, c.handle, region, offset32, 8, 0x8000, RMA2_COMPLETER_NOTIFICATION, RMA2_CMD_DEFAULT));

    block(c.port);

    std::cout << "Buffer: 0x" << std::hex << buffer[0] << "\n";
    std::cout << "Buffer: 0x" << std::hex << buffer[offset / 8] << "\n";
    for (int i = 0; i < 1024; ++i)
    {
        if (buffer[i] != 0xdead)
        {
            std::cout << i << ": " << buffer[i] << "\n";
        }
    }
    CHECK(rma2_unregister(c.port, region));
}

#define CHECKFD(x) check_fd(x, #x);


void physical_memory(Connection c)
{
    auto fd = open("/dev/extoll/pmap", O_RDWR);
    CHECKFD(fd);

    CHECKFD(ioctl(fd, PMAP_IOCTL_SET_TYPE, 0));
    CHECKFD(ioctl(fd, PMAP_IOCTL_SET_SIZE, 4096));

    auto buffer = static_cast<uint64_t*>(mmap(nullptr, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));

    if (reinterpret_cast<std::intptr_t>(buffer) == -1)
    {
        std::cerr << "mmap failed\n";
        exit(1);
    }

    RMA2_NLA nla;
    CHECKFD(ioctl(fd, PMAP_IOCTL_GET_PADDR, &nla));
    std::cout << "Address: " << std::hex << nla << "\n";

    CHECK(rma2_post_get_qw_direct(c.port, c.handle, nla, 8, 0x8000, RMA2_COMPLETER_NOTIFICATION, RMA2_CMD_DEFAULT));

    block(c.port);

    std::cout << "Buffer: 0x" << std::hex << buffer[0] << "\n";

}


int main()
{
    Connection connection = setup();

    std::cout << "\nVirtual Memory:\n";
    std::cout << "===============\n";

    //virtual_memory(connection);

    std::cout << "\nPhysical Memory:\n";
    std::cout << "================\n";

    //physical_memory(connection);

    teardown(connection);
}