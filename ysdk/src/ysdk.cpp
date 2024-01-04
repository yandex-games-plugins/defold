#define EXTENSION_SYMBOL ysdk
#define LIB_NAME "ysdk"
#define MODULE_NAME "ysdk"

#include <dmsdk/sdk.h>
#include <utils.h>

#if defined(DM_PLATFORM_HTML5)
#include "ysdk.h"
#endif

#pragma region Features

// ===============================================
// Loading API
// ===============================================

static int CPP_LoadingAPI_Ready(lua_State *L) {
#if defined(DM_PLATFORM_HTML5)
  JS_LoadingAPI_Ready();
#endif
  return 1;
}

// ===============================================
// Init Features Table
// ===============================================

static const luaL_reg LoadingAPI_methods[] = {{"ready", CPP_LoadingAPI_Ready},
                                              {0, 0}};

static int Init_Features(lua_State *L) {
  int top = lua_gettop(L);

  lua_pushliteral(L, "features");
  lua_newtable(L);

  lua_pushliteral(L, "loading_api");
  lua_newtable(L);
  luaL_register(L, NULL, LoadingAPI_methods);
  lua_settable(L, -3); // loading_api -> features

  lua_settable(L, -3); // features -> ysdk

  assert(top == lua_gettop(L));
  return 1;
}

#pragma endregion

#pragma region Payments

// ===============================================
// Create Purchase
// ===============================================

static void CPP_CreatePurchase_Handler(dmScript::LuaCallbackInfo *callback,
                                       const int success, const char *json,
                                       const char *signature) {
  lua_State *L = dmScript::GetCallbackLuaContext(callback);

  if (!dmScript::SetupCallback(callback)) {
    dmLogError("Failed to setup callback");
    return;
  }

  if (success) {
    dmScript::JsonToLua(L, json, strlen(json));

    if (strlen(signature) <= 2) {
      lua_pushnil(L);
    } else {
      lua_pushstring(L, signature);
    }
  } else {
    lua_pushnil(L);
    lua_pushnil(L);
  }

  dmScript::PCall(L, 3, 0);

  dmScript::TeardownCallback(callback);
}

static int CPP_CreatePurchase(lua_State *L) {
  int top = lua_gettop(L);

  dmScript::LuaCallbackInfo *callback = dmScript::CreateCallback(L, 1);
  char *params = dmYandex::LuaTableToJSON(L, 2);

#if defined(DM_PLATFORM_HTML5)
  JS_CreatePurchase((CreatePurchaseHandler)CPP_CreatePurchase_Handler, callback,
                    params);
#endif

  free(params);

  assert(top == lua_gettop(L));
  return 0;
}

// ===============================================
// Get Purchases
// ===============================================

static void CPP_GetPurchases_Handler(dmScript::LuaCallbackInfo *callback,
                                     const int success, const char *json,
                                     const char *signature) {
  lua_State *L = dmScript::GetCallbackLuaContext(callback);

  if (!dmScript::SetupCallback(callback)) {
    dmLogError("Failed to setup callback");
    return;
  }

  if (success) {
    dmScript::JsonToLua(L, json, strlen(json));

    if (strlen(signature) <= 2) {
      lua_pushnil(L);
    } else {
      lua_pushstring(L, signature);
    }
  } else {
    lua_pushnil(L);
    lua_pushnil(L);
  }

  dmScript::PCall(L, 3, 0);

  dmScript::TeardownCallback(callback);
}

static int CPP_GetPurchases(lua_State *L) {
  int top = lua_gettop(L);

  dmScript::LuaCallbackInfo *callback = dmScript::CreateCallback(L, 1);
  char *params = dmYandex::LuaTableToJSON(L, 2);

#if defined(DM_PLATFORM_HTML5)
  JS_GetPurchases((GetPurchasesHandler)CPP_GetPurchases_Handler, callback,
                  params);
#endif

  free(params);

  assert(top == lua_gettop(L));
  return 0;
}

// ===============================================
// Get Catalog
// ===============================================

static void CPP_GetCatalog_Handler(dmScript::LuaCallbackInfo *callback,
                                   const int success, const char *json) {
  lua_State *L = dmScript::GetCallbackLuaContext(callback);

  if (!dmScript::SetupCallback(callback)) {
    dmLogError("Failed to setup callback");
    return;
  }

  if (success) {
    dmScript::JsonToLua(L, json, strlen(json));
  } else {
    lua_pushnil(L);
  }

  dmScript::PCall(L, 2, 0);

  dmScript::TeardownCallback(callback);
}

static int CPP_GetCatalog(lua_State *L) {
  int top = lua_gettop(L);

  dmScript::LuaCallbackInfo *callback = dmScript::CreateCallback(L, 1);

#if defined(DM_PLATFORM_HTML5)
  JS_GetCatalog((GetCatalogHandler)CPP_GetCatalog_Handler, callback);
#endif

  assert(top == lua_gettop(L));
  return 0;
}

// ===============================================
// Consume Purchase
// ===============================================

static int CPP_ConsumePurchase(lua_State *L) {
  int top = lua_gettop(L);

  const char *PurchaseToken = luaL_checkstring(L, 1);

#if defined(DM_PLATFORM_HTML5)
  JS_ConsumePurchase(PurchaseToken);
#endif

  assert(top == lua_gettop(L));
  return 0;
}

// ===============================================
// Init Payments Table
// ===============================================

static const luaL_reg Payments_methods[] = {
    {"create_purchase", CPP_CreatePurchase},
    {"create_purchase", CPP_CreatePurchase},
    {"get_purchases", CPP_GetPurchases},
    {"get_catalog", CPP_GetCatalog},
    {"consume_purchase", CPP_ConsumePurchase},
    {0, 0}};

static int Init_Payments(lua_State *L) {
  int top = lua_gettop(L);

  lua_pushliteral(L, "payments");
  lua_newtable(L);
  luaL_register(L, NULL, Payments_methods);
  lua_settable(L, -3); // payments -> ysdk

  assert(top == lua_gettop(L));
  return 1;
}

