#include "LuaValueBase.hpp"

#include <string>

namespace OmicronTK {
namespace lua {

LuaValueType LuaValueBase::type() const { return LuaValueType::Undefined; }

double LuaValueBase::number_value() const { return 0.0; }

int LuaValueBase::integer_value() const { return 0; }

const std::string &LuaValueBase::string_value() const { return EmptyString; }

LuaCFunction LuaValueBase::cfunction_value() const { return nullptr; }

bool LuaValueBase::boolean_value() const { return false; }

void *LuaValueBase::lightuserdata_value() const { return nullptr; }

}
}
