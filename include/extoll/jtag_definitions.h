/*
 * This is a generated file - do not change it
 * 2019-04-01 16:08:27.657832
 */

#pragma once

#include <cinttypes>

#include <extoll/rma.h>


namespace extoll {
namespace library {
namespace jtag {



//! Read-only register file ID at address 0x0
struct ID
{
    //! \brief The raw bits used to send and receive data to and from the hardware
    //!
    //! This member my be accessed directly.
    uint64_t raw = 0;

    //! Initialize with zero
    ID() = default;
    //! Initialize with a specific value
    explicit ID(uint64_t value) : raw(value) {};

    //! The Jtag command to access this register
    constexpr static RMA2_NLA ADDRESS = 0x0;
    //! Indicates whether this register can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this register can be written on the software side
    constexpr static bool WRITABLE = false;
    //! Indicates whether this register is a Jtag action
    constexpr static bool TRIGGER = false;
    //! The bit size of this register
    constexpr static uint64_t SIZE = 32;
    //! The mask used to cut off extraneous bits when reading from the Fpga
    constexpr static uint64_t MASK = 0xffffffff;
};


//! Read-only register file Systime at address 0xb
struct Systime
{
    //! \brief The raw bits used to send and receive data to and from the hardware
    //!
    //! This member my be accessed directly.
    uint64_t raw = 0;

    //! Initialize with zero
    Systime() = default;
    //! Initialize with a specific value
    explicit Systime(uint64_t value) : raw(value) {};

    //! The Jtag command to access this register
    constexpr static RMA2_NLA ADDRESS = 0xb;
    //! Indicates whether this register can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this register can be written on the software side
    constexpr static bool WRITABLE = false;
    //! Indicates whether this register is a Jtag action
    constexpr static bool TRIGGER = false;
    //! The bit size of this register
    constexpr static uint64_t SIZE = 15;
    //! The mask used to cut off extraneous bits when reading from the Fpga
    constexpr static uint64_t MASK = 0x7fff;
};


//! Read-only register file RxData at address 0x12
struct RxData
{
    //! \brief The raw bits used to send and receive data to and from the hardware
    //!
    //! This member my be accessed directly.
    uint64_t raw = 0;

    //! Initialize with zero
    RxData() = default;
    //! Initialize with a specific value
    explicit RxData(uint64_t value) : raw(value) {};

    //! The Jtag command to access this register
    constexpr static RMA2_NLA ADDRESS = 0x12;
    //! Indicates whether this register can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this register can be written on the software side
    constexpr static bool WRITABLE = false;
    //! Indicates whether this register is a Jtag action
    constexpr static bool TRIGGER = false;
    //! The bit size of this register
    constexpr static uint64_t SIZE = 64;
    //! The mask used to cut off extraneous bits when reading from the Fpga
    constexpr static uint64_t MASK = 0xffffffffffffffff;
};


//! Read-only register file Status at address 0x1a
struct Status
{
    //! \brief The raw bits used to send and receive data to and from the hardware
    //!
    //! This member my be accessed directly.
    uint64_t raw = 0;

    //! Initialize with zero
    Status() = default;
    //! Initialize with a specific value
    explicit Status(uint64_t value) : raw(value) {};

    //! The Jtag command to access this register
    constexpr static RMA2_NLA ADDRESS = 0x1a;
    //! Indicates whether this register can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this register can be written on the software side
    constexpr static bool WRITABLE = false;
    //! Indicates whether this register is a Jtag action
    constexpr static bool TRIGGER = false;
    //! The bit size of this register
    constexpr static uint64_t SIZE = 8;
    //! The mask used to cut off extraneous bits when reading from the Fpga
    constexpr static uint64_t MASK = 0xff;
};


//! Read-only register file CrcCount at address 0x27
struct CrcCount
{
    //! \brief The raw bits used to send and receive data to and from the hardware
    //!
    //! This member my be accessed directly.
    uint64_t raw = 0;

    //! Initialize with zero
    CrcCount() = default;
    //! Initialize with a specific value
    explicit CrcCount(uint64_t value) : raw(value) {};

