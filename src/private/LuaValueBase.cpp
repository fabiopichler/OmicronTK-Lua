#include "LuaValueBase.hpp"

#include <string>

namespace OmicronTK {
namespace lua {

LuaValue::Type LuaValueBase::type() const { return LuaValue::Undefined; }

double LuaValueBase::number_value() const { return 0.0; }

int LuaValueBase::integer_value() const { return 0; }

const std::string &LuaValueBase::string_value() const { return EmptyString; }

LuaCFunction LuaValueBase::cfunction_value() const { return nullptr; }

bool LuaValueBase::boolean_value() const { return false; }

void *LuaValueBase::userdata_value() const { return nullptr; }

}
}