#pragma endregion

#pragma region Player

// ===============================================
// Get Player Info
// ===============================================

static void CPP_GetPlayerInfo_Handler(dmScript::LuaCallbackInfo *callback,
                                      const int success, const char *json,
                                      const char *signature) {
  lua_State *L = dmScript::GetCallbackLuaContext(callback);

  if (!dmScript::SetupCallback(callback)) {
    dmLogError("Failed to setup callback");
    return;
  }

  if (success) {
    dmScript::JsonToLua(L, json, strlen(json));

    if (strlen(signature) <= 2) {
      lua_pushnil(L);
    } else {
      lua_pushstring(L, signature);
    }
  } else {
    lua_pushnil(L);
    lua_pushnil(L);
  }

  dmScript::PCall(L, 3, 0);

  dmScript::TeardownCallback(callback);
}

static int CPP_GetPlayerInfo(lua_State *L) {
  int top = lua_gettop(L);

  dmScript::LuaCallbackInfo *callback = dmScript::CreateCallback(L, 1);
  char *params;
  if (lua_isnoneornil(L, 2)) {
    params = NULL;
  } else {
    params = dmYandex::LuaTableToJSON(L, 2);
  }

#if defined(DM_PLATFORM_HTML5)
  JS_GetPlayerInfo((GetPlayerInfoHandler)CPP_GetPlayerInfo_Handler, callback,
                   params);
#endif

  free(params);

  assert(top == lua_gettop(L));
  return 0;
}

// ===============================================
// Open Auth Dialog
// ===============================================

static void CPP_OpenAuthDialog_Handler(dmScript::LuaCallbackInfo *callback,
                                       const int success) {
  lua_State *L = dmScript::GetCallbackLuaContext(callback);

  if (!dmScript::SetupCallback(callback)) {
    dmLogError("Failed to setup callback");
    return;
  }

  lua_pushboolean(L, success);

  dmScript::PCall(L, 2, 0);

  dmScript::TeardownCallback(callback);
}

static int CPP_OpenAuthDialog(lua_State *L) {
  int top = lua_gettop(L);

  dmScript::LuaCallbackInfo *callback = dmScript::CreateCallback(L, 1);

#if defined(DM_PLATFORM_HTML5)
  JS_OpenAuthDialog((OpenAuthDialogHandler)CPP_OpenAuthDialog_Handler,
                    callback);
#endif

  assert(top == lua_gettop(L));
  return 0;
}

// ===============================================
// Get Player IDs Per Game
// ===============================================

static void CPP_GetPlayerIDsPerGame_Handler(dmScript::LuaCallbackInfo *callback,
                                            const int success,
                                            const char *json) {
  lua_State *L = dmScript::GetCallbackLuaContext(callback);

  if (!dmScript::SetupCallback(callback)) {
    dmLogError("Failed to setup callback");
    return;
  }

  if (success) {
    dmScript::JsonToLua(L, json, strlen(json));
  } else {
    lua_pushnil(L);
  }

  dmScript::PCall(L, 2, 0);

  dmScript::TeardownCallback(callback);
}

static int CPP_GetPlayerIDsPerGame(lua_State *L) {
  int top = lua_gettop(L);

  dmScript::LuaCallbackInfo *callback = dmScript::CreateCallback(L, 1);

#if defined(DM_PLATFORM_HTML5)
  JS_GetPlayerIDsPerGame(
      (GetPlayerIDsPerGameHandler)CPP_GetPlayerIDsPerGame_Handler, callback);
#endif

  assert(top == lua_gettop(L));
  return 0;
}

// ===============================================
// Get Player Data
// ===============================================

static void CPP_GetPlayerData_Handler(dmScript::LuaCallbackInfo *callback,
                                      const int success, const char *json) {
  lua_State *L = dmScript::GetCallbackLuaContext(callback);

  if (!dmScript::SetupCallback(callback)) {
    dmLogError("Failed to setup callback");
    return;
  }

  if (success) {
    dmScript::JsonToLua(L, json, strlen(json));
  } else {
    lua_pushnil(L);
  }

  dmScript::PCall(L, 2, 0);

  dmScript::TeardownCallback(callback);
}

static int CPP_GetPlayerData(lua_State *L) {
  int top = lua_gettop(L);

  dmScript::LuaCallbackInfo *callback = dmScript::CreateCallback(L, 1);
  char *keys = dmYandex::LuaTableToJSON(L, 2);

#if defined(DM_PLATFORM_HTML5)
  JS_GetPlayerData((GetPlayerDataHandler)CPP_GetPlayerData_Handler, callback,
                   keys);
#endif

  free(keys);

  assert(top == lua_gettop(L));
  return 0;
}

// ===============================================
// Set Player Data
// ===============================================

static int CPP_SetPlayerData(lua_State *L) {
  int top = lua_gettop(L);

  char *data = dmYandex::LuaTableToJSON(L, 1);
  int flush = lua_toboolean(L, 2);

#if defined(DM_PLATFORM_HTML5)
  JS_SetPlayerData(data, flush);
#endif

  free(data);

  assert(top == lua_gettop(L));
  return 0;
}

// ===============================================
// Get Player Stats
// ===============================================

static void CPP_GetPlayerStats_Handler(dmScript::LuaCallbackInfo *callback,
                                       const int success, const char *json) {
  lua_State *L = dmScript::GetCallbackLuaContext(callback);

  if (!dmScript::SetupCallback(callback)) {
    dmLogError("Failed to setup callback");
    return;
  }

  if (success) {
    dmScript::JsonToLua(L, json, strlen(json));
  } else {
    lua_pushnil(L);
  }

  dmScript::PCall(L, 2, 0);

  dmScript::TeardownCallback(callback);
}

