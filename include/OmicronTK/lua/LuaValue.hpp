#pragma once

#include <vector>
#include <memory>

#include "OmicronTK/lua/defines.hpp"
#include "OmicronTK/lua/CallbackInfo.hpp"

namespace OmicronTK {
namespace lua {

enum class LuaValueType
{
    Undefined,
    Nil,
    Number,
    Integer,
    String,
    CFunction,
    Boolean,
    Lightuserdata
};

class LuaValueBase;
class LuaValue
{
public:
    LuaValue(double value);
    LuaValue(int value);
    LuaValue(const char *value);
    LuaValue(const std::string &value);
    LuaValue(LuaCFunction value);
    LuaValue(LuaCppFunction value);
    LuaValue(bool value);
    LuaValue(void *value);

    LuaValueType type() const;
    double number_value() const;
    int integer_value() const;
    const std::string &string_value() const;
    LuaCFunction cfunction_value() const;
    bool boolean_value() const;
    void *lightuserdata_value() const;

    inline operator double () const { return number_value(); }
    inline operator int () const { return integer_value(); }
    inline operator const char *() { return string_value().c_str(); }
    inline operator const std::string &() const { return string_value(); }
    inline operator LuaCFunction () const { return cfunction_value(); }
    inline operator bool () const { return boolean_value(); }
    inline operator void *() const { return lightuserdata_value(); }

private:
    std::shared_ptr<LuaValueBase> m_ptr;
};

using LuaValueVector = std::vector<LuaValue>;

struct LuaReg
{
    const char *name;
    LuaValue value;
};

using LuaRegVector = std::vector<LuaReg>;

}
}
