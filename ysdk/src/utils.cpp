#include <string.h>
#include "utils.h"

static int WriteString(char* dst, size_t dst_size, const char* example, size_t example_size)
{
    if (!dst) {
        return example_size; // If we're only counting the number of characters needed
    }

    if (dst_size < example_size) {
        return 0;
    }

    for (size_t i = 0; i < example_size; ++i) {
        dst[i] = example[i];
    }

    return example_size;
}

static int EscapeJsonString(const char* unescaped, char* escaped, char* end_ptr)
{
    if (unescaped == NULL || escaped == NULL) {
        return 0;
    }

    // keep going through the unescaped until null terminating
    // always need at least 3 chars left in escaped buffer,
    // 2 for char expanding + 1 for null term
    char* esc_start = escaped;
    while (*unescaped && escaped <= end_ptr - 3) {

        switch (*unescaped) {

            case '\x22':
                *escaped++ = '\\';
                *escaped++ = '"';
                break;
            case '\x5C':
                *escaped++ = '\\';
                *escaped++ = '\\';
                break;
            case '\x08':
                *escaped++ = '\\';
                *escaped++ = '\b';
                break;
            case '\x0C':
                *escaped++ = '\\';
                *escaped++ = '\f';
                break;
            case '\x0A':
                *escaped++ = '\\';
                *escaped++ = '\n';
                break;
            case '\x0D':
                *escaped++ = '\\';
                *escaped++ = '\r';
                break;
            case '\x09':
                *escaped++ = '\\';
                *escaped++ = '\t';
                break;

            default:
                *escaped++ = *unescaped;
                break;

        }

        unescaped++;

    }

    *escaped = 0;

    return (escaped - esc_start);
}

static int WriteEscapedJsonString(char* json, size_t json_size, const char* value, size_t value_len)
{
    if (value == NULL) {
        return 0;
    }

    // allocate buffers to hold the escaped key and value strings
    char *value_escaped = (char*)malloc((1+value_len*2)*sizeof(char));

    // escape string characters such as "
    value_len = EscapeJsonString(value, value_escaped, value_escaped+((1+value_len*2)*sizeof(char)));

    int wrote_len = 0;
    if (json == 0) {
        wrote_len = value_len + 2;
    }
    else if (value_len+2 <= json_size) {
        wrote_len += WriteString(json, json_size, "\"", 1);
        wrote_len += WriteString(json+1, json_size-1, (const char*)value_escaped, value_len);
        wrote_len += WriteString(json+1+value_len, json_size-1-value_len, "\"", 1);
    }

    free(value_escaped);
    return wrote_len;
}

static int EncodeLuaValue(lua_State* L, int index, char* buffer, size_t buffer_size);

static int EncodeLuaTable(lua_State* L, int index, char* json_buffer, size_t json_buffer_size)
{
    assert(lua_istable(L, index));
    int top = lua_gettop(L);

    size_t cursor = 0;
    if (json_buffer && json_buffer_size < 1) {
        return 0;
    }

    bool is_array = dmYandex::IsLuaArray(L, index);

    if(json_buffer) {
        json_buffer[cursor] = is_array ? '[' : '{';
    }
    cursor++;

    lua_pushnil(L);
    int i = 0;
    while (lua_next(L, index) != 0) {

        // add commas
        if (i>0) {
            if (json_buffer && !WriteString(json_buffer+cursor, json_buffer_size-cursor, ",", 1)) {
                lua_pop(L, 2);
                assert(top == lua_gettop(L));
                return 0;
            }
            cursor++;
        }

        // write key (skipped if this is an array)
        if (!is_array) {
            lua_pushvalue(L, -2);
            int r = EncodeLuaValue(L, lua_gettop(L), json_buffer ? json_buffer+cursor : 0, json_buffer ? json_buffer_size-cursor : 0);
            lua_pop(L, 1);
            cursor+=r;

            if (json_buffer && !WriteString(json_buffer+cursor, json_buffer_size-cursor, ":", 1)) {
                lua_pop(L, 2);
                assert(top == lua_gettop(L));
                return 0;
            }
            cursor++;
        }

        // write value
        int r = EncodeLuaValue(L, lua_gettop(L), json_buffer ? json_buffer+cursor : 0, json_buffer ? json_buffer_size-cursor : 0);
        if (!r) {
            lua_pop(L, 2);
            assert(top == lua_gettop(L));
            return 0;
        }
        cursor+=r;

        lua_pop(L, 1);

        ++i;
    }

    // write ending of json object or array
    const char* end = is_array ? (const char*)"]\0" : (const char*)"}\0";
    if (json_buffer && !WriteString(json_buffer+cursor, json_buffer_size-cursor, end, 2)) {
        assert(top == lua_gettop(L));
        return 0;
    }
    cursor+=1;

    assert(top == lua_gettop(L));
    return cursor;
}

static int EncodeLuaValue(lua_State* L, int index, char* buffer, size_t buffer_size)
{
    // need space for null term
    if (buffer && buffer_size < 1) {
        return 0;
    }
    if( buffer ) {
        buffer_size--;
    }

    int top = lua_gettop(L);
    lua_pushvalue(L, index);
    index = lua_gettop(L);
    int value_type = lua_type(L, index);
    size_t len = 0;

    switch (value_type) {
        case LUA_TSTRING: {
            // String entries need to be escaped and enclosed with citations
            const char* v = lua_tolstring(L, index, &len);
            len = WriteEscapedJsonString(buffer, buffer_size, v, len);
            break;
        }
        case LUA_TBOOLEAN:
            if (lua_toboolean(L, index)) {
                len = WriteString(buffer, buffer_size, "true", 4);
            } else {
                len = WriteString(buffer, buffer_size, "false", 5);
            }
            break;
        case LUA_TNUMBER: {
            const char* v = lua_tolstring(L, index, &len);
            len = WriteString(buffer, buffer_size, v, len);
            break;
        }
        case LUA_TTABLE:
            len = EncodeLuaTable(L, index, buffer, buffer_size);
            break;
        case LUA_TNIL:
            len = WriteString(buffer, buffer_size, "null", 4);
            break;
        default:
            dmLogError("unserializeable entry: %s (%x)", lua_typename(L, -1), value_type);
            break;
    }

    if (buffer) {
        buffer[len] = '\0';
    }

    lua_pop(L, 1);
    assert(top == lua_gettop(L));
    return len;
}

bool dmYandex::IsLuaArray(lua_State* L, int index)
{
  assert(lua_istable(L, index));
  int top = lua_gettop(L);

  lua_pushnil(L);
  int i = 1;
  bool table_is_array = true;
  while (lua_next(L, index) != 0) {
    // check key type
    if (LUA_TNUMBER != lua_type(L, -2) || i != (int)lua_tonumber(L, -2)) {
        table_is_array = false;
        lua_pop(L, 2);
        break;
    }
    i++;

    lua_pop(L, 1);
  }

  assert(top == lua_gettop(L));
  return table_is_array;
}

char* dmYandex::LuaTableToJSON(lua_State* L, int index)
{
  assert(lua_istable(L, index));
  int top = lua_gettop(L);

  int size_needed = 1 + EncodeLuaTable(L, index, 0, 0);
  char* json = (char*)malloc(size_needed);
  EncodeLuaTable(L, index, json, size_needed);

  assert(top == lua_gettop(L));
  return json;
}