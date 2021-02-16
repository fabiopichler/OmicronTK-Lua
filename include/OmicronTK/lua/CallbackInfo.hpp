#pragma once

#include "OmicronTK/lua/defines.hpp"

#include <lua.hpp>

namespace OmicronTK {
namespace lua {

class CallbackInfo
{
public:
    CallbackInfo(lua_State *L);

    inline lua_State *state() { return m_state; }

    int length();

    double getNumber(int idx);
    float getFloat(int idx);
    int getInteger(int idx);
    unsigned int getUInt(int idx);
    long getLong(int idx);
    unsigned long getULong(int idx);
    std::string getString(int idx);
    lua_CFunction getCFunction(int idx);
    bool getBoolean(int idx);
    void *getUserData(int idx);
    void *getLightUserData(int idx);

    template<typename T>
    inline T *getUserData(int idx)
    {
        return static_cast<T *>(getUserData(idx));
    }

    template<typename T>
    inline T *getLightUserData(int idx)
    {
        return static_cast<T *>(getLightUserData(idx));
    }

private:
    lua_State *m_state;
};

using LuaCppFunction = int (*)(CallbackInfo info);

}
}
