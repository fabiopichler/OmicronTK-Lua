#include "OmicronTK/lua/Value.hpp"
#include "OmicronTK/lua/defines.hpp"

#include <string>
#include <cstring>

namespace OmicronTK {
namespace lua {

void Value::_switch(const Value &value)
{
    switch (value.m_type)
    {
        case ValueType::Nil: break;
        case ValueType::Number: m_number = value.m_number; break;
        case ValueType::Float: m_float = value.m_float; break;
        case ValueType::Integer: m_integer = value.m_integer; break;
        case ValueType::UInt: m_uint = value.m_uint; break;
        case ValueType::Long: m_long = value.m_long; break;
        case ValueType::ULong: m_ulong = value.m_ulong; break;
        case ValueType::String: m_string = strdup(value.m_string); break;
        case ValueType::CFunction: m_cfunction = value.m_cfunction; break;
        case ValueType::Boolean: m_boolean = value.m_boolean; break;
        case ValueType::UserData: m_userdata = value.m_userdata; break;
    }
}

Value::Value()
    : m_type(ValueType::Nil) {}

Value::Value(const Value &value)
    : m_type(value.m_type)
{
    _switch(value);
}

Value::Value(Value &&value)
    : m_type(value.m_type)
{
    if (value.m_type == ValueType::String)
        m_string = value.m_string;
    else
        _switch(value);

    value.m_type = ValueType::Nil;
    value.m_number = 0;
}

Value::Value(double value)
    : m_type(ValueType::Number)
    , m_number(value) {}

Value::Value(float value)
    : m_type(ValueType::Float)
    , m_float(value) {}

Value::Value(int value)
    : m_type(ValueType::Integer)
    , m_integer(value) {}

Value::Value(unsigned int value)
    : m_type(ValueType::UInt)
    , m_uint(value) {}

Value::Value(long value)
    : m_type(ValueType::Long)
    , m_long(value) {}

Value::Value(unsigned long value)
    : m_type(ValueType::ULong)
    , m_ulong(value) {}

Value::Value(const char *value)
    : m_type(ValueType::String)
    , m_string(strdup(value)) {}

Value::Value(const std::string &value)
    : m_type(ValueType::String)
    , m_string(strdup(value.c_str())) {}

Value::Value(LuaCFunction value)
    : m_type(ValueType::CFunction)
    , m_cfunction(value) {}

Value::Value(bool value)
    : m_type(ValueType::Boolean)
    , m_boolean(value) {}

Value::Value(void *value)
    : m_type(ValueType::UserData)
    , m_userdata(value) {}

Value::~Value()
{
    if (m_type == ValueType::String)
        free(m_string);
}

Value &Value::operator=(const Value &value)
{
    if (&value != this)
    {
        m_type = value.m_type;

        _switch(value);
    }

    return *this;
}

Value &Value::operator=(Value &&value)
{
    if (&value != this)
    {
        m_type = value.m_type;

        if (value.m_type == ValueType::String)
            m_string = value.m_string;
        else
            _switch(value);

        value.m_type = ValueType::Nil;
        value.m_number = 0;
    }

    return *this;
}

ValueType Value::type() const
{
    return m_type;
}

double Value::number_value() const
{
    return m_type == ValueType::Number ? m_number : 0.0;
}

float Value::float_value() const
{
    return m_type == ValueType::Float ? m_float : 0.0f;
}

int Value::integer_value() const
{
    return m_type == ValueType::Integer ? m_integer : 0;
}

unsigned int Value::uint_value() const
{
    return m_type == ValueType::UInt ? m_uint : 0u;
}

long Value::long_value() const
{
    return m_type == ValueType::Long ? m_long : 0l;
}

unsigned long Value::ulong_value() const
{
    return m_type == ValueType::ULong ? m_ulong : 0ul;
}

const char *Value::c_str_value() const
{
    return m_type == ValueType::String ? m_string : EmptyString.c_str();
}

std::string Value::string_value() const
{
    return m_type == ValueType::String ? m_string : EmptyString;
}

LuaCFunction Value::cfunction_value() const
{
    return m_type == ValueType::CFunction ? m_cfunction : nullptr;
}

bool Value::boolean_value() const
{
    return m_type == ValueType::Boolean ? m_boolean : false;
}

void *Value::userdata_value() const
{
    return m_type == ValueType::UserData ? m_userdata : nullptr;
}

}
}
