#ifndef LIBHBP_CPP_PHYSICAL_BUFFER_H
#define LIBHBP_CPP_PHYSICAL_BUFFER_H

#include <cinttypes>
#include <vector>

#include <rma.h>

namespace extoll {
namespace library {

class PhysicalBuffer
{
    RMA2_Port port = nullptr;
    std::vector<uint64_t> _data{};
    RMA2_Region* _region = nullptr;

public:
    explicit PhysicalBuffer(RMA2_Port port, size_t pages);
    ~PhysicalBuffer();

    size_t size() const;
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

}}

#endif //LIBHBP_CPP_PHYSICAL_BUFFER_H
