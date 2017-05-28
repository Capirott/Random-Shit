Handles = {}
local memoizedFuncs = {}

-- metatable which does magic
local mt = {}

mt.__index = function(handle, key)
    	if not handle.isValid then
    	    	print(debug.traceback())
	        error("Error: handle is not valid!", 2)
	end
	if Entity[key] == nil then 
		print(debug.traceback())
	        error("Error: " .. key .. " is not valid!", 2)
	end
	local f = memoizedFuncs[key]
		if not f then
		f = function(handle, ...) return Entity[key](handle.cppRef, ...) end
		memoizedFuncs[key] = f
	end
	return f
end

function getWrappedSafeFunction(f)
    return function(handle, ...)
            if not handle.isValid then
                print(debug.traceback())
                error("Error: handle is not valid!", 2)
            end
            return f(handle.cppRef, ...)
        end
end

function createHandle(cppRef)
    local handle = {
        cppRef = cppRef,
        isValid = true
    }

    -- speedy access without __index call
    handle.getName = getWrappedSafeFunction(Entity.getName)

    setmetatable(handle, mt)
    Handles[cppRef:getId()] = handle
    return handle
end

function onEntityRemoved(cppRef)
    local handle = Handles[cppRef:getId()];
    handle.cppRef = nil
    handle.isValid = false
    Handles[cppRef:getId()] = nil
end

function test(cppRef)
    local handle = Handles[cppRef:getId()]
    testHandle(handle)
end

function testHandle(handle)
    print("Hello, my name is " .. handle:getName())
    handle:setName("Mark")
    print("My name is " .. handle:getName() .. " now!")
end

function testBadReference()
    local handle = Handles[0] -- this handle exists and is okay
    handle.isValid = false -- but suppose that entity was removed!
    local _, err = pcall(testHandle, handle)
    if err then 
        print(err)
    end
end