    //! The Jtag command to access this register
    constexpr static RMA2_NLA ADDRESS = 0x27;
    //! Indicates whether this register can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this register can be written on the software side
    constexpr static bool WRITABLE = false;
    //! Indicates whether this register is a Jtag action
    constexpr static bool TRIGGER = false;
    //! The bit size of this register
    constexpr static uint64_t SIZE = 8;
    //! The mask used to cut off extraneous bits when reading from the Fpga
    constexpr static uint64_t MASK = 0xff;
};


//! Read-only register file ArqTxPckNum at address 0x31
struct ArqTxPckNum
{
    //! \brief The raw bits used to send and receive data to and from the hardware
    //!
    //! This member my be accessed directly.
    uint64_t raw = 0;

    //! Initialize with zero
    ArqTxPckNum() = default;
    //! Initialize with a specific value
    explicit ArqTxPckNum(uint64_t value) : raw(value) {};

    //! The Jtag command to access this register
    constexpr static RMA2_NLA ADDRESS = 0x31;
    //! Indicates whether this register can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this register can be written on the software side
    constexpr static bool WRITABLE = false;
    //! Indicates whether this register is a Jtag action
    constexpr static bool TRIGGER = false;
    //! The bit size of this register
    constexpr static uint64_t SIZE = 32;
    //! The mask used to cut off extraneous bits when reading from the Fpga
    constexpr static uint64_t MASK = 0xffffffff;
};


//! Read-only register file ArqRxPckNum at address 0x32
struct ArqRxPckNum
{
    //! \brief The raw bits used to send and receive data to and from the hardware
    //!
    //! This member my be accessed directly.
    uint64_t raw = 0;

    //! Initialize with zero
    ArqRxPckNum() = default;
    //! Initialize with a specific value
    explicit ArqRxPckNum(uint64_t value) : raw(value) {};

    //! The Jtag command to access this register
    constexpr static RMA2_NLA ADDRESS = 0x32;
    //! Indicates whether this register can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this register can be written on the software side
    constexpr static bool WRITABLE = false;
    //! Indicates whether this register is a Jtag action
    constexpr static bool TRIGGER = false;
    //! The bit size of this register
    constexpr static uint64_t SIZE = 32;
    //! The mask used to cut off extraneous bits when reading from the Fpga
    constexpr static uint64_t MASK = 0xffffffff;
};


//! Read-only register file ArqRxDropNum at address 0x33
struct ArqRxDropNum
{
    //! \brief The raw bits used to send and receive data to and from the hardware
    //!
    //! This member my be accessed directly.
    uint64_t raw = 0;

    //! Initialize with zero
    ArqRxDropNum() = default;
    //! Initialize with a specific value
    explicit ArqRxDropNum(uint64_t value) : raw(value) {};

    //! The Jtag command to access this register
    constexpr static RMA2_NLA ADDRESS = 0x33;
    //! Indicates whether this register can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this register can be written on the software side
    constexpr static bool WRITABLE = false;
    //! Indicates whether this register is a Jtag action
    constexpr static bool TRIGGER = false;
    //! The bit size of this register
    constexpr static uint64_t SIZE = 32;
    //! The mask used to cut off extraneous bits when reading from the Fpga
    constexpr static uint64_t MASK = 0xffffffff;
};


//! Read-only register file ArqTxTimeoutNum at address 0x36
struct ArqTxTimeoutNum
{
    //! \brief The raw bits used to send and receive data to and from the hardware
    //!
    //! This member my be accessed directly.
    uint64_t raw = 0;

    //! Initialize with zero
    ArqTxTimeoutNum() = default;
    //! Initialize with a specific value
    explicit ArqTxTimeoutNum(uint64_t value) : raw(value) {};

