#pragma once

#include "OmicronTK/lua/LuaValue.hpp"

namespace OmicronTK {
namespace lua {

class LuaValueBase
{
protected:
    virtual LuaValue::Type type() const;
    virtual double number_value() const;
    virtual int integer_value() const;
    virtual const std::string &string_value() const;
    virtual LuaCFunction cfunction_value() const;
    virtual bool boolean_value() const;
    virtual void *lightuserdata_value() const;

    friend class LuaValue;
};

template<typename T>
class Value : public LuaValueBase
{
public:
    Value(T value, LuaValue::Type type)
        : m_value(value)
        , m_type(type) {}

    LuaValue::Type type() const override { return m_type; }

protected:
    T m_value;
    LuaValue::Type m_type;
};

}
}
