{#-
Note: this is actually not a generated file.
It is used to generate a file which is why it includes that message
-#}
/*
 * This is a generated file - do not change it
 * {{ datetime }}
 */

#include <catch2/catch.hpp>

#include {{ test_include }}

{% macro init(def) -%}
{{ def.name }} rf {{ '{' }}
{%- for field in def.fields -%}
{% if field.type == 'bool' %}false{% elif field.enum %}{{def.name}}::{{field.type}}(0){% else %}0{% endif %}{% if not loop.last %}, {% endif %}
{%- endfor -%}
{{ '}' }};
{%- endmacro -%}

using namespace {{ ns|join('::') }};


{% for def in defs %}{% if def.needs_constructor %}
TEST_CASE("Definition '{{ def.name }}'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        {{ init(def) }}

        {% for value in test_values %}
        rf.raw = {{ value|hex }}u;

        {% for field in def.fields %}
        {%- set expected = field|cut(value) %}
        {%- if expected == 'false' %}
        REQUIRE(!rf.{{ field.name }}());
        {%- elif expected == 'true' %}
        REQUIRE(rf.{{ field.name }}());
        {%- elif field.enum %}
        REQUIRE(rf.{{ field.name }}() == {{def.name}}::{{field.type}}({{field|cut(value)}}));
        {%- else %}
        REQUIRE(rf.{{ field.name }}() == {{ field|cut(value) }}u);
        {%- endif %}
        {%- endfor %}
        {% endfor %}
    }

    SECTION("write fields - read raw")
    {
        {{ init(def) }}

        {% for value in test_values %}
        {% for field in def.fields %}
        rf.{{ field.name }}({% if field.enum %}{{def.name}}::{{ field.type }}({% endif %}{{ field|cut(value) }}{% if field.enum %}){% endif %});
        {%- endfor %}

        {%- set expected = def|cut((value)) %}
        {%- if expected == 'false' %}
        REQUIRE((rf.raw & {{ def|mask|hex }}u) == 0);
        {%- elif expected == 'true' %}
        REQUIRE((rf.raw & {{ def|mask|hex }}u) == 1);
        {%- else %}
        REQUIRE((rf.raw & {{ def|mask|hex }}u) == {{ def|cut(value) }});
        {%- endif %}
        {%- endfor %}
    }
}
{% endif %}{%- endfor %}

