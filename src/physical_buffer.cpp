#include <physical_buffer.h>

#include <iostream>

#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <pmap.h>
#include <unistd.h>

#include <exception.h>

PhysicalBuffer::PhysicalBuffer(int pages)
{
    if (pages <= 0 || pages > 1000)
    {
        throw BufferError("Failed to create physical buffer. Incorrect page count.");
    }
    _byte_size = uint32_t(pages) * 1024 * 4;

    file_descriptor = open("/dev/extoll/pmap", O_RDWR);
    if (file_descriptor < 0)
    {
        throw BufferError("Failed to open extoll pmap file. (Are you root?)");
    }

    int result = ioctl(file_descriptor, PMAP_IOCTL_SET_TYPE, 0);
    if (result < 0)
    {
        close(file_descriptor);
        throw BufferError("Failed to set kernel managed type.");
    }

    result = ioctl(file_descriptor, PMAP_IOCTL_SET_SIZE, _byte_size);
    if (result < 0)
    {
        close(file_descriptor);
        throw BufferError("Failed to set memory size.");
    }

    _data = reinterpret_cast<uint64_t*>(mmap(nullptr, _byte_size, PROT_READ | PROT_WRITE, MAP_SHARED, file_descriptor, 0));
    if (_data == MAP_FAILED || _data == nullptr)
    {
        close(file_descriptor);
        throw BufferError("Failed to memory map file.");
    }

    result = ioctl(file_descriptor, PMAP_IOCTL_GET_PADDR, &_address);
    if (result < 0)
    {
        munmap(_data, _byte_size);
        close(file_descriptor);
        throw BufferError("Failed to get physical address.");
    }
}

PhysicalBuffer::~PhysicalBuffer()
{
    if (_data != nullptr && _data != MAP_FAILED)
    {
        munmap(_data, _byte_size);
    }
    if (file_descriptor != 0)
    {
        close(file_descriptor);
    }
}

RMA2_NLA PhysicalBuffer::address() const
{
    return _address;
}

const uint64_t* PhysicalBuffer::data() const
{
    return _data;
}

uint64_t* PhysicalBuffer::data()
{
    return _data;
}

uint32_t PhysicalBuffer::byte_size() const
{
    return _byte_size;
}
