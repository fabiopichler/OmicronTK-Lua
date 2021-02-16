#include "OmicronTK/lua/Value.hpp"
#include "OmicronTK/lua/defines.hpp"

#include <string>
#include <cstring>

namespace OmicronTK {
namespace lua {

static char *newString(const char *value)
{
    const size_t len = std::strlen(value) + 1;
    char *str = new char[len];

    std::memcpy(str, value, len);

    return str;
}

void Value::_switch(const Value &value)
{
    switch (value.m_type)
    {
        case ValueType::Nil: break;
        case ValueType::Number: this->m_number = value.m_number; break;
        case ValueType::Float: this->m_float = value.m_float; break;
        case ValueType::Integer: this->m_integer = value.m_integer; break;
        case ValueType::UInt: this->m_uint = value.m_uint; break;
        case ValueType::Long: this->m_long = value.m_long; break;
        case ValueType::ULong: this->m_ulong = value.m_ulong; break;
        case ValueType::String: this->m_string = newString(value.m_string); break;
        case ValueType::CFunction: this->m_cfunction = value.m_cfunction; break;
        case ValueType::Boolean: this->m_boolean = value.m_boolean; break;
        case ValueType::UserData: this->m_userdata = value.m_userdata; break;
    }
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

Value::Value(const Value &value)
    : m_type(value.m_type)
{
    _switch(value);
}

Value::Value(Value &&value)
    : m_type(value.m_type)
{
    _switch(value);
}

Value::Value()
    : m_type(ValueType::Nil) {}

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
    , m_string(newString(value)) {}

Value::Value(const std::string &value)
    : m_type(ValueType::String)
    , m_string(newString(value.c_str())) {}

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
        delete this->m_string;
}

ValueType Value::type() const
{
    return m_type;
}

double Value::number_value() const
{
    return m_type == ValueType::Number ? this->m_number : 0.0;
}

float Value::float_value() const
{
    return m_type == ValueType::Float ? this->m_float : 0.0f;
}

int Value::integer_value() const
{
    return m_type == ValueType::Integer ? this->m_integer : 0;
}

unsigned int Value::uint_value() const
{
    return m_type == ValueType::UInt ? this->m_uint : 0u;
}

long Value::long_value() const
{
    return m_type == ValueType::Long ? this->m_long : 0l;
}

unsigned long Value::ulong_value() const
{
    return m_type == ValueType::ULong ? this->m_ulong : 0ul;
}

const char *Value::c_str_value() const
{
    return m_type == ValueType::String ? this->m_string : EmptyString.c_str();
}

std::string Value::string_value() const
{
    return m_type == ValueType::String ? this->m_string : EmptyString;
}

LuaCFunction Value::cfunction_value() const
{
    return m_type == ValueType::CFunction ? this->m_cfunction : nullptr;
}

bool Value::boolean_value() const
{
    return m_type == ValueType::Boolean ? this->m_boolean : false;
}

void *Value::userdata_value() const
{
    return m_type == ValueType::UserData ? this->m_userdata : nullptr;
}

}
}
