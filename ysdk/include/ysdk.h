#pragma once

#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_HTML5)

#pragma region Features

// ===============================================
// Loading API
// ===============================================

extern "C" {
void JS_LoadingAPI_Ready();
}

// ===============================================
// Gameplay API
// ===============================================

extern "C" {
void JS_GameplayAPI_Start();
void JS_GameplayAPI_Stop();
}


#pragma endregion

#pragma region Payments

// ===============================================
// Create Purchase
// ===============================================

typedef void (*CreatePurchaseHandler)(dmScript::LuaCallbackInfo *callback,
                                      const int success, const char *jsons,
                                      const char *signature);

extern "C" {
void JS_CreatePurchase(CreatePurchaseHandler handler,
                       dmScript::LuaCallbackInfo *callback, const char *params);
}

// ===============================================
// Open Auth Dialog
// ===============================================

typedef void (*OpenAuthDialogHandler)(dmScript::LuaCallbackInfo *callback,
                                      const int success);

extern "C" {
void JS_OpenAuthDialog(OpenAuthDialogHandler handler,
                       dmScript::LuaCallbackInfo *callback);
}

// ===============================================
// Get Purchases
// ===============================================

typedef void (*GetPurchasesHandler)(dmScript::LuaCallbackInfo *callback,
                                    const int success, const char *jsons,
                                    const char *signature);

extern "C" {
void JS_GetPurchases(GetPurchasesHandler handler,
                     dmScript::LuaCallbackInfo *callback, const char *params);
}

// ===============================================
// Get Catalog
// ===============================================

typedef void (*GetCatalogHandler)(dmScript::LuaCallbackInfo *callback,
                                  const int success, const char *jsons);

extern "C" {
void JS_GetCatalog(GetCatalogHandler handler,
                   dmScript::LuaCallbackInfo *callback);
}

// ===============================================
// Consume Purchase
// ===============================================

extern "C" {
void JS_ConsumePurchase(const char *purchaseToken);
}

#pragma endregion

#pragma region Player

// ===============================================
// Get Player Info
// ===============================================

typedef void (*GetPlayerInfoHandler)(dmScript::LuaCallbackInfo *callback,
                                     const int success, const char *jsons,
                                     const char *signature);

extern "C" {
void JS_GetPlayerInfo(GetPlayerInfoHandler handler,
                      dmScript::LuaCallbackInfo *callback, const char *params);
}

// ===============================================
// Get Player IDs Per Game
// ===============================================

typedef void (*GetPlayerIDsPerGameHandler)(dmScript::LuaCallbackInfo *callback,
                                           const int success, const char *json);

extern "C" {
void JS_GetPlayerIDsPerGame(GetPlayerIDsPerGameHandler handler,
                            dmScript::LuaCallbackInfo *callback);
}

// ===============================================
// Get Player Data
// ===============================================

typedef void (*GetPlayerDataHandler)(dmScript::LuaCallbackInfo *callback,
                                     const int success, const char *json);

extern "C" {
void JS_GetPlayerData(GetPlayerDataHandler handler,
                      dmScript::LuaCallbackInfo *callback, const char *keys);
}

// ===============================================
// Set Player Data
// ===============================================

extern "C" {
void JS_SetPlayerData(const char *data, const int flush);
}

// ===============================================
// Get Player Stats
// ===============================================

typedef void (*GetPlayerStatsHandler)(dmScript::LuaCallbackInfo *callback,
                                      const int success, const char *json);

extern "C" {
void JS_GetPlayerStats(GetPlayerStatsHandler handler,
                       dmScript::LuaCallbackInfo *callback, const char *keys);
}

// ===============================================
// Set Player Stats
// ===============================================

extern "C" {
void JS_SetPlayerStats(const char *stats);
}

// ===============================================
// Increment Player Stats
// ===============================================

extern "C" {
void JS_IncrementPlayerStats(const char *increments);
}

#pragma endregion

#pragma region Feedback

// ===============================================
// Can Review
// ===============================================

typedef void (*CanReviewHandler)(dmScript::LuaCallbackInfo *callback,
                                 const int success, const int canReview,
                                 const char *reason);

extern "C" {
void JS_CanReview(CanReviewHandler handler,
                  dmScript::LuaCallbackInfo *callback);
}

// ===============================================
// Request Review
// ===============================================

typedef void (*RequestReviewHandler)(dmScript::LuaCallbackInfo *callback,
                                     const int success, const int feedbackSent);

extern "C" {
void JS_RequestReview(RequestReviewHandler handler,
                      dmScript::LuaCallbackInfo *callback);
}

#pragma endregion

#pragma region Environment

extern "C" {
char *JS_GetEnvironment();
}

#pragma endregion

#pragma region Adv

// ===============================================
// Fullscreen Adv
// ===============================================

typedef void (*ShowFullscreenAdvHandler)(dmScript::LuaCallbackInfo *onOpen,
                                         dmScript::LuaCallbackInfo *onClose,
                                         dmScript::LuaCallbackInfo *onError,
                                         dmScript::LuaCallbackInfo *onOffline,
                                         const int callbackType,
                                         const char *data);