    //! The Jtag command to access this register
    constexpr static RMA2_NLA ADDRESS = 0x36;
    //! Indicates whether this register can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this register can be written on the software side
    constexpr static bool WRITABLE = false;
    //! Indicates whether this register is a Jtag action
    constexpr static bool TRIGGER = false;
    //! The bit size of this register
    constexpr static uint64_t SIZE = 32;
    //! The mask used to cut off extraneous bits when reading from the Fpga
    constexpr static uint64_t MASK = 0xffffffff;
};


//! Read-only register file ArqRxTimeoutNum at address 0x37
struct ArqRxTimeoutNum
{
    //! \brief The raw bits used to send and receive data to and from the hardware
    //!
    //! This member my be accessed directly.
    uint64_t raw = 0;

    //! Initialize with zero
    ArqRxTimeoutNum() = default;
    //! Initialize with a specific value
    explicit ArqRxTimeoutNum(uint64_t value) : raw(value) {};

    //! The Jtag command to access this register
    constexpr static RMA2_NLA ADDRESS = 0x37;
    //! Indicates whether this register can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this register can be written on the software side
    constexpr static bool WRITABLE = false;
    //! Indicates whether this register is a Jtag action
    constexpr static bool TRIGGER = false;
    //! The bit size of this register
    constexpr static uint64_t SIZE = 32;
    //! The mask used to cut off extraneous bits when reading from the Fpga
    constexpr static uint64_t MASK = 0xffffffff;
};


//! Write-only register file LvdsPadsEnable at address 0x2
struct LvdsPadsEnable
{
    //! \brief The raw bits used to send and receive data to and from the hardware
    //!
    //! This member my be accessed directly.
    uint64_t raw = 0;

    //! Initialize with zero
    LvdsPadsEnable() = default;
    //! Initialize with a specific value
    explicit LvdsPadsEnable(uint64_t value) : raw(value) {};

    //! The Jtag command to access this register
    constexpr static RMA2_NLA ADDRESS = 0x2;
    //! Indicates whether this register can be read on the software side
    constexpr static bool READABLE = false;
    //! Indicates whether this register can be written on the software side
    constexpr static bool WRITABLE = true;
    //! Indicates whether this register is a Jtag action
    constexpr static bool TRIGGER = false;
    //! The bit size of this register
    constexpr static uint64_t SIZE = 1;
    //! The mask used to cut off extraneous bits when reading from the Fpga
    constexpr static uint64_t MASK = 0x1;
};


//! Write-only register file LinkControl at address 0x3
struct LinkControl
{
    //! \brief The raw bits used to send and receive data to and from the hardware
    //!
    //! This member my be accessed directly.
    uint64_t raw = 0;

    //! Initialize with zero
    LinkControl() = default;
    //! Initialize with a specific value
    explicit LinkControl(uint64_t value) : raw(value) {};

    //! The Jtag command to access this register
    constexpr static RMA2_NLA ADDRESS = 0x3;
    //! Indicates whether this register can be read on the software side
    constexpr static bool READABLE = false;
    //! Indicates whether this register can be written on the software side
    constexpr static bool WRITABLE = true;
    //! Indicates whether this register is a Jtag action
    constexpr static bool TRIGGER = false;
    //! The bit size of this register
    constexpr static uint64_t SIZE = 9;
    //! The mask used to cut off extraneous bits when reading from the Fpga
    constexpr static uint64_t MASK = 0x1ff;
};


//! Write-only register file Layer1Mode at address 0x4
struct Layer1Mode
{
    //! \brief The raw bits used to send and receive data to and from the hardware
    //!
    //! This member my be accessed directly.
    uint64_t raw = 0;

    //! Initialize with zero
    Layer1Mode() = default;
    //! Initialize with a specific value
    explicit Layer1Mode(uint64_t value) : raw(value) {};

    //! The Jtag command to access this register
    constexpr static RMA2_NLA ADDRESS = 0x4;
    //! Indicates whether this register can be read on the software side
    constexpr static bool READABLE = false;
    //! Indicates whether this register can be written on the software side
    constexpr static bool WRITABLE = true;
    //! Indicates whether this register is a Jtag action
    constexpr static bool TRIGGER = false;
    //! The bit size of this register
    constexpr static uint64_t SIZE = 8;
    //! The mask used to cut off extraneous bits when reading from the Fpga
    constexpr static uint64_t MASK = 0xff;
};


//! Write-only register file SystemEnable at address 0x5
struct SystemEnable
{
    //! \brief The raw bits used to send and receive data to and from the hardware
    //!
    //! This member my be accessed directly.
    uint64_t raw = 0;

