#pragma once

extern "C"
{
	#include <Lua/lua.h>
	#include <Lua/lauxlib.h>
	#include <Lua/lualib.h>
}
#include "ErrHandler.h"

namespace Ackerfe
{
	struct LuaState
	{
		lua_State *state;
	};

	void luaInit(lua_State *state)
	{
		state = luaL_newstate();
		luaL_openlibs(state);
	}
	void luaTerminate(lua_State *state)
	{
		lua_close(state);
	}
	bool isLuaOK(lua_State *state, int luaFunction)
	{
		if (luaFunction != LUA_OK)
		{
			throwError("Lua", lua_tostring(state, -1));
			return false;
		}
		return true;
	}
}
