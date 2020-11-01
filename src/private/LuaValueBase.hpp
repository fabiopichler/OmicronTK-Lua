#pragma once

#include "OmicronTK/lua/LuaValue.hpp"

namespace OmicronTK {
namespace lua {

class LuaValueBase
{
protected:
    virtual LuaValueType type() const;
    virtual double number_value() const;
    virtual int integer_value() const;
    virtual const std::string &string_value() const;
    virtual LuaCFunction closure_value() const;
    virtual bool boolean_value() const;
    virtual void *lightuserdata_value() const;

    friend class LuaValue;
};

template<typename T>
class Value : public LuaValueBase
{
public:
    Value(T value, LuaValueType type)
        : m_value(value)
        , m_type(type) {}

    LuaValueType type() const override { return m_type; }

protected:
    T m_value;
    LuaValueType m_type;
};

}
}