    //! Initialize with zero
    SystemEnable() = default;
    //! Initialize with a specific value
    explicit SystemEnable(uint64_t value) : raw(value) {};

    //! The Jtag command to access this register
    constexpr static RMA2_NLA ADDRESS = 0x5;
    //! Indicates whether this register can be read on the software side
    constexpr static bool READABLE = false;
    //! Indicates whether this register can be written on the software side
    constexpr static bool WRITABLE = true;
    //! Indicates whether this register is a Jtag action
    constexpr static bool TRIGGER = false;
    //! The bit size of this register
    constexpr static uint64_t SIZE = 1;
    //! The mask used to cut off extraneous bits when reading from the Fpga
    constexpr static uint64_t MASK = 0x1;
};


//! Write-only register file BiasControl at address 0x6
struct BiasControl
{
    //! \brief The raw bits used to send and receive data to and from the hardware
    //!
    //! This member my be accessed directly.
    uint64_t raw = 0;

    //! Initialize with zero
    BiasControl() = default;
    //! Initialize with a specific value
    explicit BiasControl(uint64_t value) : raw(value) {};

    //! The Jtag command to access this register
    constexpr static RMA2_NLA ADDRESS = 0x6;
    //! Indicates whether this register can be read on the software side
    constexpr static bool READABLE = false;
    //! Indicates whether this register can be written on the software side
    constexpr static bool WRITABLE = true;
    //! Indicates whether this register is a Jtag action
    constexpr static bool TRIGGER = false;
    //! The bit size of this register
    constexpr static uint64_t SIZE = 6;
    //! The mask used to cut off extraneous bits when reading from the Fpga
    constexpr static uint64_t MASK = 0x3f;
};


//! Write-only register file StopTimeCount at address 0xa
struct StopTimeCount
{
    //! \brief The raw bits used to send and receive data to and from the hardware
    //!
    //! This member my be accessed directly.
    uint64_t raw = 0;

    //! Initialize with zero
    StopTimeCount() = default;
    //! Initialize with a specific value
    explicit StopTimeCount(uint64_t value) : raw(value) {};

    //! The Jtag command to access this register
    constexpr static RMA2_NLA ADDRESS = 0xa;
    //! Indicates whether this register can be read on the software side
    constexpr static bool READABLE = false;
    //! Indicates whether this register can be written on the software side
    constexpr static bool WRITABLE = true;
    //! Indicates whether this register is a Jtag action
    constexpr static bool TRIGGER = false;
    //! The bit size of this register
    constexpr static uint64_t SIZE = 1;
    //! The mask used to cut off extraneous bits when reading from the Fpga
    constexpr static uint64_t MASK = 0x1;
};


//! Write-only register file Set2Xpls at address 0xd
struct Set2Xpls
{
    //! \brief The raw bits used to send and receive data to and from the hardware
    //!
    //! This member my be accessed directly.
    uint64_t raw = 0;

    //! Initialize with zero
    Set2Xpls() = default;
    //! Initialize with a specific value
    explicit Set2Xpls(uint64_t value) : raw(value) {};

    //! The Jtag command to access this register
    constexpr static RMA2_NLA ADDRESS = 0xd;
    //! Indicates whether this register can be read on the software side
    constexpr static bool READABLE = false;
    //! Indicates whether this register can be written on the software side
    constexpr static bool WRITABLE = true;
    //! Indicates whether this register is a Jtag action
    constexpr static bool TRIGGER = false;
    //! The bit size of this register
    constexpr static uint64_t SIZE = 1;
    //! The mask used to cut off extraneous bits when reading from the Fpga
    constexpr static uint64_t MASK = 0x1;
};


//! Write-only register file Pll2gControl at address 0x10
struct Pll2gControl
{
    //! \brief The raw bits used to send and receive data to and from the hardware
    //!
    //! This member my be accessed directly.
    uint64_t raw = 0;

