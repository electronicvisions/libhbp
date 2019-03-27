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


{% for def in defs %}
struct {{ def.name }}
{
    {% for f in def.fields %}
    // {{f.name}} : {{f.width}}
    {%- endfor %}

    uint64_t raw = 0;

    {%- for e in def.enums %}
    enum class {{ e.name }}{% if e.underlying_type %} : {{ e.underlying_type }}{% endif %}
    {
    {% for name, value in e.fields.items() %}
        {{ name }} = {{ value }},
    {%- endfor %}
    };

    {%- for name in e.fields %}
    constexpr static {{e.name}} {{name}} = {{e.name}}::{{name}};
    {%- endfor %}
{%- endfor %}

    {{def.name}}() = default;
{%- if def.needs_constructor %}

    {{def.name}}({%- for f in def.fields -%}
        {{f.type}} {{f.name}}_{% if not loop.last %}, {% endif %}
    {%- endfor -%})
    {
        {% for f in def.fields %}
        raw |= (uint64_t({{f.name}}_) & {{f.mask}}) << {{f.offset}};
        {%- endfor %}
    }
{% for f in def.fields %}
    {{f.type}} {{f.name}}() const { return {{f.type}}(raw >> {{f.offset}} & {{f.mask}});}
{%- endfor %}

{% for f in def.fields %}
    void {{f.name}}({{f.type}} value) { raw &= ~({{f.mask}}ull << {{f.offset}}); raw |= (uint64_t(value) & {{f.mask}}) << {{f.offset}};}
{%- endfor %}
{% else %}
    {{def.name}}(uint64_t value)
        : raw(value & {{def.fields[0].mask}}) {}

    uint64_t {{def.fields[0].name}}() const { return raw & {{def.fields[0].mask}};};
    void {{def.fields[0].name}}(uint64_t value) { raw = value; }
{% endif %}
    constexpr static RMA2_NLA ADDRESS = {{ def.address|hex }};
    constexpr static bool READABLE = {{ def.read|lower }};
    constexpr static bool WRITABLE = {{ def.write|lower }};
};

{% endfor %}


{% for id in ns %}
}
{%- endfor %}
