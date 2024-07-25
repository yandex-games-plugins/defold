if ysdk then return end
ysdk = {}

-- THIS IS NOT AN IMPLEMENTATION OF YANDEX.GAMES SDK
-- THE MAIN PURPOSE OF THIS FILE IS TO PROVIDE A MOCK FOR THE SDK TO WORK IN THE EDITOR
-- AND TO PROVIDE A TYPE ANNOTATIONS FOR THE SDK

-- region Features

ysdk.features = {
  loading_api = {
    ready = function()
      print("loading_ready")
    end
  }
}

-- endregion

-- region Payments

local payments = {}

---@class YSDK_Purchase
---@field product_id string product ID.
---@field purchase_token string Token entitling the buyer to use the purchase.
---@field developer_payload string Optional parameter. Additional purchase data that you want to send to your server (transferred in the signature parameter).

---@param callback fun(self: any, purchase: YSDK_Purchase|nil, signature: string|nil)
---@param options {id: string, developer_payload: string|nil, signed: boolean|nil}
function payments.create_purchase(callback, options)
  print("purchase")
end

---@param callback fun(self: any, purchases: YSDK_Purchase[]|nil, signature: string|nil)
---@param options { signed: string|nil }
function payments.get_purchases(callback, options)
  print("get_purchases")
end

---@class YSDK_Product
---@field id string Product ID.
---@field title string Product name.
---@field description string Product description.
---@field image_uri string URL of the product image.
---@field price string Product price in <price> <currency code> format. For example, "25 YAN".
---@field price_value string Product price in <price> format. For example, "25".
---@field price_currency_code string Currency code ("YAN").
---@field price_currency_image {small: string, medium: string, svg: string} Currency image URLs.

---@param callback fun(self: any, products: YSDK_Product[]|nil): nil
function payments.get_catalog(callback)
  print("get_catalog")
end

---@param purchaseToken string String, a token returned by the create_purchase() and get_purchases() methods.
function payments.consume_purchase(purchaseToken)
  print("consume_purchase")
end

ysdk.payments = payments

-- endregion

-- region Player

local player = {}

---@class YSDK_Player_Info
---@field logged_in boolean
---@field unique_id string
---@field name string
---@field payingStatus "paying"|"partially_paying"|"not_paying"|"unknown"
---@field photo PhotoTable

---@param callback fun(self: any, player: YSDK_Player_Info|nil, signature: string|nil): nil
---@param options {scopes: boolean|nil, signed: boolean|nil}
function player.get_info(callback, options)
  print("get_info")
end

---@param callback fun(self: any, authorized: boolean): nil
function player.open_auth_dialog(callback)
  print("open_auth_dialog")
end

---@param callback fun(self: any, ids: {app_id: number, user_id: string}[]): nil
function player.get_ids_per_game(callback)
  print("get_ids_per_game")
end

---@param callback fun(self: any, data: table<string, any>|nil): nil
---@param keys string[]
function player.get_data(callback, keys)
  print("get_data")
end

---@param data table<string, any>
---@param flush boolean|nil
function player.set_data(data, flush)
  print("set_data")
end

---@param callback fun(self: any, data: table<string, number>|nil): nil
---@param keys string[]
function player.get_stats(callback, keys)
  print("get_stats")
end

---@param increments table<string, number>
function player.increment_stats(increments)
  print("increment_stats")
end

---@param stats table<string, number>
function player.set_stats(stats)
  print("set_stats")
end

ysdk.player = player

-- endregion

-- region Feedback

local feedback = {}

---@alias CantReviewReason
---| "NO_AUTH" The user isn't logged in.
---| "GAME_RATED" The user already rated the game.
---| "REVIEW_ALREADY_REQUESTED" A request was sent, now awaiting the user's action.
---| "REVIEW_WAS_REQUESTED" A request was sent and the user performed an action (gave a rating or closed the pop-up window).
---| "UNKNOWN" A request wasn't sent because an error occurred on the Yandex side.

