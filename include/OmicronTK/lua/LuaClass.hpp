#pragma once

#include "OmicronTK/lua/LuaValue.hpp"

namespace OmicronTK {
namespace lua {

class LuaClass
{
public:
    explicit LuaClass(const std::string &name) : m_name(name) {}

    inline void addStatic(const LuaReg &reg) { m_statics.push_back(reg); }
    inline void addMember(const LuaReg &reg) { m_members.push_back(reg); }
    inline void addMetamethod(const LuaReg &reg) { m_metamethods.push_back(reg); }

    inline void addStatic(const std::string &field, const LuaValue &value)
    {
        m_statics.push_back({field.c_str(), value});
    }

    inline void addMember(const std::string &field, const LuaValue &value)
    {
        m_members.push_back({field.c_str(), value});
    }

    inline void addMetamethod(const std::string &field, const LuaValue &value)
    {
        m_metamethods.push_back({field.c_str(), value});
    }

    inline void addConstructor(const LuaValue &constructor) { m_members.push_back({ "constructor", constructor }); }
    inline void addDestructor(const LuaValue &__gc) { m_metamethods.push_back({ "__gc", __gc }); }

private:
    std::string m_name;
    LuaRegVector m_statics;
    LuaRegVector m_members;
    LuaRegVector m_metamethods;

    friend class Lua;
};

}
}
