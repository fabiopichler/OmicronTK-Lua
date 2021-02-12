#pragma once

#include "OmicronTK/lua/Value.hpp"

namespace OmicronTK {
namespace lua {

class Class
{
public:
    explicit Class(const std::string &name);

    void setStatics(const RegVector &statics);
    void addStatic(const std::string &field, const Value &value);
    void addStatic(const LuaReg &reg);

    void setMembers(const RegVector &members);
    void addMember(const std::string &field, const Value &value);
    void addMember(const LuaReg &reg);

    void setMetamethods(const RegVector &metamethods);
    void addMetamethod(const std::string &field, const Value &value);
    void addMetamethod(const LuaReg &reg);

    void addConstructor(const Value &constructor);
    void addDestructor(const Value &__gc);

private:
    std::string m_name;
    RegVector m_statics;
    RegVector m_members;
    RegVector m_metamethods;

    friend class Lua;
};

}
}