extern "C" {
void JS_ShowFullscreenAdv(ShowFullscreenAdvHandler handler,
                          dmScript::LuaCallbackInfo *onOpen,
                          dmScript::LuaCallbackInfo *onClose,
                          dmScript::LuaCallbackInfo *onError,
                          dmScript::LuaCallbackInfo *onOffline);
}

// ===============================================
// Rewarded Video
// ===============================================

typedef void (*ShowRewardedVideoHandler)(dmScript::LuaCallbackInfo *onOpen,
                                         dmScript::LuaCallbackInfo *onRewarded,
                                         dmScript::LuaCallbackInfo *onClose,
                                         dmScript::LuaCallbackInfo *onError,
                                         const int callbackType,
                                         const char *data);

extern "C" {
void JS_ShowRewardedVideo(ShowRewardedVideoHandler handler,
                          dmScript::LuaCallbackInfo *onOpen,
                          dmScript::LuaCallbackInfo *onRewarded,
                          dmScript::LuaCallbackInfo *onClose,
                          dmScript::LuaCallbackInfo *onError);
}

// ===============================================
// Sticky Banner
// ===============================================

typedef void (*GetBannerAdvStatusHandler)(dmScript::LuaCallbackInfo *callback,
                                          const int success,
                                          const int stickyAdvIsShowing,
                                          const char *reason);

extern "C" {
void JS_GetBannerAdvStatus(GetBannerAdvStatusHandler handler,
                           dmScript::LuaCallbackInfo *callback);
void JS_ShowBannerAdv();
void JS_HideBannerAdv();
}

#pragma endregion

#pragma region Events

typedef void (*OnEventHandler)(dmScript::LuaCallbackInfo *callback);

extern "C" {
void JS_OnEvent(OnEventHandler handler, dmScript::LuaCallbackInfo *callback,
                const char *eventName);
void JS_DispatchEvent(const char *eventName, const char *detail);
}

#pragma endregion

#pragma region Leaderboards

// ===============================================
// Get Leaderboard Description
// ===============================================

typedef void (*GetLeaderboardDescriptionHandler)(
    dmScript::LuaCallbackInfo *callback, const int success, const char *json);

extern "C" {
void JS_GetLeaderboardDescription(GetLeaderboardDescriptionHandler handler,
                                  dmScript::LuaCallbackInfo *callback,
                                  const char *leaderboardName);
}

// ===============================================
// Set Leaderboard Score
// ===============================================

extern "C" {
void JS_SetLeaderboardScore(const char *leaderboardName, const char *score,
                            const char *extraData);
}

// ===============================================
// Get Leaderboard Player Entry
// ===============================================

typedef void (*GetLeaderboardPlayerEntryHandler)(
    dmScript::LuaCallbackInfo *callback, const int success, const char *json);

extern "C" {
void JS_GetLeaderboardPlayerEntry(GetLeaderboardPlayerEntryHandler handler,
                                  dmScript::LuaCallbackInfo *callback,
                                  const char *leaderboardName);
}

// ===============================================
// Get Leaderboard Entries
// ===============================================

typedef void (*GetLeaderboardEntriesHandler)(
    dmScript::LuaCallbackInfo *callback, const int success, const char *json);

extern "C" {
void JS_GetLeaderboardEntries(GetLeaderboardPlayerEntryHandler handler,
                              dmScript::LuaCallbackInfo *callback,
                              const char *leaderboardName, const char *params);
}

#pragma endregion

#pragma region Shortcut

// ===============================================
// Can Show Prompt
// ===============================================

typedef void (*CanShowPromptHandler)(dmScript::LuaCallbackInfo *callback,
                                     const int success,
                                     const int canShowPrompt);

extern "C" {
void JS_CanShowPrompt(CanShowPromptHandler handler,
                      dmScript::LuaCallbackInfo *callback);
}

// ===============================================
// Show Prompt
// ===============================================

typedef void (*ShowPromptHandler)(dmScript::LuaCallbackInfo *callback,
                                  const int success, const int accepted);

extern "C" {
void JS_ShowPrompt(ShowPromptHandler handler,
                   dmScript::LuaCallbackInfo *callback);
}

#pragma endregion

#pragma region Screen

// ===============================================
// Fullscreen
// ===============================================

extern "C" {
char *JS_Screen_Fullscreen_GetStatus();
void JS_Screen_Fullscreen_Request();
void JS_Screen_Fullscreen_Exit();
}

// ===============================================
// Orientation
// ===============================================

extern "C" {
char *JS_Screen_Orientation_Get();
void JS_Screen_Orientation_Set(const char *value);
}

#pragma endregion

#pragma region Clipboard

extern "C" {
void JS_ClipboardWriteText(const char *text);
}

#pragma endregion

#pragma region DeviceInfo

extern "C" {
char *JS_GetDeviceInfo();
}

#pragma endregion

#pragma region Flags

// ===============================================
// Get Flags
// ===============================================

typedef void (*GetFlagsHandler)(dmScript::LuaCallbackInfo *callback,
                                const int success, const char *json);

extern "C" {
void JS_GetFlags(GetFlagsHandler handler, dmScript::LuaCallbackInfo *callback,
                 const char *params);
}

#pragma endregion

#endif