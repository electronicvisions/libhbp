#ifndef LIBHBP_CPP_PHYSICAL_BUFFER_H
#define LIBHBP_CPP_PHYSICAL_BUFFER_H

#include <cinttypes>
#include <vector>

#include <extoll/rma.h>

namespace extoll {
namespace library {

//! \brief A user-space buffer registered with the Rma driver.
//!
//! This class is barely exposed to the user
class PhysicalBuffer
{
protected:
    //! the network port
    RMA2_Port _port = nullptr;
    //! the user-space buffer
    std::vector<uint64_t> _data{};
    //! the registered memory region with the driver
    RMA2_Region* _region = nullptr;

public:
    //! Creates a buffer from an Rma port and the number of pages (4kB)
    explicit PhysicalBuffer(RMA2_Port port, size_t pages);
    //! Unregisteres the region and frees the memory
    ~PhysicalBuffer();

    //! This class is not copyable
    PhysicalBuffer(const PhysicalBuffer&) = delete;
    //! This class is not copy-assignable
    PhysicalBuffer& operator=(const PhysicalBuffer&) = delete;

    //! The capacity of the buffer in quad words
    size_t capacity() const;
    //! The capacity of the buffer in bytes
    uint32_t byte_size() const;
    //! Accessor for the memory region
    RMA2_Region* region();
    //! The logical address of the mapped memory region with an optional offset in bytes
    RMA2_NLA address(size_t=0) const;

    //! Reads the buffer at a position
    uint64_t operator[](size_t position) const;
    //! Writes to the buffer at a position
    uint64_t& operator[](size_t position);

    //! Reads from the buffer at a position
    template <typename T>
    T at(size_t position) const
    {
        return static_cast<T>(_data[position]);
    }
};

//! \brief A specialized memory region that acts like a ringbuffer
//!
//! This class is synchronized with the ringbuffer on the remote Fpga.
class RingBuffer : public PhysicalBuffer
{
    size_t read_index = 0;
    size_t readable_words = 0;
    size_t read_words = 0;
    RMA2_Handle _handle = nullptr;
    uint64_t _type = 0;

    bool receive(bool throw_on_timeout);
public:
    //! Creates a ringbuffer from an Rma network port and handle, the number of pages and the payload type to expect
    RingBuffer(RMA2_Port port, RMA2_Handle handle, size_t pages, uint16_t type);
    //! Frees all resources and does a last sync with the remote Fpga
    ~RingBuffer();

    //! Blocks and reads one quad word from the buffer
    uint64_t get();
    //! \brief Notifies the hardware about how many bytes were read
    //!
    //! This method is also called internally after a certain amount of read quad words
    void notify();
    //! Simulates reading all quad words in the buffer and discards the packets
    void clear();
    //! Does a hard reset without notifying the hardware.
    void reset();

    //! The number of quad words that have not been read yet.
    size_t size() const;
};

}}

#endif //LIBHBP_CPP_PHYSICAL_BUFFER_H