    //! Initialize with zero
    Pll2gControl() = default;
    //! Initialize with a specific value
    explicit Pll2gControl(uint64_t value) : raw(value) {};

    //! The Jtag command to access this register
    constexpr static RMA2_NLA ADDRESS = 0x10;
    //! Indicates whether this register can be read on the software side
    constexpr static bool READABLE = false;
    //! Indicates whether this register can be written on the software side
    constexpr static bool WRITABLE = true;
    //! Indicates whether this register is a Jtag action
    constexpr static bool TRIGGER = false;
    //! The bit size of this register
    constexpr static uint64_t SIZE = 3;
    //! The mask used to cut off extraneous bits when reading from the Fpga
    constexpr static uint64_t MASK = 0x7;
};


//! Write-only register file TxData at address 0x11
struct TxData
{
    //! \brief The raw bits used to send and receive data to and from the hardware
    //!
    //! This member my be accessed directly.
    uint64_t raw = 0;

    //! Initialize with zero
    TxData() = default;
    //! Initialize with a specific value
    explicit TxData(uint64_t value) : raw(value) {};

    //! The Jtag command to access this register
    constexpr static RMA2_NLA ADDRESS = 0x11;
    //! Indicates whether this register can be read on the software side
    constexpr static bool READABLE = false;
    //! Indicates whether this register can be written on the software side
    constexpr static bool WRITABLE = true;
    //! Indicates whether this register is a Jtag action
    constexpr static bool TRIGGER = false;
    //! The bit size of this register
    constexpr static uint64_t SIZE = 64;
    //! The mask used to cut off extraneous bits when reading from the Fpga
    constexpr static uint64_t MASK = 0xffffffffffffffff;
};


//! Write-only register file TestControl at address 0x17
struct TestControl
{
    //! \brief The raw bits used to send and receive data to and from the hardware
    //!
    //! This member my be accessed directly.
    uint64_t raw = 0;

    //! Initialize with zero
    TestControl() = default;
    //! Initialize with a specific value
    explicit TestControl(uint64_t value) : raw(value) {};

    //! The Jtag command to access this register
    constexpr static RMA2_NLA ADDRESS = 0x17;
    //! Indicates whether this register can be read on the software side
    constexpr static bool READABLE = false;
    //! Indicates whether this register can be written on the software side
    constexpr static bool WRITABLE = true;
    //! Indicates whether this register is a Jtag action
    constexpr static bool TRIGGER = false;
    //! The bit size of this register
    constexpr static uint64_t SIZE = 4;
    //! The mask used to cut off extraneous bits when reading from the Fpga
    constexpr static uint64_t MASK = 0xf;
};


//! Write-only register file PllFarControl at address 0x29
struct PllFarControl
{
    //! \brief The raw bits used to send and receive data to and from the hardware
    //!
    //! This member my be accessed directly.
    uint64_t raw = 0;

    //! Initialize with zero
    PllFarControl() = default;
    //! Initialize with a specific value
    explicit PllFarControl(uint64_t value) : raw(value) {};

    //! The Jtag command to access this register
    constexpr static RMA2_NLA ADDRESS = 0x29;
    //! Indicates whether this register can be read on the software side
    constexpr static bool READABLE = false;
    //! Indicates whether this register can be written on the software side
    constexpr static bool WRITABLE = true;
    //! Indicates whether this register is a Jtag action
    constexpr static bool TRIGGER = false;
    //! The bit size of this register
    constexpr static uint64_t SIZE = 15;
    //! The mask used to cut off extraneous bits when reading from the Fpga
    constexpr static uint64_t MASK = 0x7fff;
};


//! Write-only register file ArqControl at address 0x30
struct ArqControl
{
    //! \brief The raw bits used to send and receive data to and from the hardware
    //!
    //! This member my be accessed directly.
    uint64_t raw = 0;

