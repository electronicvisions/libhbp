#ifndef LIBHBP_CPP_PHYSICAL_BUFFER_H
#define LIBHBP_CPP_PHYSICAL_BUFFER_H

#include <cinttypes>

#include <rma.h>

class PhysicalBuffer
{
    uint32_t _byte_size;
    uint64_t* _data;
    RMA2_NLA _address;
    int file_descriptor;

public:
    explicit PhysicalBuffer(int pages);
    ~PhysicalBuffer();

    RMA2_NLA address() const;
    const uint64_t* data() const;
    uint64_t* data();
    uint32_t byte_size() const;
};

#endif //LIBHBP_CPP_PHYSICAL_BUFFER_H
