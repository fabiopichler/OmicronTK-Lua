#pragma once

#include <map>

#include "OmicronTK/lua/defines.hpp"

namespace OmicronTK {
namespace lua {

enum ValueType
{
    Nil,
    Number,
    Float,
    Integer,
    UInt,
    Long,
    ULong,
    String,
    CFunction,
    Boolean,
    UserData
};

template<ValueType>
struct __ValueType
{
    using type = void;
};

template<const ValueType _type>
using _ValueType = typename __ValueType<_type>::type;

template<>
struct __ValueType<Nil>
{
    using type = void *;
};

template<>
struct __ValueType<Number>
{
    using type = double;
};

template<>
struct __ValueType<Float>
{
    using type = float;
};

template<>
struct __ValueType<Integer>
{
    using type = int;
};

template<>
struct __ValueType<UInt>
{
    using type = unsigned int;
};

template<>
struct __ValueType<Long>
{
    using type = long;
};

template<>
struct __ValueType<ULong>
{
    using type = unsigned long;
};

template<>
struct __ValueType<String>
{
    using type = const char *;
};

template<>
struct __ValueType<CFunction>
{
    using type = LuaCFunction;
};

template<>
struct __ValueType<Boolean>
{
    using type = bool;
};

template<>
struct __ValueType<UserData>
{
    using type = void *;
};

class Value
{
    template<const ValueType type, const ValueType expected, typename _Tp>
    using _enable_if = typename std::enable_if<type == expected, _Tp>::type;

public:
    Value &operator=(const Value &value);

    Value(const Value &value);
    Value(Value &&value);
    Value(); // nil
    Value(double value);
    Value(float value);
    Value(int value);
    Value(unsigned int value);
    Value(long value);
    Value(unsigned long value);
    Value(const char *value);
    Value(const std::string &value);
    Value(LuaCFunction value);
    Value(bool value);
    Value(void *value);
    ~Value();

    ValueType type() const;

    double number_value() const;
    float float_value() const;
    int integer_value() const;
    unsigned int uint_value() const;
    long long_value() const;
    unsigned long ulong_value() const;
    const char *c_str_value() const;
    std::string string_value() const;
    LuaCFunction cfunction_value() const;
    bool boolean_value() const;
    void *userdata_value() const;

    inline operator double () const { return number_value(); }
    inline operator float () const { return float_value(); }
    inline operator int () const { return integer_value(); }
    inline operator unsigned int () const { return uint_value(); }
    inline operator long () const { return long_value(); }
    inline operator unsigned long () const { return ulong_value(); }
    inline operator const char *() { return c_str_value(); }
    inline operator std::string () const { return c_str_value(); }
    inline operator LuaCFunction () const { return cfunction_value(); }
    inline operator bool () const { return boolean_value(); }
    inline operator void *() const { return userdata_value(); }

    template<const ValueType type>
    _enable_if<type, ValueType::Nil, void *> value() {
        return nullptr;
    }

    template<const ValueType type>
    _enable_if<type, ValueType::Number, double> value() {
        return number_value();
    }

    template<const ValueType type>
    _enable_if<type, ValueType::Float, float> value() {
        return float_value();
    }

    template<const ValueType type>
    _enable_if<type, ValueType::Integer, int> value() {
        return integer_value();
    }

    template<const ValueType type>
    _enable_if<type, ValueType::UInt, unsigned int> value() {
        return uint_value();
    }

    template<const ValueType type>
    _enable_if<type, ValueType::Long, long> value() {
        return long_value();
    }

    template<const ValueType type>
    _enable_if<type, ValueType::ULong, unsigned long> value() {
        return ulong_value();
    }

    template<const ValueType type>
    _enable_if<type, ValueType::String, const char *> value() {
        return c_str_value();
    }

    template<const ValueType type>
    _enable_if<type, ValueType::CFunction, LuaCFunction> value() {
        return cfunction_value();
    }

    template<const ValueType type>
    _enable_if<type, ValueType::Boolean, bool> value() {
        return boolean_value();
    }

    template<const ValueType type>
    _enable_if<type, ValueType::UserData, void *> value() {
        return userdata_value();
    }

private:
    void _switch(const Value &value);

    ValueType m_type;

    union
    {
        double m_number;
        float m_float;
        int m_integer;
        unsigned int m_uint;
        long m_long;
        unsigned long m_ulong;
        char *m_string;
        LuaCFunction m_cfunction;
        bool m_boolean;
        void *m_userdata;
    };
};

using ValueVec = std::vector<Value>;
using ValueMap = std::map<std::string, Value>;

}
}