static int CPP_GetPlayerStats(lua_State *L) {
  int top = lua_gettop(L);

  dmScript::LuaCallbackInfo *callback = dmScript::CreateCallback(L, 1);
  char *keys = dmYandex::LuaTableToJSON(L, 2);

#if defined(DM_PLATFORM_HTML5)
  JS_GetPlayerStats((GetPlayerStatsHandler)CPP_GetPlayerStats_Handler, callback,
                    keys);
#endif

  free(keys);

  assert(top == lua_gettop(L));
  return 0;
}

// ===============================================
// Increment Player Stats
// ===============================================

static int CPP_IncrementPlayerStats(lua_State *L) {
  int top = lua_gettop(L);

  char *increments = dmYandex::LuaTableToJSON(L, 1);

#if defined(DM_PLATFORM_HTML5)
  JS_IncrementPlayerStats(increments);
#endif

  free(increments);

  assert(top == lua_gettop(L));
  return 0;
}

// ===============================================
// Set Player Stats
// ===============================================

static int CPP_SetPlayerStats(lua_State *L) {
  int top = lua_gettop(L);

  char *stats = dmYandex::LuaTableToJSON(L, 1);

#if defined(DM_PLATFORM_HTML5)
  JS_SetPlayerStats(stats);
#endif

  free(stats);

  assert(top == lua_gettop(L));
  return 0;
}

// ===============================================
// Init Player Table
// ===============================================

static const luaL_reg Player_methods[] = {
    {"get_info", CPP_GetPlayerInfo},
    {"open_auth_dialog", CPP_OpenAuthDialog},
    {"get_ids_per_game", CPP_GetPlayerIDsPerGame},
    {"get_data", CPP_GetPlayerData},
    {"set_data", CPP_SetPlayerData},
    {"get_stats", CPP_GetPlayerStats},
    {"increment_stats", CPP_IncrementPlayerStats},
    {"set_stats", CPP_SetPlayerStats},
    {0, 0}};

static int Init_Player(lua_State *L) {
  int top = lua_gettop(L);

  lua_pushliteral(L, "player");
  lua_newtable(L);
  luaL_register(L, NULL, Player_methods);
  lua_settable(L, -3); // player -> ysdk

  assert(top == lua_gettop(L));
  return 1;
}

#pragma endregion

#pragma region Feedback

// ===============================================
// Can Review
// ===============================================

static void CPP_CanReview_Handler(dmScript::LuaCallbackInfo *callback,
                                  const int success, const int canReview,
                                  const char *reason) {
  lua_State *L = dmScript::GetCallbackLuaContext(callback);

  if (!dmScript::SetupCallback(callback)) {
    dmLogError("Failed to setup callback");
    return;
  }

  if (success) {
    lua_pushboolean(L, canReview);

    if (strlen(reason) <= 2) {
      lua_pushnil(L);
    } else {
      lua_pushstring(L, reason);
    }
  } else {
    lua_pushboolean(L, 0);
    lua_pushnil(L);
  }

  dmScript::PCall(L, 2, 0);

  dmScript::TeardownCallback(callback);
}

static int CPP_CanReview(lua_State *L) {
  int top = lua_gettop(L);

  dmScript::LuaCallbackInfo *callback = dmScript::CreateCallback(L, 1);

#if defined(DM_PLATFORM_HTML5)
  JS_CanReview((CanReviewHandler)CPP_CanReview_Handler, callback);
#endif

  assert(top == lua_gettop(L));
  return 0;
}

// ===============================================
// Request Review
// ===============================================

static void CPP_RequestReview_Handler(dmScript::LuaCallbackInfo *callback,
                                      const int success,
                                      const int feedbackSent) {
  lua_State *L = dmScript::GetCallbackLuaContext(callback);

  if (!dmScript::SetupCallback(callback)) {
    dmLogError("Failed to setup callback");
    return;
  }

  if (success && feedbackSent) {
    lua_pushboolean(L, 1);
  } else {
    lua_pushboolean(L, 0);
  }

  dmScript::PCall(L, 2, 0);

  dmScript::TeardownCallback(callback);
}

static int CPP_RequestReview(lua_State *L) {
  int top = lua_gettop(L);

  dmScript::LuaCallbackInfo *callback = dmScript::CreateCallback(L, 1);

#if defined(DM_PLATFORM_HTML5)
  JS_RequestReview((RequestReviewHandler)CPP_RequestReview_Handler, callback);
#endif

  assert(top == lua_gettop(L));
  return 0;
}

// ===============================================
// Init Feedback Table
// ===============================================

static const luaL_reg Feedback_methods[] = {
    {"can_review", CPP_CanReview},
    {"request_review", CPP_RequestReview},
    {0, 0}};

static int Init_Feedback(lua_State *L) {
  int top = lua_gettop(L);

  lua_pushliteral(L, "feedback");
  lua_newtable(L);
  luaL_register(L, NULL, Feedback_methods);
  lua_settable(L, -3); // feedback -> ysdk

  assert(top == lua_gettop(L));
  return 1;
}

#pragma endregion

#pragma region Environment

// ===============================================
// Init Environment Table
// ===============================================

static int Init_Environment(lua_State *L) {
  int top = lua_gettop(L);

#if defined(DM_PLATFORM_HTML5)
  const char *result = JS_GetEnvironment();
#else
  const char *result = "{\"app\":0,\"browser\":{\"lang\":\"en\"},\"i18n\":{"
                       "\"lang\":\"en\",\"tld\":\"com\"}}";
#endif

  lua_pushliteral(L, "environment");
  dmScript::JsonToLua(L, result, strlen(result));
  lua_settable(L, -3);

  assert(top == lua_gettop(L));
  return 1;
}

#pragma endregion

#pragma region Adv

#pragma region Fullscreen Adv

