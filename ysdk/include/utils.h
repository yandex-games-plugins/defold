
#include <dmsdk/sdk.h>

namespace dmYandex {
    bool IsLuaArray(lua_State* L, int index);
    char* LuaTableToJSON(lua_State* L, int index);
}