
/*--*/R"#####(

local function checkSuper(super)
    return super ~= nil and (type(super) ~= "table" or type(super.self) ~= "table" or type(super.class) ~= "table")
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

    local _class = {
        self = {},
        class = { name = name },
    }

    if super then
        setmetatable(_class.self, { __index = super.self })
        _class.class.superClass = super.class.name
    end

    function _class.new(...)
        local o = setmetatable({}, { __index = _class.self })

        if super then
            o.super = super.self.constructor
        end

        if o.constructor then
            o.constructor(o, ...)
        elseif super and super.self.constructor then
            super.self.constructor(o, ...)
        end

        return o
    end

    return _class
end

)#####";
