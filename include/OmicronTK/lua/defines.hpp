#pragma once

#include <vector>
#include <string>

typedef struct lua_State lua_State;

namespace OmicronTK {
namespace lua {

using LuaCFunction = int (*)(lua_State *L);

static const std::string EmptyString;

}
}
