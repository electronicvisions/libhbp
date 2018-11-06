#include <buffer.h>

#include <iostream>
#include <cassert>

#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <pmap.h>
#include <unistd.h>

#include <exception.h>

using namespace extoll::library;

PhysicalBuffer::PhysicalBuffer(RMA2_Port port, size_t pages)
    : port(port), _data(pages * 1024 * 4 / sizeof(uint64_t))
{
    assert((pages > 0) && (pages <= 1000));

    if (rma2_register(port, _data.data(), _data.size() * sizeof(uint64_t), &_region) != RMA2_SUCCESS)
    {
        throw FailedToRegisterRegion();
    }
}

PhysicalBuffer::~PhysicalBuffer()
{
    rma2_unregister(port, _region);
}

RMA2_Region* PhysicalBuffer::region()
{
    return _region;
}

uint64_t PhysicalBuffer::operator[](size_t position) const
{
    return _data[position];
}

uint64_t& PhysicalBuffer::operator[](size_t position)
{
    return _data[position];
}

size_t PhysicalBuffer::size() const
{
    return _data.size();
}

RMA2_NLA PhysicalBuffer::address(size_t offset) const
{
    RMA2_NLA nla;
    rma2_get_nla(_region, offset, &nla);
    return nla;
}

uint32_t PhysicalBuffer::byte_size() const
{
    return uint32_t(size() / sizeof(uint64_t));
}
