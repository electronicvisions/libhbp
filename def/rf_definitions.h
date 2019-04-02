{#-
Note: this is actually not a generated file.
It is used to generate a file which is why it includes that message
-#}
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
{%- elif def.write -%}
Write-only
{%- else -%};
Trigger
{%- endif %} register file {{ def.name }} at address {{ def.address|hex }}.
{%- for doc in def.doc %}
//! {{doc }}
{%- endfor %}
struct {{ def.name }}
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    {%- for e in def.enums %}
    //! All possible values for the `{{e.name|lower}}` field.
    enum class {{ e.name }}{% if e.underlying_type %} : {{ e.underlying_type }}{% endif %}
    {
    {%- for name, value in e.fields.items() %}
        {{ name }} = {{ value }},
    {%- endfor %}
    };

    {%- for name in e.fields %}
    //! Convenience alias for the `{{e.name}}` enum
    constexpr static {{e.name}} {{name}} = {{e.name}}::{{name}};
    {%- endfor %}
    {%- endfor %}

    //! Initialize all fields with zero
    {{def.name}}() = default;
    {%- if def.needs_constructor %}

    //! Initialize all fields with a specific value
    {{def.name}}({%- for f in def.fields -%}
    {{f.type}} {{f.name}}_{% if not loop.last %}, {% endif %}
    {%- endfor -%})
    {
    {%- for f in def.fields %}
        raw |= (uint64_t({{f.name}}_) & {{f.mask}}) << {{f.offset}};
    {%- endfor %}
    }
    {% for f in def.fields %}
    //! Read the `{{f.name}}` field
    {{f.type}} {{f.name}}() const { return {{f.type}}(raw >> {{f.offset}} & {{f.mask}});}
    {%- endfor %}

    {% for f in def.fields %}
    //! Set the `{{f.name}}` field
    void {{f.name}}({{f.type}} value) { raw &= ~({{f.mask}}ull << {{f.offset}}); raw |= (uint64_t(value) & {{f.mask}}) << {{f.offset}};}
    {%- endfor %}
    {% else %}
    //! Initialize the single field with a specific value
    {{def.name}}(uint64_t value)
    : raw(value & {{def.fields[0].mask}}) {}

    //! Read the single field
    uint64_t {{def.fields[0].name}}() const { return raw & {{def.fields[0].mask}};};
    //! Set the single field
    void {{def.fields[0].name}}(uint64_t value) { raw = value; }
    {% endif %}
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = {{ def.address|hex }};
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = {{ def.read|lower }};
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = {{ def.write|lower }};
};

{% endfor %}


{% for id in ns %}
}
{%- endfor %}
