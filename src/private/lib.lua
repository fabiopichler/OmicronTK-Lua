
/*--*/R"#####(
function class(self, base)
    self.__index = self

    if base then
        setmetatable(self, base)
    end

    function self.new(...)
        local o = setmetatable({}, self)

        if base then
            o.super = base.constructor
        end

        if o.constructor then
            o.constructor(o, ...)
        elseif base and base.constructor then
            base.constructor(o, ...)
        end

        return o
    end

    return self
end
)#####";