    //! Initialize with zero
    ArqControl() = default;
    //! Initialize with a specific value
    explicit ArqControl(uint64_t value) : raw(value) {};

    //! The Jtag command to access this register
    constexpr static RMA2_NLA ADDRESS = 0x30;
    //! Indicates whether this register can be read on the software side
    constexpr static bool READABLE = false;
    //! Indicates whether this register can be written on the software side
    constexpr static bool WRITABLE = true;
    //! Indicates whether this register is a Jtag action
    constexpr static bool TRIGGER = false;
    //! The bit size of this register
    constexpr static uint64_t SIZE = 32;
    //! The mask used to cut off extraneous bits when reading from the Fpga
    constexpr static uint64_t MASK = 0xffffffff;
};


//! Write-only register file ArqTxTimeoutValue at address 0x34
struct ArqTxTimeoutValue
{
    //! \brief The raw bits used to send and receive data to and from the hardware
    //!
    //! This member my be accessed directly.
    uint64_t raw = 0;

    //! Initialize with zero
    ArqTxTimeoutValue() = default;
    //! Initialize with a specific value
    explicit ArqTxTimeoutValue(uint64_t value) : raw(value) {};

    //! The Jtag command to access this register
    constexpr static RMA2_NLA ADDRESS = 0x34;
    //! Indicates whether this register can be read on the software side
    constexpr static bool READABLE = false;
    //! Indicates whether this register can be written on the software side
    constexpr static bool WRITABLE = true;
    //! Indicates whether this register is a Jtag action
    constexpr static bool TRIGGER = false;
    //! The bit size of this register
    constexpr static uint64_t SIZE = 32;
    //! The mask used to cut off extraneous bits when reading from the Fpga
    constexpr static uint64_t MASK = 0xffffffff;
};


//! Write-only register file ArqRxTimeoutValue at address 0x35
struct ArqRxTimeoutValue
{
    //! \brief The raw bits used to send and receive data to and from the hardware
    //!
    //! This member my be accessed directly.
    uint64_t raw = 0;

    //! Initialize with zero
    ArqRxTimeoutValue() = default;
    //! Initialize with a specific value
    explicit ArqRxTimeoutValue(uint64_t value) : raw(value) {};

    //! The Jtag command to access this register
    constexpr static RMA2_NLA ADDRESS = 0x35;
    //! Indicates whether this register can be read on the software side
    constexpr static bool READABLE = false;
    //! Indicates whether this register can be written on the software side
    constexpr static bool WRITABLE = true;
    //! Indicates whether this register is a Jtag action
    constexpr static bool TRIGGER = false;
    //! The bit size of this register
    constexpr static uint64_t SIZE = 32;
    //! The mask used to cut off extraneous bits when reading from the Fpga
    constexpr static uint64_t MASK = 0xffffffff;
};


//! Read-write register file IBias at address 0x7
struct IBias
{
    //! \brief The raw bits used to send and receive data to and from the hardware
    //!
    //! This member my be accessed directly.
    uint64_t raw = 0;

    //! Initialize with zero
    IBias() = default;
    //! Initialize with a specific value
    explicit IBias(uint64_t value) : raw(value) {};

    //! The Jtag command to access this register
    constexpr static RMA2_NLA ADDRESS = 0x7;
    //! Indicates whether this register can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this register can be written on the software side
    constexpr static bool WRITABLE = true;
    //! Indicates whether this register is a Jtag action
    constexpr static bool TRIGGER = false;
    //! The bit size of this register
    constexpr static uint64_t SIZE = 15;
    //! The mask used to cut off extraneous bits when reading from the Fpga
    constexpr static uint64_t MASK = 0x7fff;
};


//! Read-write register file DelayRxData at address 0x21
struct DelayRxData
{
    //! \brief The raw bits used to send and receive data to and from the hardware
    //!
    //! This member my be accessed directly.
    uint64_t raw = 0;

    //! Initialize with zero
    DelayRxData() = default;
    //! Initialize with a specific value
    explicit DelayRxData(uint64_t value) : raw(value) {};

