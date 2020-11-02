#pragma once

#include <vector>
#include <string>

typedef struct lua_State lua_State;

namespace OmicronTK {
namespace lua {

using LuaCFunction = int (*)(lua_State *L);

struct LuaReg
{
    const char *name;
    LuaCFunction func;
};

using LuaRegVector = std::vector<LuaReg>;

static const std::string EmptyString;

}
}
