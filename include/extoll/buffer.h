#ifndef LIBHBP_CPP_PHYSICAL_BUFFER_H
#define LIBHBP_CPP_PHYSICAL_BUFFER_H

#include <cinttypes>
#include <vector>

#include <extoll/rma.h>

namespace extoll {
namespace library {

class PhysicalBuffer
{
protected:
    RMA2_Port _port = nullptr;
    std::vector<uint64_t> _data{};
    RMA2_Region* _region = nullptr;

public:
    explicit PhysicalBuffer(RMA2_Port port, size_t pages);
    ~PhysicalBuffer();

    PhysicalBuffer(const PhysicalBuffer&) = delete;
    PhysicalBuffer& operator=(const PhysicalBuffer&) = delete;

    size_t capacity() const;
    uint32_t byte_size() const;
    RMA2_Region* region();
    RMA2_NLA address(size_t=0) const;

    uint64_t operator[](size_t position) const;
    uint64_t& operator[](size_t position);

    template <typename T>
    T at(size_t position) const
    {
        return static_cast<T>(_data[position]);
    }
};

class RingBuffer : public PhysicalBuffer
{
    size_t read_index = 0;
    size_t readable_words = 0;
    size_t read_words = 0;
    RMA2_Handle _handle = nullptr;
    uint64_t _type = 0;

    bool receive(bool throw_on_timeout);
public:
    RingBuffer(RMA2_Port port, RMA2_Handle handle, size_t pages, uint16_t type);
    ~RingBuffer();

    uint64_t get();
    void notify();
    void clear();

    size_t size() const;
};

}}

#endif //LIBHBP_CPP_PHYSICAL_BUFFER_H
