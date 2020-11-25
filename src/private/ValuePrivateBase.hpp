#pragma once

#include "OmicronTK/lua/Value.hpp"

namespace OmicronTK {
namespace lua {

class ValuePrivateBase
{
protected:
    virtual Value::Type type() const;
    virtual double number_value() const;
    virtual int integer_value() const;
    virtual const std::string &string_value() const;
    virtual LuaCFunction cfunction_value() const;
    virtual bool boolean_value() const;
    virtual void *userdata_value() const;

    friend class Value;
};

template<Value::Type m_type, typename T>
class ValuePrivate : public ValuePrivateBase
{
public:
    explicit ValuePrivate(const T &value) : m_value(value) {}
    explicit ValuePrivate(T &&value) : m_value(std::move(value)) {}

    Value::Type type() const override { return m_type; }

protected:
    T m_value;
};

}
}