---@param callback fun(self: any, can_review: boolean, reason: CantReviewReason|nil): nil
function feedback.can_review(callback)
  print("can_review")
end

---@param callback fun(self: any, feedback_sent: boolean): nil
function feedback.request_review(callback)
  print("request_review")
end

ysdk.feedback = feedback

-- endregion

-- region Environment

---@class YSDK_Environment
---@field app _YSDK_App Game data.
---@field browser _YSDK_Browser Browser data.
---@field i18n _YSDK_I18N Service internationalization.
---@field payload string|nil The value of the payload parameter from the game's address. Optional. For example, in https://yandex.ru/games/app/123?payload=test you can return test as follows: ysdk.environment.payload.

---@class _YSDK_App
---@field id string Game ID.

---@class _YSDK_Browser
---@field lang string Preferred browser language in ISO 639-1 format.

---@class _YSDK_I18N
---@field lang string The Yandex Games interface language in ISO 639-1 format. For example, "tr" means that the game is currently running under the Yandex Games Turkish interface. We recommend using this parameter to determine the user's language in the game.
---@field tld string Top-level domain. For example, "com" means that the game is currently running under the Yandex Games international domain. When hosting a game in your domain, please keep in mind that it must open correctly under any Yandex domain.

---@type YSDK_Environment
ysdk.environment = {
  app = {
    id = "0"
  },
  browser = {
    lang = "en"
  },
  i18n = {
    lang = "en",
    tld = "com"
  }
}

-- endregion

-- region Adv

local adv = {}

-- region Fullscreen

---@class YSDK_FullscreenAdv_Callbacks
---@field on_open (fun(self: any): nil)|nil Called when an ad is opened successfully.
---@field on_close (fun(self: any, was_shown: boolean): nil)|nil Called when an ad is closed, an error occurred, or an ad failed to open due to too frequent calls. Used with the wasShown argument (type boolean), the value of which indicates whether an ad was shown.
---@field on_error (fun(self: any, error: string): nil)|nil Called when an error occurs. The error object is passed to the callback function.
---@field on_offline (fun(self: any): nil)|nil Called when the network connection is lost (when offline mode is enabled).

---@param callbacks YSDK_FullscreenAdv_Callbacks
function adv.show_fullscreen_adv(callbacks)
  print("show_fullscreen_adv")
end

-- endregion

-- region Rewarded

---@class YSDK_RewardedAdv_Callbacks
---@field on_open (fun(self: any): nil)|nil Called when a video ad is displayed on the screen.
---@field on_close (fun(self: any): nil)|nil Called when a user closes a video ad.
---@field on_rewarded (fun(self: any): nil)|nil Called when a video ad impression is counted. Use this function to specify a reward for viewing the video ad.
---@field on_error (fun(self: any, error: string): nil)|nil Called when an error occurs. The error object is passed to the callback function.

---@param callbacks YSDK_RewardedAdv_Callbacks
function adv.show_rewarded_video(callbacks)
  print("show_rewarded_adv")
end

-- endregion

-- region Sticky Banner

---@alias StickyNotShowingReason
---| "ADV_IS_NOT_CONNECTED" Banners aren't connected.
---| "UNKNOWN" A request wasn't sent because an error occurred on the Yandex side.

---@param callback fun(self: any, sticky_adv_is_showing: boolean, reason: StickyNotShowingReason|nil)
function adv.get_banner_adv_status(callback)
  print("get_banner_adv_status")
end

function adv.show_banner_adv()
  print("show_banner_adv")
end

function adv.hide_banner_adv()
  print("hide_banner_adv")
end

-- endregion

ysdk.adv = adv

-- endregion

-- region Events

---@alias SDKEvent "EXIT" | "HISTORY_BACK"

---@param eventName SDKEvent
---@param listener fun(self: any)
function ysdk.on_event(eventName, listener)
  print("on_event", eventName)
end

---@param eventName SDKEvent
---@param detail table|nil
function ysdk.dispatch_event(eventName, detail)
  print("dispatch_event", eventName)
end

