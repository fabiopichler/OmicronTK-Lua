#*******************************************************************************
#  OmicronTK+Lua
#
#  Author: Fábio Pichler
#  Website: http://fabiopichler.net
#  License: The MIT License
#
#  Copyright 2018-2019, Fábio Pichler
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

TEMPLATE = lib
CONFIG += c++11 plugin
CONFIG -= app_bundle
CONFIG -= qt

CONFIG(debug, debug|release) {

    BUILDDIR = debug
    DEBUG = -d
    unix:MAKEFILE = Makefile.debug

} else {

    BUILDDIR = release
    unix:MAKEFILE = Makefile.release

}

exists(./config.local.pri) {
    include(./config.local.pri)
} else {
    include(./config.pri)
}

OBJECTS_DIR = obj/$${BUILDDIR}
DESTDIR = ./build

INCLUDEPATH += "./include"
LIBS += -L$${DESTDIR}

unix:QMAKE_LFLAGS_RPATH=
unix:QMAKE_LFLAGS += '-Wl,-rpath,\'\$$ORIGIN\',-z,origin'