    //! The Jtag command to access this register
    constexpr static RMA2_NLA ADDRESS = 0x21;
    //! Indicates whether this register can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this register can be written on the software side
    constexpr static bool WRITABLE = true;
    //! Indicates whether this register is a Jtag action
    constexpr static bool TRIGGER = false;
    //! The bit size of this register
    constexpr static uint64_t SIZE = 6;
    //! The mask used to cut off extraneous bits when reading from the Fpga
    constexpr static uint64_t MASK = 0x3f;
};


//! Read-write register file DelayRxClock at address 0x22
struct DelayRxClock
{
    //! \brief The raw bits used to send and receive data to and from the hardware
    //!
    //! This member my be accessed directly.
    uint64_t raw = 0;

    //! Initialize with zero
    DelayRxClock() = default;
    //! Initialize with a specific value
    explicit DelayRxClock(uint64_t value) : raw(value) {};

    //! The Jtag command to access this register
    constexpr static RMA2_NLA ADDRESS = 0x22;
    //! Indicates whether this register can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this register can be written on the software side
    constexpr static bool WRITABLE = true;
    //! Indicates whether this register is a Jtag action
    constexpr static bool TRIGGER = false;
    //! The bit size of this register
    constexpr static uint64_t SIZE = 6;
    //! The mask used to cut off extraneous bits when reading from the Fpga
    constexpr static uint64_t MASK = 0x3f;
};


//! Write-only register file StartLink at address 0x8
struct StartLink
{
    //! \brief The raw bits used to send and receive data to and from the hardware
    //!
    //! This member my be accessed directly.
    uint64_t raw = 0;

    //! Initialize with zero
    StartLink() = default;
    //! Initialize with a specific value
    explicit StartLink(uint64_t value) : raw(value) {};

    //! The Jtag command to access this register
    constexpr static RMA2_NLA ADDRESS = 0x8;
    //! Indicates whether this register can be read on the software side
    constexpr static bool READABLE = false;
    //! Indicates whether this register can be written on the software side
    constexpr static bool WRITABLE = false;
    //! Indicates whether this register is a Jtag action
    constexpr static bool TRIGGER = true;
    //! The bit size of this register
    constexpr static uint64_t SIZE = 0;
    //! The mask used to cut off extraneous bits when reading from the Fpga
    constexpr static uint64_t MASK = 0;
};


//! Write-only register file StopLink at address 0x9
struct StopLink
{
    //! \brief The raw bits used to send and receive data to and from the hardware
    //!
    //! This member my be accessed directly.
    uint64_t raw = 0;

    //! Initialize with zero
    StopLink() = default;
    //! Initialize with a specific value
    explicit StopLink(uint64_t value) : raw(value) {};

    //! The Jtag command to access this register
    constexpr static RMA2_NLA ADDRESS = 0x9;
    //! Indicates whether this register can be read on the software side
    constexpr static bool READABLE = false;
    //! Indicates whether this register can be written on the software side
    constexpr static bool WRITABLE = false;
    //! Indicates whether this register is a Jtag action
    constexpr static bool TRIGGER = true;
    //! The bit size of this register
    constexpr static uint64_t SIZE = 0;
    //! The mask used to cut off extraneous bits when reading from the Fpga
    constexpr static uint64_t MASK = 0;
};


//! Write-only register file StartConfigPackage at address 0x18
struct StartConfigPackage
{
    //! \brief The raw bits used to send and receive data to and from the hardware
    //!
    //! This member my be accessed directly.
    uint64_t raw = 0;

    //! Initialize with zero
    StartConfigPackage() = default;
    //! Initialize with a specific value
    explicit StartConfigPackage(uint64_t value) : raw(value) {};

    //! The Jtag command to access this register
    constexpr static RMA2_NLA ADDRESS = 0x18;
    //! Indicates whether this register can be read on the software side
    constexpr static bool READABLE = false;
    //! Indicates whether this register can be written on the software side
    constexpr static bool WRITABLE = false;
    //! Indicates whether this register is a Jtag action
    constexpr static bool TRIGGER = true;
    //! The bit size of this register
    constexpr static uint64_t SIZE = 0;
    //! The mask used to cut off extraneous bits when reading from the Fpga
    constexpr static uint64_t MASK = 0;
};


//! Write-only register file StartPulsePackage at address 0x19
struct StartPulsePackage
{
    //! \brief The raw bits used to send and receive data to and from the hardware
    //!
    //! This member my be accessed directly.
    uint64_t raw = 0;

