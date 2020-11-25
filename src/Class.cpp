#include "OmicronTK/lua/Class.hpp"

namespace OmicronTK {
namespace lua {

Class::Class(const std::string &name) : m_name(name) {}

void Class::addStatic(const std::string &field, const Value &value)
{
    m_statics.push_back({ field.c_str(), value });
}

void Class::addStatic(const LuaReg &reg)
{
    m_statics.push_back(reg);
}

void Class::addMember(const std::string &field, const Value &value)
{
    m_members.push_back({ field.c_str(), value });
}

void Class::addMember(const LuaReg &reg)
{
    m_members.push_back(reg);
}

void Class::addMetamethod(const std::string &field, const Value &value)
{
    m_metamethods.push_back({ field.c_str(), value });
}

void Class::addMetamethod(const LuaReg &reg)
{
    m_metamethods.push_back(reg);
}

void Class::addConstructor(const Value &constructor)
{
    m_members.push_back({ "constructor", constructor });
}

void Class::addDestructor(const Value &__gc)
{
    m_metamethods.push_back({ "__gc", __gc });
}

}
}
