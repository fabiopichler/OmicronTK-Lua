
/*--*/R"#####(

--[[

Copyright (c) 2020 Fábio Pichler

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

--]]

Object = {
    proto = {},
    class = { name = "Object" },
}

function Object.proto:constructor() end

function Object.proto:instanceOf(class)
    return getmetatable(self).__index == class.proto
end

function Object.proto:toString()
    local class = getmetatable(self).class

    return tostring(self) .. ", class: " .. class.name .. ", super: " .. class.super
end

local function checkSuper(super)
    return super ~= nil and (type(super) ~= "table" or type(super.proto) ~= "table" or type(super.class) ~= "table")
end

function class(name, super)

    if type(name) ~= "string" then
        error "'name' must be a string"
        return nil
    end

    if checkSuper(super) then
        error "'super' is not a valid class"
        return nil
    end

    super = super or Object

    local _class = {
        proto = {},
        class = {
            name = name,
            super = super.class.name,
        },
    }

    setmetatable(_class.proto, { __index = super.proto })

    function _class.new(...)
        local self = {
            super = super.proto.constructor,
        }

        setmetatable(self, {
            __index = _class.proto,
            class = _class.class,
        })

        _class.proto.constructor(self, ...)

        return self
    end

    return _class
end

)#####";