static void CPP_ShowFullscreenAdv_Handler(dmScript::LuaCallbackInfo *onOpen,
                                          dmScript::LuaCallbackInfo *onClose,
                                          dmScript::LuaCallbackInfo *onError,
                                          dmScript::LuaCallbackInfo *onOffline,
                                          const int callbackType,
                                          const char *data) {
  switch (callbackType) {
  case 0: {
    if (!dmScript::IsCallbackValid(onOpen)) {
      return;
    }

    lua_State *L = dmScript::GetCallbackLuaContext(onOpen);

    if (dmScript::SetupCallback(onOpen)) {
      dmScript::PCall(L, 1, 0);
      dmScript::TeardownCallback(onOpen);
    } else {
      dmLogError("Failed to setup onOpen");
    }
    break;
  }
  case 1: {
    if (!dmScript::IsCallbackValid(onClose)) {
      return;
    }

    lua_State *L = dmScript::GetCallbackLuaContext(onClose);

    if (dmScript::SetupCallback(onClose)) {
      if (strcmp(data, "true") == 0) {
        lua_pushboolean(L, 1);
      } else {
        lua_pushboolean(L, 0);
      }
      dmScript::PCall(L, 2, 0);
      dmScript::TeardownCallback(onClose);
    } else {
      dmLogError("Failed to setup onClose");
    }

    if (dmScript::IsCallbackValid(onOpen)) {
      dmScript::DestroyCallback(onOpen);
    }
    if (dmScript::IsCallbackValid(onError)) {
      dmScript::DestroyCallback(onError);
    }
    if (dmScript::IsCallbackValid(onOffline)) {
      dmScript::DestroyCallback(onOffline);
    }
    break;
  }
  case 2: {
    if (!dmScript::IsCallbackValid(onError)) {
      return;
    }

    lua_State *L = dmScript::GetCallbackLuaContext(onError);

    if (dmScript::SetupCallback(onError)) {
      lua_pushstring(L, data);
      dmScript::PCall(L, 2, 0);
      dmScript::TeardownCallback(onError);
    } else {
      dmLogError("Failed to setup onError");
    }

    if (dmScript::IsCallbackValid(onOpen)) {
      dmScript::DestroyCallback(onOpen);
    }
    if (dmScript::IsCallbackValid(onOffline)) {
      dmScript::DestroyCallback(onOffline);
    }
    break;
  }
  case 3: {
    if (!dmScript::IsCallbackValid(onOffline)) {
      return;
    }

    lua_State *L = dmScript::GetCallbackLuaContext(onOffline);

    if (dmScript::SetupCallback(onOffline)) {
      dmScript::PCall(L, 1, 0);
      dmScript::TeardownCallback(onOffline);
    } else {
      dmLogError("Failed to setup onOffline");
    }

    if (dmScript::IsCallbackValid(onOpen)) {
      dmScript::DestroyCallback(onOpen);
    }
    if (dmScript::IsCallbackValid(onError)) {
      dmScript::DestroyCallback(onError);
    }
    if (dmScript::IsCallbackValid(onOffline)) {
      dmScript::DestroyCallback(onOffline);
    }
    break;
  }
  }
}

static int CPP_ShowFullscreenAdv(lua_State *L) {
  int top = lua_gettop(L);

  dmScript::LuaCallbackInfo *onOpen = NULL;

  lua_pushstring(L, "on_open");
  lua_gettable(L, -2);
  if (lua_isfunction(L, lua_gettop(L))) {
    onOpen = dmScript::CreateCallback(L, lua_gettop(L));
  }
  lua_pop(L, 1);

  dmScript::LuaCallbackInfo *onClose = NULL;

  lua_pushstring(L, "on_close");
  lua_gettable(L, -2);
  if (lua_isfunction(L, lua_gettop(L))) {
    onClose = dmScript::CreateCallback(L, lua_gettop(L));
  }
  lua_pop(L, 1);

  dmScript::LuaCallbackInfo *onError = NULL;

  lua_pushstring(L, "on_error");
  lua_gettable(L, -2);
  if (lua_isfunction(L, lua_gettop(L))) {
    onError = dmScript::CreateCallback(L, lua_gettop(L));
  }
  lua_pop(L, 1);

  dmScript::LuaCallbackInfo *onOffline = NULL;

  lua_pushstring(L, "on_offline");
  lua_gettable(L, -2);
  if (lua_isfunction(L, lua_gettop(L))) {
    onOffline = dmScript::CreateCallback(L, lua_gettop(L));
  }
  lua_pop(L, 1);

#if defined(DM_PLATFORM_HTML5)
  JS_ShowFullscreenAdv((ShowFullscreenAdvHandler)CPP_ShowFullscreenAdv_Handler,
                       onOpen, onClose, onError, onOffline);
#endif

  assert(top == lua_gettop(L));
  return 0;
}

#pragma endregion

#pragma region Rewarded Video

static void CPP_ShowRewardedVideo_Handler(dmScript::LuaCallbackInfo *onOpen,
                                          dmScript::LuaCallbackInfo *onRewarded,
                                          dmScript::LuaCallbackInfo *onClose,
                                          dmScript::LuaCallbackInfo *onError,
                                          const int callbackType,
                                          const char *data) {
  switch (callbackType) {
  case 0: {
    if (!dmScript::IsCallbackValid(onOpen)) {
      return;
    }

    lua_State *L = dmScript::GetCallbackLuaContext(onOpen);

    if (dmScript::SetupCallback(onOpen)) {
      dmScript::PCall(L, 1, 0);
      dmScript::TeardownCallback(onOpen);
    } else {
      dmLogError("Failed to setup onOpen");
    }
    break;
  }
  case 1: {
    if (!dmScript::IsCallbackValid(onRewarded)) {
      return;
    }

    lua_State *L = dmScript::GetCallbackLuaContext(onRewarded);

    if (dmScript::SetupCallback(onRewarded)) {
      dmScript::PCall(L, 1, 0);
      dmScript::TeardownCallback(onRewarded);
    } else {
      dmLogError("Failed to setup onRewarded");
    }

    break;
  }
  case 2: {
    if (!dmScript::IsCallbackValid(onClose)) {
      return;
    }

    lua_State *L = dmScript::GetCallbackLuaContext(onClose);

    if (dmScript::SetupCallback(onClose)) {
      dmScript::PCall(L, 1, 0);
      dmScript::TeardownCallback(onClose);
    } else {
      dmLogError("Failed to setup onClose");
    }

    if (dmScript::IsCallbackValid(onOpen)) {
      dmScript::DestroyCallback(onOpen);
    }
    if (dmScript::IsCallbackValid(onError)) {
      dmScript::DestroyCallback(onError);
    }
    break;
  }
  case 3: {
    if (!dmScript::IsCallbackValid(onError)) {
      return;
    }

    lua_State *L = dmScript::GetCallbackLuaContext(onError);

    if (dmScript::SetupCallback(onError)) {
      lua_pushstring(L, data);
      dmScript::PCall(L, 2, 0);
      dmScript::TeardownCallback(onError);
    } else {
      dmLogError("Failed to setup onError");
    }

    if (dmScript::IsCallbackValid(onOpen)) {
      dmScript::DestroyCallback(onOpen);
    }
    if (dmScript::IsCallbackValid(onClose)) {
      dmScript::DestroyCallback(onClose);
    }
    if (dmScript::IsCallbackValid(onRewarded)) {
      dmScript::DestroyCallback(onRewarded);
    }
    break;
  }
  }
}

