/*
 * This is a generated file - do not change it
 * {{ datetime }}
 */

#pragma once

#include <cinttypes>

#include <extoll/rma.h>

{% for id in ns %}
namespace {{ id }} {
{%- endfor %}


{% for def in defs %}
//! {% if def.read and def.write -%}
Read-write
{%- elif def.read -%}
Read-only
{%- else -%}
Write-only
{%- endif %} register file {{ def.name }} at address {{ def.address|hex }}
struct {{ def.name }}
{
    //! \brief The raw bits used to send and receive data to and from the hardware
    //!
    //! This member my be accessed directly.
    uint64_t raw = 0;

    //! Initialize with zero
    {{def.name}}() = default;
    //! Initialize with a specific value
    explicit {{def.name}}(uint64_t value) : raw(value) {};

    //! The Jtag command to access this register
    constexpr static RMA2_NLA ADDRESS = {{ def.address|hex }};
    //! Indicates whether this register can be read on the software side
    constexpr static bool READABLE = {{ def.read|lower }};
    //! Indicates whether this register can be written on the software side
    constexpr static bool WRITABLE = {{ def.write|lower }};
    //! Indicates whether this register is a Jtag action
    constexpr static bool TRIGGER = {{ (not def.read and not def.write)|lower }};
    //! The bit size of this register
    constexpr static uint64_t SIZE = {{ def.width }};
    //! The mask used to cut off extraneous bits when reading from the Fpga
    constexpr static uint64_t MASK = {% if def.read or def.write %}{{def|mask|hex}}{% else %}0{% endif %};
};

{% endfor %}


{% for id in ns %}
}
{%- endfor %}