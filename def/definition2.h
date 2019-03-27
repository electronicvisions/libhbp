/**
 * This is a generated file - do not change it
 * {{ datetime }}
 */

#pragma once

#include <cinttypes>

#include <extoll/rma.h>

{% for id in ns %}
namespace {{ id }} {
{%- endfor %}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"

{% for def in defs %}
struct {{ def.name }}
{
    union
    {
        struct
        {
            {% for field in def.fields %}
            {{ field.type }} {{ field.name }} : {{ field.width }};
        {%- endfor %}
        };
        uint64_t raw;
    };

{% for e in def.enums %}
    enum {{ e.name }}{% if e.underlying_type %} : {{ e.underlying_type }}{% endif %}
    {
    {% for name, value in e.fields.items() %}
        {{ name }} = {{ value }},
    {%- endfor %}
    };
{%- endfor %}

    const static RMA2_NLA ADDRESS = {{ def.address|hex }};
    const static bool READABLE = {{ def.read|lower }};
    const static bool WRITABLE = {{ def.write|lower }};
};

static_assert(sizeof({{ def.name }}) == sizeof(uint64_t), "sizeof register file '{{ def.name }}' != sizeof uint64_t");
static_assert(std::is_trivial<{{ def.name }}>::value, "'{{ def.name }}' is not trivial");
{% endfor %}

#pragma GCC diagnostic pop

{% for id in ns %}
}
{%- endfor %}
