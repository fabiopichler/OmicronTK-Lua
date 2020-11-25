#pragma once

#include <vector>
#include <memory>

#include "OmicronTK/lua/defines.hpp"
#include "OmicronTK/lua/CallbackInfo.hpp"

namespace OmicronTK {
namespace lua {

class ValuePrivateBase;
class Value
{
public:
    enum Type
    {
        Nil,
        Number,
        Integer,
        String,
        CFunction,
        Boolean,
        UserData
    };

    Value(Value &&value);
    Value(const Value &value);
    Value(); // nil
    Value(double value);
    Value(int value);
    Value(const char *value);
    Value(const std::string &value);
    Value(LuaCFunction value);
    Value(LuaCppFunction value);
    Value(bool value);
    Value(void *value);

    Value::Type type() const;

    void *nil_value() const;
    double number_value() const;
    int integer_value() const;
    const std::string &string_value() const;
    LuaCFunction cfunction_value() const;
    bool boolean_value() const;
    void *userdata_value() const;

    inline operator double () const { return number_value(); }
    inline operator int () const { return integer_value(); }
    inline operator const char *() { return string_value().c_str(); }
    inline operator const std::string &() const { return string_value(); }
    inline operator LuaCFunction () const { return cfunction_value(); }
    inline operator bool () const { return boolean_value(); }
    inline operator void *() const { return userdata_value(); }

    // ---- tests ----
    Value(unsigned int value);
    inline operator unsigned int () const { return unsigned(integer_value()); }
    inline operator unsigned long () const { return unsigned(integer_value()); }
    // ---------------

private:
    std::shared_ptr<ValuePrivateBase> m_ptr;
};

using ValueVector = std::vector<Value>;

struct LuaReg
{
    const char *name;
    Value value;
};

using RegVector = std::vector<LuaReg>;

}
}
