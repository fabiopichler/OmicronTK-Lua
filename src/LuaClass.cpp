#include "OmicronTK/lua/LuaClass.hpp"

namespace OmicronTK {
namespace lua {

LuaClass::LuaClass(const std::string &name) : m_name(name) {}

void LuaClass::addStatic(const std::string &field, const LuaValue &value)
{
    m_statics.push_back({ field.c_str(), value });
}

void LuaClass::addStatic(const LuaReg &reg)
{
    m_statics.push_back(reg);
}

void LuaClass::addMember(const std::string &field, const LuaValue &value)
{
    m_members.push_back({ field.c_str(), value });
}

void LuaClass::addMember(const LuaReg &reg)
{
    m_members.push_back(reg);
}

void LuaClass::addMetamethod(const std::string &field, const LuaValue &value)
{
    m_metamethods.push_back({ field.c_str(), value });
}

void LuaClass::addMetamethod(const LuaReg &reg)
{
    m_metamethods.push_back(reg);
}

void LuaClass::addConstructor(const LuaValue &constructor)
{
    m_members.push_back({ "constructor", constructor });
}

void LuaClass::addDestructor(const LuaValue &__gc)
{
    m_metamethods.push_back({ "__gc", __gc });
}

}
}