-- endregion

-- region Leaderboards

local leaderboards = {}

---@class YSDK_Leaderboard_Description
---@field app_id string Application ID.
---@field default boolean If true, then it is the primary leaderboard.
---@field invert_sort_order boolean false - rankings are sorted in descending order. true - rankings are sorted in ascending order.
---@field decimal_offset number Score offset. For example, when decimal_offset: 2 1234 will be displayed as 12.34.
---@field type "numeric"|"time" Leaderboard result type. Available parameters: numeric (number), time (seconds).
---@field name string Leaderboard name.
---@field title YSDK_Language_Table Localized names.

---@param leaderboard_name string Leaderboard name.
---@param callback fun(self: any, description: YSDK_Leaderboard_Description|nil): nil
function leaderboards.get_description(leaderboard_name, callback)
  print("leaderboards.get_description")
end

---@param leaderboard_name string Leaderboard name.
---@param score integer Score. Only the integer type is accepted. Must be greater than 0. If the leaderboard type is time, the values must be passed in milliseconds.
---@param extraData string|nil User description. Optional.
function leaderboards.set_score(leaderboard_name, score, extraData)
  print("leaderboards.set_score")
end

---@class YSDK_Leaderboard_Entry
---@field score integer Score. Only the integer type is accepted. Must be greater than 0. If the leaderboard type is time, the values must be passed in milliseconds.
---@field extraData string|nil User description. Optional.
---@field rank number
---@field avatar_src PhotoTable URLs of a user's photo. Available values for size: small, medium, and large.
---@field avatar_srcset PhotoTable examplesets of a user's photo that is suitable for Retina displays. Available values for size: small, medium, and large.
---@field lang string
---@field public_name string
---@field unique_id string
---@field formatted_score string

---@param leaderboard_name string Leaderboard name.
---@param callback fun(self: any, player_entry: YSDK_Leaderboard_Entry|nil): nil
function leaderboards.get_player_entry(leaderboard_name, callback)
  print("leaderboards.get_player_entry")
end

---@class YSDK_Leaderboard_Entries
---@field leaderboard YSDK_Leaderboard_Description Leaderboard description.
---@field ranges {start: integer, size: integer}[] Ranking ranges in the response.
---@field user_rank integer User's rank. Returns 0 if none or if the request is for the top of the table without including the user.
---@field entries YSDK_Leaderboard_Entry[] Requested entries.

---@class YSDK_Get_Entries_Options
---@field include_user boolean|nil Defines whether to include the logged-in user in the response.
---@field quantity_around number|nil Number of entries to return below and above the user in the leaderboard. The minimum value is 1, the maximum value is 10. The default is 5.
---@field quantity_top number|nil Number of entries from the top of the leaderboard. The minimum value is 1, the maximum value is 20. The default is 5.

---@param leaderboard_name string Leaderboard name.
---@param callback fun(self: any, entries: YSDK_Leaderboard_Entries|nil): nil
---@param options YSDK_Get_Entries_Options|nil
function leaderboards.get_entries(leaderboard_name, callback, options)
  print("leaderboards.get_entries")
end

ysdk.leaderboards = leaderboards

-- endregion

-- region Shortcut

local shortcut = {}

---@param callback fun(self: any, can_show: boolean): nil
function shortcut.can_show_prompt(callback)
  print("can_show_shortcut_prompt")
end

---@param callback fun(self: any, accepted: boolean): nil
function shortcut.show_prompt(callback)
  print("show_shortcut_prompt")
end

ysdk.shortcut = shortcut

-- endregion

-- region Screen

---@class YSDK_Screen
---@field fullscreen YSDK_Screen_Fullscreen Flag to switch to full-screen mode when opening the game or on the first user action. Default value: true.
---@field orientation YSDK_Screen_Orientation Screen settings during the game.

---@class YSDK_Screen_Fullscreen
---@field status fun():"on"|"off" Returns current fullscreen status. "on"/"off"
---@field request function Request to switch to full-screen mode.
---@field exit function Request to leave full-screen mode.

