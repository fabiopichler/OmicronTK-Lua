#pragma once

#include "OmicronTK/lua/global.h"
#include "OmicronTK/lua/defines.hpp"

#include <vector>
#include <list>
#include <memory>

namespace OmicronTK {
namespace lua {

class Persistent;

using PersistentVector = std::vector<std::unique_ptr<Persistent>>;
using PersistentList = std::list<std::unique_ptr<Persistent>>;

class OTKLUA_EXPORT Persistent
{
public:
    explicit Persistent(lua_State *L = nullptr);
    virtual ~Persistent();

    void ref(lua_State *L = nullptr);
    void unref();
    void rawgeti();

private:
    lua_State *L;
    int m_ref;
};

}
}
