#pragma once

#include "OmicronTK/lua/global.h"
#include "OmicronTK/lua/Value.hpp"
#include <OmicronTK/lua/Callback.hpp>

#include <stdexcept>

namespace OmicronTK {
namespace lua {

class Lua;
class OTKLUA_EXPORT NativeClass
{
public:
    explicit NativeClass(Lua &lua, const std::string &name, const std::string &nspace = std::string());

    void setStatics(const ValueMap &statics);
    void addStatic(const std::string &field, const Value &value);

    void setMembers(const ValueMap &members);
    void addMember(const std::string &field, const Value &value);

    void setMetamethods(const ValueMap &metamethods);
    void addMetamethod(const std::string &field, const Value &value);

    void addConstructor(const Value &constructor);
    void addDestructor(const Value &__gc);

    void create();

    template<void (*value)(CallbackInfo &info)>
    inline void addConstructor()
    {
        addConstructor(&Callback::luaCallback<value>);
    }

    template<void (*value)(CallbackInfo &info)>
    inline void addDestructor()
    {
        addDestructor(&Callback::luaCallback<value>);
    }

    template<void (*value)(CallbackInfo &info)>
    inline void addStatic(const std::string &field)
    {
        addStatic(field, &Callback::luaCallback<value>);
    }

    template<void (*value)(CallbackInfo &info)>
    inline void addMember(const std::string &field)
    {
        addMember(field, &Callback::luaCallback<value>);
    }

private:
    Lua &m_lua;
    std::string m_name;
    std::string m_nspace;
    ValueMap m_statics;
    ValueMap m_members;
    ValueMap m_metamethods;
};

}
}