---@class YSDK_Screen_Orientation
---@field get fun():"portrait"|"landscape" Returns screen orientation.
---@field set fun(value: "portrait"|"landscape") Locks screen orientation.

local mock_fullscreen = "off";
local mock_orientation = "landscape";

---@type YSDK_Screen
ysdk.screen = {
  fullscreen = {
    status = function() return mock_fullscreen end,
    request = function() mock_fullscreen = "on" end,
    exit = function() mock_fullscreen = "off" end
  },
  orientation = {
    get = function() return mock_orientation end,
    set = function(value) mock_orientation = value end
  }
}


-- endregion

-- region Clipboard

local clipboard = {}

---@param text string
function clipboard.write_text(text)
  print("clipboard_write_text", text)
end

ysdk.clipboard = clipboard;

-- endregion

-- region DeviceInfo

---@class YSDK_DeviceInfo
---@field type "mobile"|"desktop"|"tablet"|"tv"
---@field isMobile boolean
---@field isDesktop boolean
---@field isTablet boolean
---@field isTV boolean

---@type YSDK_DeviceInfo
ysdk.device_info = {
  type = "desktop",
  isMobile = false,
  isDesktop = true,
  isTablet = false,
  isTV = false
}

-- endregion

-- region Flags

---@class YSDK_ClientFeature
---@field name string
---@field value string

---@class YSDK_GetFlagsParams
---@field defaultFlags table<string, string>|nil
---@field clientFeatures YSDK_ClientFeature[]|nil 

---@param params YSDK_GetFlagsParams|nil
---@param callback fun(self: any, flags: table<string, string>): nil
ysdk.get_flags = function(params, callback)
  print("getFlags")
end

-- endregion

-- region Types

---@class PhotoTable
---@field small string
---@field medium string
---@field large string

---@class YSDK_Language_Table
---@field af string|nil
---@field am string|nil
---@field ar string|nil
---@field az string|nil
---@field be string|nil
---@field bg string|nil
---@field bn string|nil
---@field ca string|nil
---@field cs string|nil
---@field da string|nil
---@field de string|nil
---@field el string|nil
---@field en string|nil
---@field es string|nil
---@field et string|nil
---@field eu string|nil
---@field fa string|nil
---@field fi string|nil
---@field fr string|nil
---@field gl string|nil
---@field he string|nil
---@field hi string|nil
---@field hr string|nil
---@field hu string|nil
---@field hy string|nil
---@field id string|nil
---@field is string|nil
---@field it string|nil
---@field ja string|nil
---@field ka string|nil
---@field kk string|nil
---@field km string|nil
---@field kn string|nil
---@field ko string|nil
---@field ky string|nil
---@field lo string|nil
---@field lt string|nil
---@field lv string|nil
---@field mk string|nil
---@field ml string|nil
---@field mn string|nil
---@field mr string|nil
---@field ms string|nil
---@field my string|nil
---@field ne string|nil
---@field nl string|nil
---@field no string|nil
---@field pl string|nil
---@field pt string|nil
---@field ro string|nil
---@field ru string|nil
---@field si string|nil
---@field sk string|nil
---@field sl string|nil
---@field sr string|nil
---@field sv string|nil
---@field sw string|nil
---@field ta string|nil
---@field te string|nil
---@field tg string|nil
---@field th string|nil
---@field tk string|nil
---@field tl string|nil
---@field tr string|nil
---@field uk string|nil
---@field ur string|nil
---@field uz string|nil
---@field vi string|nil
---@field zh string|nil
---@field zu string|nil

---@alias YSDK_TLD
--- | "az"
--- | "by"
--- | "co.il"
--- | "com"
--- | "com.am"
--- | "com.ge"
--- | "com.tr"
--- | "ee"
--- | "fr"
--- | "kg"
--- | "kz"
--- | "lt"
--- | "lv"
--- | "md"
--- | "ru"
--- | "tj"
--- | "tm"
--- | "ua"
--- | "uz"

-- endregion