static int CPP_ShowRewardedVideo(lua_State *L) {
  int top = lua_gettop(L);

  dmScript::LuaCallbackInfo *onOpen = NULL;

  lua_pushstring(L, "on_open");
  lua_gettable(L, -2);
  if (lua_isfunction(L, lua_gettop(L))) {
    onOpen = dmScript::CreateCallback(L, lua_gettop(L));
  }
  lua_pop(L, 1);

  dmScript::LuaCallbackInfo *onRewarded = NULL;

  lua_pushstring(L, "on_rewarded");
  lua_gettable(L, -2);
  if (lua_isfunction(L, lua_gettop(L))) {
    onRewarded = dmScript::CreateCallback(L, lua_gettop(L));
  }
  lua_pop(L, 1);

  dmScript::LuaCallbackInfo *onClose = NULL;

  lua_pushstring(L, "on_close");
  lua_gettable(L, -2);
  if (lua_isfunction(L, lua_gettop(L))) {
    onClose = dmScript::CreateCallback(L, lua_gettop(L));
  }
  lua_pop(L, 1);

  dmScript::LuaCallbackInfo *onError = NULL;

  lua_pushstring(L, "on_error");
  lua_gettable(L, -2);
  if (lua_isfunction(L, lua_gettop(L))) {
    onError = dmScript::CreateCallback(L, lua_gettop(L));
  }
  lua_pop(L, 1);

#if defined(DM_PLATFORM_HTML5)
  JS_ShowRewardedVideo((ShowRewardedVideoHandler)CPP_ShowRewardedVideo_Handler,
                       onOpen, onRewarded, onClose, onError);
#endif

  assert(top == lua_gettop(L));
  return 0;
}

#pragma endregion

#pragma region Sticky Banner

// ===============================================
// Get Banner Adv Status
// ===============================================

static void CPP_GetBannerAdvStatus_Handler(dmScript::LuaCallbackInfo *callback,
                                           const int success,
                                           const int stickyAdvIsShowing,
                                           const char *reason) {
  lua_State *L = dmScript::GetCallbackLuaContext(callback);

  if (!dmScript::SetupCallback(callback)) {
    dmLogError("Failed to setup callback");
    return;
  }

  if (success) {
    lua_pushboolean(L, stickyAdvIsShowing);

    if (strlen(reason) <= 2) {
      lua_pushnil(L);
    } else {
      lua_pushstring(L, reason);
    }
  } else {
    lua_pushboolean(L, 0);
    lua_pushnil(L);
  }

  dmScript::PCall(L, 3, 0);

  dmScript::TeardownCallback(callback);
}

static int CPP_GetBannerAdvStatus(lua_State *L) {
  int top = lua_gettop(L);

  dmScript::LuaCallbackInfo *callback = dmScript::CreateCallback(L, 1);

#if defined(DM_PLATFORM_HTML5)
  JS_GetBannerAdvStatus(
      (GetBannerAdvStatusHandler)CPP_GetBannerAdvStatus_Handler, callback);
#endif

  assert(top == lua_gettop(L));
  return 0;
}

// ===============================================
// Show Banner
// ===============================================

static int CPP_ShowBannerAdv(lua_State *L) {
  int top = lua_gettop(L);

#if defined(DM_PLATFORM_HTML5)
  JS_ShowBannerAdv();
#endif

  assert(top == lua_gettop(L));
  return 0;
}

// ===============================================
// Hide Banner
// ===============================================

static int CPP_HideBannerAdv(lua_State *L) {
  int top = lua_gettop(L);

#if defined(DM_PLATFORM_HTML5)
  JS_HideBannerAdv();
#endif

  assert(top == lua_gettop(L));
  return 0;
}

#pragma endregion

// ===============================================
// Init Adv Table
// ===============================================

static const luaL_reg Adv_methods[] = {
    // Fullscreen Adv
    {"show_fullscreen_adv", CPP_ShowFullscreenAdv},

    // Rewarded Video
    {"show_rewarded_video", CPP_ShowRewardedVideo},

    // Sticky Banner
    {"get_banner_adv_status", CPP_GetBannerAdvStatus},
    {"show_banner_adv", CPP_ShowBannerAdv},
    {"hide_banner_adv", CPP_HideBannerAdv},

    {0, 0}};

static int Init_Adv(lua_State *L) {
  int top = lua_gettop(L);

  lua_pushliteral(L, "adv");
  lua_newtable(L);
  luaL_register(L, NULL, Adv_methods);
  lua_settable(L, -3); // adv -> ysdk

  assert(top == lua_gettop(L));
  return 1;
}

#pragma endregion

#pragma region Events

