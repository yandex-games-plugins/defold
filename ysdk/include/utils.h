
#include <dmsdk/sdk.h>


bool IsLuaArray(lua_State* L, int index);

char* LuaTableToJSON(lua_State* L, int index);
