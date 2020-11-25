#pragma once

#include "OmicronTK/lua/LuaValue.hpp"

namespace OmicronTK {
namespace lua {

class LuaClass
{
public:
    explicit LuaClass(const std::string &name);

    void addStatic(const std::string &field, const LuaValue &value);
    void addStatic(const LuaReg &reg);

    void addMember(const std::string &field, const LuaValue &value);
    void addMember(const LuaReg &reg);

    void addMetamethod(const std::string &field, const LuaValue &value);
    void addMetamethod(const LuaReg &reg);

    void addConstructor(const LuaValue &constructor);
    void addDestructor(const LuaValue &__gc);

private:
    std::string m_name;
    LuaRegVector m_statics;
    LuaRegVector m_members;
    LuaRegVector m_metamethods;

    friend class Lua;
};

}
}