static void CPP_OnEvent_Handler(dmScript::LuaCallbackInfo *callback) {
  lua_State *L = dmScript::GetCallbackLuaContext(callback);

  if (!dmScript::SetupCallback(callback)) {
    dmLogError("Failed to setup callback");
    return;
  }

  dmScript::PCall(L, 1, 0);
}

static int CPP_OnEvent(lua_State *L) {
  int top = lua_gettop(L);

  const char *eventName = luaL_checkstring(L, 1);

  dmScript::LuaCallbackInfo *callback = dmScript::CreateCallback(L, 2);

#if defined(DM_PLATFORM_HTML5)
  JS_OnEvent((OnEventHandler)CPP_OnEvent_Handler, callback, eventName);
#endif

  assert(top == lua_gettop(L));
  return 0;
}

static int CPP_DispatchEvent(lua_State *L) {
  int top = lua_gettop(L);

  const char *eventName = luaL_checkstring(L, 1);
  char *detail = dmYandex::LuaTableToJSON(L, 2);

#if defined(DM_PLATFORM_HTML5)
  JS_DispatchEvent(eventName, detail);
#endif

  free(detail);

  assert(top == lua_gettop(L));
  return 0;
}

#pragma endregion

#pragma region Leaderboards

// ===============================================
// Get Leaderboard Description
// ===============================================

static void
CPP_GetLeaderboardDescription_Handler(dmScript::LuaCallbackInfo *callback,
                                      const int success, const char *json) {
  lua_State *L = dmScript::GetCallbackLuaContext(callback);

  if (!dmScript::SetupCallback(callback)) {
    dmLogError("Failed to setup callback");
    return;
  }

  if (success) {
    dmScript::JsonToLua(L, json, strlen(json));
  } else {
    lua_pushnil(L);
  }

  dmScript::PCall(L, 3, 0);

  dmScript::TeardownCallback(callback);
}

static int CPP_GetLeaderboardDescription(lua_State *L) {
  int top = lua_gettop(L);

  const char *leaderboardName = luaL_checkstring(L, 1);
  dmScript::LuaCallbackInfo *callback = dmScript::CreateCallback(L, 2);

#if defined(DM_PLATFORM_HTML5)
  JS_GetLeaderboardDescription(
      (GetLeaderboardDescriptionHandler)CPP_GetLeaderboardDescription_Handler,
      callback, leaderboardName);
#endif

  assert(top == lua_gettop(L));
  return 0;
}

// ===============================================
// Set Leaderboard Score
// ===============================================

static int CPP_SetLeaderboardScore(lua_State *L) {
  int top = lua_gettop(L);

  const char *leaderboardName = luaL_checkstring(L, 1);
  const char *score = lua_tolstring(L, 2, NULL);
  const char *extraData = lua_tolstring(L, 3, NULL);

#if defined(DM_PLATFORM_HTML5)
  JS_SetLeaderboardScore(leaderboardName, score, extraData);
#endif

  assert(top == lua_gettop(L));
  return 0;
}

// ===============================================
// Get Leaderboard Player Entry
// ===============================================

static void
CPP_GetLeaderboardPlayerEntry_Handler(dmScript::LuaCallbackInfo *callback,
                                      const int success, const char *json) {
  lua_State *L = dmScript::GetCallbackLuaContext(callback);

  if (!dmScript::SetupCallback(callback)) {
    dmLogError("Failed to setup callback");
    return;
  }

  if (success) {
    dmScript::JsonToLua(L, json, strlen(json));
  } else {
    lua_pushnil(L);
  }

  dmScript::PCall(L, 2, 0);

  dmScript::TeardownCallback(callback);
}

static int CPP_GetLeaderboardPlayerEntry(lua_State *L) {
  int top = lua_gettop(L);

  const char *leaderboardName = luaL_checkstring(L, 1);
  dmScript::LuaCallbackInfo *callback = dmScript::CreateCallback(L, 2);

#if defined(DM_PLATFORM_HTML5)
  JS_GetLeaderboardPlayerEntry(
      (GetLeaderboardPlayerEntryHandler)CPP_GetLeaderboardPlayerEntry_Handler,
      callback, leaderboardName);
#endif

  assert(top == lua_gettop(L));
  return 0;
}

// ===============================================
// Get Leaderboard Entries
// ===============================================

static void
CPP_GetLeaderboardEntries_Handler(dmScript::LuaCallbackInfo *callback,
                                  const int success, const char *json) {
  lua_State *L = dmScript::GetCallbackLuaContext(callback);

  if (!dmScript::SetupCallback(callback)) {
    dmLogError("Failed to setup callback");
    return;
  }

  if (success) {
    dmScript::JsonToLua(L, json, strlen(json));
  } else {
    lua_pushnil(L);
  }

  dmScript::PCall(L, 2, 0);

  dmScript::TeardownCallback(callback);
}

static int CPP_GetLeaderboardEntries(lua_State *L) {
  int top = lua_gettop(L);

  const char *leaderboardName = luaL_checkstring(L, 1);
  dmScript::LuaCallbackInfo *callback = dmScript::CreateCallback(L, 2);

  char *params;
  if (lua_isnoneornil(L, 3)) {
    params = NULL;
  } else {
    params = dmYandex::LuaTableToJSON(L, 3);
  }

#if defined(DM_PLATFORM_HTML5)
  JS_GetLeaderboardEntries(
      (GetLeaderboardEntriesHandler)CPP_GetLeaderboardEntries_Handler, callback,
      leaderboardName, params);
#endif

  free(params);

  assert(top == lua_gettop(L));
  return 0;
}

// ===============================================
// Init Leaderboards Table
// ===============================================

static const luaL_reg Leaderboards_methods[] = {
    {"get_description", CPP_GetLeaderboardDescription},
    {"set_score", CPP_SetLeaderboardScore},
    {"get_player_entry", CPP_GetLeaderboardPlayerEntry},
    {"get_entries", CPP_GetLeaderboardEntries},

    {0, 0}};

