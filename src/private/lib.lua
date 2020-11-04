
/*--*/R"#####(
function class(name, super)
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
            super.constructor(o, ...)
        end

        return o
    end

    return _class
end
)#####";
