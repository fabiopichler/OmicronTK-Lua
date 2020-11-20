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
    virtual void *userdata_value() const;

    friend class LuaValue;
};

template<LuaValue::Type m_type, typename T>
class Value : public LuaValueBase
{
public:
    explicit Value(const T &value) : m_value(value) {}
    explicit Value(T &&value) : m_value(std::move(value)) {}

    LuaValue::Type type() const override { return m_type; }

protected:
    T m_value;
};

}
}