static int Init_Leaderboards(lua_State *L) {
  int top = lua_gettop(L);

  lua_pushliteral(L, "leaderboards");
  lua_newtable(L);
  luaL_register(L, NULL, Leaderboards_methods);
  lua_settable(L, -3); // leaderboards -> ysdk

  assert(top == lua_gettop(L));
  return 1;
}

#pragma endregion

#pragma region Screen

// ===============================================
// Fullscreen Get Status
// ===============================================

static int CPP_Screen_Fullscreen_GetStatus(lua_State *L) {
  int top = lua_gettop(L);

#if defined(DM_PLATFORM_HTML5)
  const char *result = JS_Screen_Fullscreen_GetStatus();
#else
  const char *result = "off";
#endif

  lua_pushstring(L, result);

  assert(top + 1 == lua_gettop(L));
  return 1;
}

// ===============================================
// Fullscreen Request
// ===============================================

static int CPP_Screen_Fullscreen_Request(lua_State *L) {
#if defined(DM_PLATFORM_HTML5)
  JS_Screen_Fullscreen_Request();
#endif
  return 1;
}

// ===============================================
// Fullscreen Exit
// ===============================================

static int CPP_Screen_Fullscreen_Exit(lua_State *L) {
#if defined(DM_PLATFORM_HTML5)
  JS_Screen_Fullscreen_Exit();
#endif
  return 1;
}

// ===============================================
// Orientation Get
// ===============================================

static int CPP_JS_Screen_Orientation_Get(lua_State *L) {
  int top = lua_gettop(L);

#if defined(DM_PLATFORM_HTML5)
  const char *result = JS_Screen_Orientation_Get();
#else
  const char *result = "landscape";
#endif

  lua_pushstring(L, result);

  assert(top + 1 == lua_gettop(L));
  return 1;
}

// ===============================================
// Orientation Set
// ===============================================

static int CPP_JS_Screen_Orientation_Set(lua_State *L) {
  int top = lua_gettop(L);

  const char *value = luaL_checkstring(L, 1);

#if defined(DM_PLATFORM_HTML5)
  JS_Screen_Orientation_Set(value);
#endif

  assert(top == lua_gettop(L));
  return 1;
}

// ===============================================
// Init Screen Table
// ===============================================

static const luaL_reg Fullscreen_methods[] = {
    {"status", CPP_Screen_Fullscreen_GetStatus},
    {"request", CPP_Screen_Fullscreen_Request},
    {"exit", CPP_Screen_Fullscreen_Exit},
    {0, 0}};

static const luaL_reg Orientation_methods[] = {
    {"get", CPP_JS_Screen_Orientation_Get},
    {"set", CPP_JS_Screen_Orientation_Set},
    {0, 0}};

static int Init_Screen(lua_State *L) {
  int top = lua_gettop(L);

  lua_pushliteral(L, "screen");
  lua_newtable(L);

  lua_pushliteral(L, "fullscreen");
  lua_newtable(L);
  luaL_register(L, NULL, Fullscreen_methods);
  lua_settable(L, -3); // fullscreen -> screen

  lua_pushliteral(L, "orientation");
  lua_newtable(L);
  luaL_register(L, NULL, Orientation_methods);
  lua_settable(L, -3); // fullscreen -> screen

  lua_settable(L, -3); // screen -> ysdk

  assert(top == lua_gettop(L));
  return 1;
}

#pragma endregion

#pragma region Shortcut

// ===============================================
// Can Show Prompt
// ===============================================

static void CPP_CanShowPrompt_Handler(dmScript::LuaCallbackInfo *callback,
                                      const int success,
                                      const int canShowPrompt) {
  lua_State *L = dmScript::GetCallbackLuaContext(callback);

  if (!dmScript::SetupCallback(callback)) {
    dmLogError("Failed to setup callback");
    return;
  }

  if (success && canShowPrompt) {
    lua_pushboolean(L, 1);
  } else {
    lua_pushboolean(L, 0);
  }

  dmScript::PCall(L, 2, 0);

  dmScript::TeardownCallback(callback);
}

static int CPP_CanShowPrompt(lua_State *L) {
  int top = lua_gettop(L);

  dmScript::LuaCallbackInfo *callback = dmScript::CreateCallback(L, 1);

#if defined(DM_PLATFORM_HTML5)
  JS_CanShowPrompt((CanShowPromptHandler)CPP_CanShowPrompt_Handler, callback);
#endif

  assert(top == lua_gettop(L));
  return 0;
}

// ===============================================
// Show Prompt
// ===============================================

static void CPP_ShowPrompt_Handler(dmScript::LuaCallbackInfo *callback,
                                   const int success, const int accepted) {
  lua_State *L = dmScript::GetCallbackLuaContext(callback);

  if (!dmScript::SetupCallback(callback)) {
    dmLogError("Failed to setup callback");
    return;
  }

  if (success && accepted) {
    lua_pushboolean(L, 1);
  } else {
    lua_pushboolean(L, 0);
  }

  dmScript::PCall(L, 2, 0);

  dmScript::TeardownCallback(callback);
}

static int CPP_ShowPrompt(lua_State *L) {
  int top = lua_gettop(L);

  dmScript::LuaCallbackInfo *callback = dmScript::CreateCallback(L, 1);

#if defined(DM_PLATFORM_HTML5)
  JS_ShowPrompt((ShowPromptHandler)CPP_ShowPrompt_Handler, callback);
#endif

  assert(top == lua_gettop(L));
  return 0;
}

// ===============================================
// Init Shortcut Table
// ===============================================

static const luaL_reg Shortcut_methods[] = {
    {"can_show_prompt", CPP_CanShowPrompt},
    {"show_prompt", CPP_ShowPrompt},
    {0, 0}};

static int Init_Shortcut(lua_State *L) {
  int top = lua_gettop(L);

  lua_pushliteral(L, "shortcut");
  lua_newtable(L);
  luaL_register(L, NULL, Shortcut_methods);
  lua_settable(L, -3); // shortcut -> ysdk

  assert(top == lua_gettop(L));
  return 1;
}

