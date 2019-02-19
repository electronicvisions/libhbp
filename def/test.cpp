/**
 * This is a generated file - do not change it
 * {{ datetime }}
 */

#include <catch.hpp>

#include {{ test_include }}

{% macro init(def) -%}
{{ def.name }} rf {{ '{{{' }}
{%- for field in def.fields -%}
{% if field.type == 'bool' %}false{% else %}0{% endif %}{% if not loop.last %}, {% endif %}
{%- endfor -%}
{{ '}}}' }};
{%- endmacro -%}

using namespace {{ ns|join('::') }};


{% for def in defs %}
TEST_CASE("Definition '{{ def.name }}'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        {{ init(def) }}

        {% for value in test_values %}
        rf.raw = {{ value|hex }};

        {% for field in def.fields %}
        {%- set expected = field|cut(value) %}
        {%- if expected == 'false' %}
        REQUIRE(!rf.{{ field.name }});
        {%- elif expected == 'true' %}
        REQUIRE(rf.{{ field.name }});
        {%- else %}
        REQUIRE(rf.{{ field.name }} == {{ field|cut(value) }});
        {%- endif %}
        {%- endfor %}
        {% endfor %}
    }

    SECTION("write fields - read raw")
    {
        {{ init(def) }}

        {% for value in test_values %}
        {% for field in def.fields %}
        rf.{{ field.name }} = {{ field|cut(value) }};
        {%- endfor %}

        REQUIRE((rf.raw & {{ def|mask|hex }}) == {{ def|cut(value) }});
        {%- endfor %}
    }
}
{%- endfor %}

