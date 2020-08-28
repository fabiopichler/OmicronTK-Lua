#*******************************************************************************
#  OmicronTK_lua
#
#  Author: Fábio Pichler
#  Website: http://fabiopichler.net
#  License: The MIT License
#
#  Copyright 2018-2020, Fábio Pichler
#
#  Permission is hereby granted, free of charge, to any person obtaining
#  a copy of this software and associated documentation files (the "Software"),
#  to deal in the Software without restriction, including without limitation
#  the rights to use, copy, modify, merge, publish, distribute, sublicense,
#  and/or sell copies of the Software, and to permit persons to whom the Software
#  is furnished to do so, subject to the following conditions:
#
#  The above copyright notice and this permission notice shall be
#  included in all copies or substantial portions of the Software.
#
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
#  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
#  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
#  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
#  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
#  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
#  THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#
#*******************************************************************************

include(./project.pri)

TARGET = OmicronTK_lua$${DEBUG}
DEFINES += OTKLUA_BUILD_CORE_LIB

unix:LIBS += -ldl -llua
win32:LIBS +=  -llua53

contains(QMAKE_HOST.arch, x86_64) {

    unix:INCLUDEPATH += $${LUA_INCLUDE_PATH_UNIX64}
    unix:LIBS += -L$${LUA_LIB_PATH_UNIX64}

    win32:INCLUDEPATH += $${LUA_INCLUDE_PATH_WIN64}
    win32:LIBS += -L$${LUA_LIB_PATH_WIN64}

} else {

    unix:INCLUDEPATH += $${LUA_INCLUDE_PATH_UNIX32}
    unix:LIBS += -L$${LUA_LIB_PATH_UNIX32}

    win32:INCLUDEPATH += $${LUA_INCLUDE_PATH_WIN32}
    win32:LIBS += -L$${LUA_LIB_PATH_WIN32}

}

win32:RC_FILE = src/lua.rc

HEADERS += \
    include/OmicronTK/lua/global.h \
    include/OmicronTK/lua/LuaBase.hpp \
    include/OmicronTK/lua/LuaState.hpp \
    include/OmicronTK/lua/version.h

SOURCES += \
    src/LuaBase.cpp \
    src/LuaState.cpp