#pragma endregion

#pragma region Clipboard

// ===============================================
// Write Text
// ===============================================

static int CPP_Clipboard_WriteText(lua_State *L) {
  int top = lua_gettop(L);

  const char *text = luaL_checkstring(L, 1);

#if defined(DM_PLATFORM_HTML5)
  JS_ClipboardWriteText(text);
#endif

  assert(top == lua_gettop(L));
  return 0;
}

// ===============================================
// Init Clipboard Table
// ===============================================

static const luaL_reg Clipboard_methods[] = {
    {"write_text", CPP_Clipboard_WriteText}, {0, 0}};

static int Init_Clipboard(lua_State *L) {
  int top = lua_gettop(L);

  lua_pushliteral(L, "clipboard");
  lua_newtable(L);
  luaL_register(L, NULL, Clipboard_methods);
  lua_settable(L, -3); // clipboard -> ysdk

  assert(top == lua_gettop(L));
  return 1;
}

#pragma endregion

#pragma region DeviceInfo

// ===============================================
// Init Device Info Table
// ===============================================

static int Init_DeviceInfo(lua_State *L) {
  int top = lua_gettop(L);

#if defined(DM_PLATFORM_HTML5)
  const char *result = JS_GetDeviceInfo();
#else
  const char *result = "{\"type\":\"desktop\",\"isMobile\":false,\"isDesktop\":"
                       "true,\"isTablet\":false,\"isTV\":false}";
#endif

  lua_pushliteral(L, "device_info");
  dmScript::JsonToLua(L, result, strlen(result));
  lua_settable(L, -3);

  assert(top == lua_gettop(L));
  return 1;
}

#pragma endregion

#pragma region Flags

// ===============================================
// Get Flags
// ===============================================

static void CPP_GetFlags_Handler(dmScript::LuaCallbackInfo *callback,
                                 const int success, const char *json) {
  lua_State *L = dmScript::GetCallbackLuaContext(callback);

  if (!dmScript::SetupCallback(callback)) {
    dmLogError("Failed to setup callback");
    return;
  }

  if (success) {
    dmScript::JsonToLua(L, json, strlen(json));
  } else {
    lua_pushnil(L);
  }

  dmScript::PCall(L, 3, 0);

  dmScript::TeardownCallback(callback);
}

static int CPP_GetFlags(lua_State *L) {
  int top = lua_gettop(L);

  dmScript::LuaCallbackInfo *callback = dmScript::CreateCallback(L, 1);
  char *params;
  if (lua_isnoneornil(L, 2)) {
    params = NULL;
  } else {
    params = dmYandex::LuaTableToJSON(L, 2);
  }

#if defined(DM_PLATFORM_HTML5)
  JS_GetFlags((GetFlagsHandler)CPP_GetFlags_Handler, callback, params);
#endif

  free(params);

  assert(top == lua_gettop(L));
  return 0;
}

#pragma endregion

static const luaL_reg Module_methods[] = {{"get_flags", CPP_GetFlags},
                                          {"on_event", CPP_OnEvent},
                                          {"dispatch_event", CPP_DispatchEvent},
                                          {0, 0}};

static void LuaInit(lua_State *L) {
  int top = lua_gettop(L);

  luaL_register(L, MODULE_NAME, Module_methods);

  Init_Features(L);
  Init_Payments(L);
  Init_Player(L);
  Init_Feedback(L);
  Init_Environment(L);
  Init_Adv(L);
  Init_Leaderboards(L);
  Init_Screen(L);
  Init_Shortcut(L);
  Init_Clipboard(L);
  Init_DeviceInfo(L);

  lua_pop(L, 1);

  assert(top == lua_gettop(L));
}

static dmExtension::Result
AppInitializeYandexGames(dmExtension::AppParams *params) {
  // dmLogInfo("AppInitializeYandexGames");
  return dmExtension::RESULT_OK;
}

static dmExtension::Result InitializeYandexGames(dmExtension::Params *params) {
  LuaInit(params->m_L);
  // dmLogInfo("Registered %s Extension", MODULE_NAME);
  return dmExtension::RESULT_OK;
}

static dmExtension::Result
AppFinalizeYandexGames(dmExtension::AppParams *params) {
  // dmLogInfo("AppFinalizeYandexGames");
  return dmExtension::RESULT_OK;
}

static dmExtension::Result FinalizeYandexGames(dmExtension::Params *params) {
  // dmLogInfo("FinalizeYandexGames");
  return dmExtension::RESULT_OK;
}

static dmExtension::Result OnUpdateYandexGames(dmExtension::Params *params) {
  // dmLogInfo("OnUpdateYandexGames");
  return dmExtension::RESULT_OK;
}

static void OnEventYandexGames(dmExtension::Params *params,
                               const dmExtension::Event *event) {
  switch (event->m_Event) {
  case dmExtension::EVENT_ID_ACTIVATEAPP:
    // dmLogInfo("OnEventYandexGames - EVENT_ID_ACTIVATEAPP");
    break;
  case dmExtension::EVENT_ID_DEACTIVATEAPP:
    // dmLogInfo("OnEventYandexGames - EVENT_ID_DEACTIVATEAPP");
    break;
  case dmExtension::EVENT_ID_ICONIFYAPP:
    // dmLogInfo("OnEventYandexGames - EVENT_ID_ICONIFYAPP");
    break;
  case dmExtension::EVENT_ID_DEICONIFYAPP:
    // dmLogInfo("OnEventYandexGames - EVENT_ID_DEICONIFYAPP");
    break;
  default:
    // dmLogWarning("OnEventYandexGames - Unknown event id");
    break;
  }
}

DM_DECLARE_EXTENSION(EXTENSION_SYMBOL, LIB_NAME, AppInitializeYandexGames,
                     AppFinalizeYandexGames, InitializeYandexGames,
                     OnUpdateYandexGames, OnEventYandexGames,
                     FinalizeYandexGames);
