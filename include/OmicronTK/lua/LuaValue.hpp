#pragma once

#include <vector>
#include <memory>

#include "OmicronTK/lua/defines.hpp"

namespace OmicronTK {
namespace lua {

enum class LuaValueType
{
    Undefined,
    Nil,
    Number,
    Integer,
    String,
    Closure,
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
    LuaValue(bool value);
    LuaValue(void *value);

    LuaValueType type() const;
    double number_value() const;
    int integer_value() const;
    const std::string &string_value() const;
    LuaCFunction closure_value() const;
    bool boolean_value() const;
    void *lightuserdata_value() const;

private:
    std::shared_ptr<LuaValueBase> m_ptr;
};

using LuaValueVector = std::vector<LuaValue>;

}
}