    //! Initialize with zero
    StartPulsePackage() = default;
    //! Initialize with a specific value
    explicit StartPulsePackage(uint64_t value) : raw(value) {};

    //! The Jtag command to access this register
    constexpr static RMA2_NLA ADDRESS = 0x19;
    //! Indicates whether this register can be read on the software side
    constexpr static bool READABLE = false;
    //! Indicates whether this register can be written on the software side
    constexpr static bool WRITABLE = false;
    //! Indicates whether this register is a Jtag action
    constexpr static bool TRIGGER = true;
    //! The bit size of this register
    constexpr static uint64_t SIZE = 0;
    //! The mask used to cut off extraneous bits when reading from the Fpga
    constexpr static uint64_t MASK = 0;
};


//! Write-only register file SetReset at address 0x1b
struct SetReset
{
    //! \brief The raw bits used to send and receive data to and from the hardware
    //!
    //! This member my be accessed directly.
    uint64_t raw = 0;

    //! Initialize with zero
    SetReset() = default;
    //! Initialize with a specific value
    explicit SetReset(uint64_t value) : raw(value) {};

    //! The Jtag command to access this register
    constexpr static RMA2_NLA ADDRESS = 0x1b;
    //! Indicates whether this register can be read on the software side
    constexpr static bool READABLE = false;
    //! Indicates whether this register can be written on the software side
    constexpr static bool WRITABLE = false;
    //! Indicates whether this register is a Jtag action
    constexpr static bool TRIGGER = true;
    //! The bit size of this register
    constexpr static uint64_t SIZE = 0;
    //! The mask used to cut off extraneous bits when reading from the Fpga
    constexpr static uint64_t MASK = 0;
};


//! Write-only register file ReleaseReset at address 0x1c
struct ReleaseReset
{
    //! \brief The raw bits used to send and receive data to and from the hardware
    //!
    //! This member my be accessed directly.
    uint64_t raw = 0;

    //! Initialize with zero
    ReleaseReset() = default;
    //! Initialize with a specific value
    explicit ReleaseReset(uint64_t value) : raw(value) {};

    //! The Jtag command to access this register
    constexpr static RMA2_NLA ADDRESS = 0x1c;
    //! Indicates whether this register can be read on the software side
    constexpr static bool READABLE = false;
    //! Indicates whether this register can be written on the software side
    constexpr static bool WRITABLE = false;
    //! Indicates whether this register is a Jtag action
    constexpr static bool TRIGGER = true;
    //! The bit size of this register
    constexpr static uint64_t SIZE = 0;
    //! The mask used to cut off extraneous bits when reading from the Fpga
    constexpr static uint64_t MASK = 0;
};


//! Write-only register file ResetCrcCount at address 0x28
struct ResetCrcCount
{
    //! \brief The raw bits used to send and receive data to and from the hardware
    //!
    //! This member my be accessed directly.
    uint64_t raw = 0;

    //! Initialize with zero
    ResetCrcCount() = default;
    //! Initialize with a specific value
    explicit ResetCrcCount(uint64_t value) : raw(value) {};

    //! The Jtag command to access this register
    constexpr static RMA2_NLA ADDRESS = 0x28;
    //! Indicates whether this register can be read on the software side
    constexpr static bool READABLE = false;
    //! Indicates whether this register can be written on the software side
    constexpr static bool WRITABLE = false;
    //! Indicates whether this register is a Jtag action
    constexpr static bool TRIGGER = true;
    //! The bit size of this register
    constexpr static uint64_t SIZE = 0;
    //! The mask used to cut off extraneous bits when reading from the Fpga
    constexpr static uint64_t MASK = 0;
};





}
}
}