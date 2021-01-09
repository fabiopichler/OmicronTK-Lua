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

Value::Value(const Value &value)
    : m_type(value.m_type)
{
    switch (value.m_type)
    {
        case Value::Nil: break;
        case Value::Number: this->m_number = value.m_number; break;
        case Value::Float: this->m_float = value.m_float; break;
        case Value::Integer: this->m_integer = value.m_integer; break;
        case Value::UInt: this->m_uint = value.m_uint; break;
        case Value::Long: this->m_long = value.m_long; break;
        case Value::ULong: this->m_ulong = value.m_ulong; break;
        case Value::String: this->m_string = newString(value.m_string); break;
        case Value::CFunction: this->m_cfunction = value.m_cfunction; break;
        case Value::Boolean: this->m_boolean = value.m_boolean; break;
        case Value::UserData: this->m_userdata = value.m_userdata; break;
    }
}

Value::Value(Value &&value)
    : m_type(value.m_type)
{
    switch (value.m_type)
    {
        case Value::Nil: break;
        case Value::Number: this->m_number = value.m_number; break;
        case Value::Float: this->m_float = value.m_float; break;
        case Value::Integer: this->m_integer = value.m_integer; break;
        case Value::UInt: this->m_uint = value.m_uint; break;
        case Value::Long: this->m_long = value.m_long; break;
        case Value::ULong: this->m_ulong = value.m_ulong; break;
        case Value::String: this->m_string = newString(value.m_string); break;
        case Value::CFunction: this->m_cfunction = value.m_cfunction; break;
        case Value::Boolean: this->m_boolean = value.m_boolean; break;
        case Value::UserData: this->m_userdata = value.m_userdata; break;
    }
}

Value::Value()
    : m_type(Value::Nil) {}

Value::Value(double value)
    : m_type(Value::Number)
    , m_number(value) {}

Value::Value(float value)
    : m_type(Value::Float)
    , m_float(value) {}

Value::Value(int value)
    : m_type(Value::Integer)
    , m_integer(value) {}

Value::Value(unsigned int value)
    : m_type(Value::UInt)
    , m_uint(value) {}

Value::Value(long value)
    : m_type(Value::Long)
    , m_long(value) {}

Value::Value(unsigned long value)
    : m_type(Value::ULong)
    , m_ulong(value) {}

Value::Value(const char *value)
    : m_type(Value::String)
    , m_string(newString(value)) {}

Value::Value(const std::string &value)
    : m_type(Value::String)
    , m_string(newString(value.c_str())) {}

Value::Value(LuaCFunction value)
    : m_type(Value::CFunction)
    , m_cfunction(value) {}

Value::Value(LuaCppFunction value)
    : m_type(Value::CFunction)
    , m_cfunction(reinterpret_cast<LuaCFunction>(value)) {}

Value::Value(bool value)
    : m_type(Value::Boolean)
    , m_boolean(value) {}

Value::Value(void *value)
    : m_type(Value::UserData)
    , m_userdata(value) {}

Value::~Value()
{
    if (m_type == Value::String)
        delete this->m_string;
}

Value::Type Value::type() const
{
    return m_type;
}

double Value::number_value() const
{
    return m_type == Value::Number ? this->m_number : 0.0;
}

float Value::float_value() const
{
    return m_type == Value::Float ? this->m_float : 0.0f;
}

int Value::integer_value() const
{
    return m_type == Value::Integer ? this->m_integer : 0;
}

unsigned int Value::uint_value() const
{
    return m_type == Value::UInt ? this->m_uint : 0u;
}

long Value::long_value() const
{
    return m_type == Value::Long ? this->m_long : 0l;
}

unsigned long Value::ulong_value() const
{
    return m_type == Value::ULong ? this->m_ulong : 0ul;
}

const char *Value::c_str_value() const
{
    return m_type == Value::String ? this->m_string : EmptyString.c_str();
}

std::string Value::string_value() const
{
    return m_type == Value::String ? this->m_string : EmptyString;
}

LuaCFunction Value::cfunction_value() const
{
    return m_type == Value::CFunction ? this->m_cfunction : nullptr;
}

bool Value::boolean_value() const
{
    return m_type == Value::Boolean ? this->m_boolean : false;
}

void *Value::userdata_value() const
{
    return m_type == Value::UserData ? this->m_userdata : nullptr;
}

}
}
