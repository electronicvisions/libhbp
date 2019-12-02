#include <extoll/buffer.h>

#include <iostream>
#include <cassert>

#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <pmap.h>
#include <unistd.h>

#include <extoll/exception.h>
#include <extoll/extoll.h>

using namespace extoll::library;

PhysicalBuffer::PhysicalBuffer(RMA2_Port port, size_t pages)
    : _port(port), _data(pages * 1024 * 4 / sizeof(uint64_t))
{
    assert((pages > 0) && (pages <= 1000));

    if (rma2_register(_port, _data.data(), _data.size() * sizeof(uint64_t), &_region) != RMA2_SUCCESS)
    {
        throw FailedToRegisterRegion();
    }
}

PhysicalBuffer::~PhysicalBuffer()
{
    rma2_unregister(_port, _region);
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

size_t PhysicalBuffer::capacity() const
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
    return uint32_t(capacity() * sizeof(uint64_t));
}

RingBuffer::RingBuffer(RMA2_Port port, RMA2_Handle handle, size_t pages, uint16_t type)
    : PhysicalBuffer(port, pages), _handle(handle), _type(type)
{

}

uint64_t RingBuffer::get()
{
    while (readable_words == 0)
    {
        receive(true);
    }
    read_index %= capacity();
    uint64_t read = _data[read_index++];
    ++read_words;
    --readable_words;

    if (read_words > 10)
    {
        notify();
    }
    return read;
}

void RingBuffer::notify()
{
    while (read_words > 0)
    {
        auto  words_to_notify = std::min(read_words, 0x1ffffffful);

        uint64_t payload = (_type << 48u) | words_to_notify;
        rma2_post_notification(_port, _handle, 0, payload, RMA2_NO_NOTIFICATION, RMA2_CMD_DEFAULT);

        read_words -= words_to_notify;
    }
}

RingBuffer::~RingBuffer()
{
    clear();
    notify();

    if (readable_words)
    {
        std::cerr << "Ignored Payload Notification with count=" << std::dec << readable_words << "\n";
    }
}

size_t RingBuffer::size() const
{
    return readable_words;
}

void RingBuffer::clear()
{
    while (receive(false));

    read_index += readable_words;
    readable_words = 0;

}

bool RingBuffer::receive(bool throw_on_timeout)
{
    RMA2_Notification* notification;
    RMA2_Class cls = (_type >> 4) & 0xff;

    for (unsigned int sleep = 1; sleep < 100000; sleep *= 10)
    {        
        if (rma2_noti_noti_match(_port, cls, RMA2_NODEID_ANY, RMA2_VPID_ANY, &notification) == RMA2_SUCCESS)
        {
            uint64_t payload = rma2_noti_get_notiput_payload(notification);
            uint16_t actual_cls = rma2_noti_get_notiput_class(notification);
            rma2_noti_free(_port, notification);
            readable_words += payload & 0xffffffff;

            std::cout << "got notification " << std::dec << (payload & 0xffffffff) << " " << std::hex << uint16_t(cls) <<
            "#" << _type << "\n";
            std::cout << "actual notification class: " << std::hex << actual_cls << "\n";
            return true;
        }
        usleep(sleep);
    }

    if (throw_on_timeout)
    {
        throw HicannResponseTimedOut();
    }
    return false;
}

void RingBuffer::reset()
{
    read_index = 0;
    readable_words = 0;
    read_words = 0;
}

