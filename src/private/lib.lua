
/*--*/R"#####(
function class(self, base)
    if base then
        setmetatable(self, { __index = base })
    end

    self.__index = self

    function self.new(...)
        local o = setmetatable({}, self)

        if base then
            o.super = base.constructor
        end

        if o.constructor then
            o:constructor(...)
        elseif base and base.constructor then
            base:constructor(...)
        end

        return o
    end

    return self
end
)#####";
