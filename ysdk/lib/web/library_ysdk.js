let LisGamesSDKLib = {
  $YGDefold: {
    allocateString: function (str) {
      const size = lengthBytesUTF8(str) + 1;
      const idx = _malloc(size);
      stringToUTF8Array(str, HEAP8, idx, size);
      return idx;
    },

    allocateJSON: function (str) {
      return YGDefold.allocateString(JSON.stringify(str));
    },
  },

//#region Features

  JS_LoadingAPI_Ready: function () {
    if (window.ysdk.features.LoadingAPI) {
      window.ysdk.features.LoadingAPI.ready();
    }
  },

  JS_GameplayAPI_Start: function () {
    if (window.ysdk.features.GameplayAPI) {
      window.ysdk.features.GameplayAPI.start();
    }
  },

  JS_GameplayAPI_Stop: function () {
    if (window.ysdk.features.GameplayAPI) {
      window.ysdk.features.GameplayAPI.stop();
    }
  },

  JS_GamesAPI_GetAllGames: function (handler, callback) {
    if (window.ysdk.features.GamesAPI) {
      window.ysdk.features.GamesAPI.getAllGames()
        .then(function (result) {
          {{{ makeDynCall('viii', 'handler') }}}(callback, 1, YGDefold.allocateJSON(result))
        })
        .catch(function () {
          {{{ makeDynCall('viiii', 'handler') }}}(callback, 0, 0)
        });
    }
  },

  JS_GamesAPI_GetGameByID: function (handler, callback, id) {
    if (window.ysdk.features.GamesAPI) {
      window.ysdk.features.GamesAPI.getGameByID(id)
        .then(function (result) {
          {{{ makeDynCall('viii', 'handler') }}}(callback, 1, YGDefold.allocateJSON(result))
        })
        .catch(function () {
          {{{ makeDynCall('viiii', 'handler') }}}(callback, 0, 0)
        });
    }
  },

//#endregion

//#region Payments

  JS_CreatePurchase: function (handler, callback, cparams) {
    const params = JSON.parse(UTF8ToString(cparams));

    window.ysdk.getPayments({ signed: params.signed ?? false })
      .then(function (payments) {
        return payments.purchase({ 
          id: params.id,
          developerPayload: params.developer_payload ?? ''
        });
      })
      .then(function (purchase) {
        const cpurchase = YGDefold.allocateJSON({
          product_id: purchase.productID,
          purchase_token: purchase.purchaseToken,
          developer_payload: purchase.developerPayload,
        });
        const csignature = YGDefold.allocateString(purchase.signature ?? '');
        {{{ makeDynCall('viiii', 'handler') }}}(callback, 1, cpurchase, csignature)
      })
      .catch(function () {
        {{{ makeDynCall('viiii', 'handler') }}}(callback, 0, 0, 0)
      });
  },

  JS_GetPurchases: function (handler, callback, cparams) {
    const params = JSON.parse(UTF8ToString(cparams));

    window.ysdk.getPayments({ signed: params.signed ?? false })
      .then(function (payments) {
        return payments.getPurchases();
      })
      .then(function (purchases) {
        const cpurchase = YGDefold.allocateJSON(purchases.map(function (purchase) {
          return {
            product_id: purchase.productID,
            purchase_token: purchase.purchaseToken,
            developer_payload: purchase.developerPayload,
          };
        }));
        const csignature = YGDefold.allocateString(purchases.signature ?? '');
        {{{ makeDynCall('viiii', 'handler') }}}(callback, 1, cpurchase, csignature)
      })
      .catch(function () {
        {{{ makeDynCall('viiii', 'handler') }}}(callback, 0, 0, 0)
      });
  },

  JS_GetCatalog: function (handler, callback) {
    window.ysdk.getPayments()
      .then(function (payments) {
        return payments.getCatalog();
      })
      .then(function (purchases) {
        const ccatalog = YGDefold.allocateJSON(purchases.map(function (product) {
          return {
            id: product.id,
            title: product.title,
            description: product.description,
            image_uri: product.image_uri,
            price: product.price,
            price_value: product.price_value,
            price_currency_code: product.price_currency_code,
            price_currency_image: {
              small: product.getPriceCurrencyImage("small"),
              medium: product.getPriceCurrencyImage("medium"),
              svg: product.getPriceCurrencyImage("svg"),
            }
          }
        }));
        {{{ makeDynCall('viii', 'handler') }}}(callback, 1, ccatalog)
      })
      .catch(function () {
        {{{ makeDynCall('viii', 'handler') }}}(callback, 0, 0)
      });
  },

  JS_ConsumePurchase: function (handler, callback, cpurchaseToken) {
    const purchaseToken = UTF8ToString(cpurchaseToken);

    window.ysdk.getPayments()
      .then(function (payments) {
        return payments.consumePurchase(purchaseToken);
      }).then(function () {
        if (callback) {
          {{{ makeDynCall('vii', 'handler') }}}(callback, 1)
        }
      }).catch(function () {
        if (callback) {
          {{{ makeDynCall('vii', 'handler') }}}(callback, 0)
        }
      });
  },

//#endregion

//#region Player

  JS_GetPlayerInfo: function (handler, callback, cparams) {    
    const params = cparams ? JSON.parse(UTF8ToString(cparams)) : undefined;

    window.ysdk.getPlayer({
      signed: params?.signed ?? false,
      scopes: params?.scopes ?? false
    })
      .then(function (player) {
        const cplayerInfo = YGDefold.allocateJSON({
          logged_in: player.getMode() !== 'lite',
          unique_id: player.getUniqueID() ?? "",
          name: player.getName() ?? "",
          photo: {
            small: player.getPhoto('small') ?? "",
            medium: player.getPhoto('medium') ?? "",
            large: player.getPhoto('large') ?? "",
          },
          paying_status: player.getPayingStatus() ?? "",
        });

        const csignature = YGDefold.allocateString(player.signature ?? '');

        {{{ makeDynCall('viiii', 'handler') }}}(callback, 1, cplayerInfo, csignature)
      })
      .catch(function () {
        {{{ makeDynCall('viiii', 'handler') }}}(callback, 0, 0, 0)
      });
  },

  JS_OpenAuthDialog: function (handler, callback) {
    window.ysdk.auth.openAuthDialog()
      .then(function () {
        {{{ makeDynCall('vi', 'handler') }}}(callback, 1)
      })
      .catch(function () {
        {{{ makeDynCall('vi', 'handler') }}}(callback, 0)
      });
  },

  JS_GetPlayerIDsPerGame: function (handler, callback) {
    window.ysdk.isAvailableMethod('player.getIDsPerGame').then(function (available) {
      if (available) {
        window.ysdk.getPlayer()
          .then(function (player) {
            return player.getIDsPerGame();
          })
          .then(function (ids) {
            {{{ makeDynCall('viii', 'handler') }}}(
              callback,
               1, 
              YGDefold.allocateJSON(
                ids.map(function (id) {
                  return {
                    app_id: id.appID,
                    user_id: id.userID
                  }
                })
              )
            )
          })
          .catch(function () {
            {{{ makeDynCall('viii', 'handler') }}}(callback, 0, 0)
          });
      } else {
        {{{ makeDynCall('viii', 'handler') }}}(callback, 0, 0)
      }
    }).catch(function () {
      {{{ makeDynCall('viii', 'handler') }}}(callback, 0, 0)
    });
  },

  JS_GetPlayerData: function (handler, callback, ckeys) {
    let keys;

    if (ckeys) {
      keys = JSON.parse(UTF8ToString(ckeys));
    }
    
    window.ysdk.getPlayer()
      .then(function (player) {
        return player.getData(keys);
      })
      .then(function (data) {
        {{{ makeDynCall('viii', 'handler') }}}(callback, 1, YGDefold.allocateJSON(data))
      })
      .catch(function () {
        {{{ makeDynCall('viii', 'handler') }}}(callback, 0, 0)
      });
  },

  JS_SetPlayerData: function (cdata, cflush) {
    const data = JSON.parse(UTF8ToString(cdata));
    const flush = cflush == 1;
    
    window.ysdk
      .getPlayer()
      .then(function (player) {
        player.setData(data, flush);
      });
  },

  JS_GetPlayerStats: function (handler, callback, ckeys) {
    let keys;

    if (ckeys) {
      keys = JSON.parse(UTF8ToString(ckeys));
    }
    
    window.ysdk
      .getPlayer()
      .then(function (player) {
        return player.getStats(keys);
      })
      .then(function (stats) {
        {{{ makeDynCall('viii', 'handler') }}}(callback, 1, YGDefold.allocateJSON(stats))
      })
      .catch(function () {
        {{{ makeDynCall('viii', 'handler') }}}(callback, 0, 0)
      });
  },

  JS_IncrementPlayerStats: function (cstats) {
    const stats = JSON.parse(UTF8ToString(cstats));
    
    window.ysdk
      .getPlayer()
      .then(function (player) {
        player.setStats(stats);
      });
  },

  JS_SetPlayerStats: function (cstats) {
    const stats = JSON.parse(UTF8ToString(cstats));
    
    window.ysdk
      .getPlayer()
      .then(function (player) {
        player.setStats(stats);
      });
  },

//#endregion

//#region Feedback

  JS_CanReview: function (handler, callback) {
    ysdk.feedback
      .canReview()
      .then(function (response) {
          {{{ makeDynCall('viiii', 'handler') }}}(callback, 1, response.value, YGDefold.allocateString(repsonse.reason ?? ''))
      })
      .catch(function () {
        {{{ makeDynCall('viiii', 'handler') }}}(callback, 0, 0, YGDefold.allocateString(''))
      });
  },

  JS_RequestReview: function (handler, callback) {
    ysdk.feedback
      .requestReview()
      .then(function (response) {
          {{{ makeDynCall('viii', 'handler') }}}(callback, 1, response.feedbackSent)
      })
      .catch(function () {
        {{{ makeDynCall('viii', 'handler') }}}(callback, 0, 0)
      });
  },

//#endregion

//#region Environment

  JS_GetEnvironment: function () {
    const environment = {
      app: window.ysdk.environment.app,
      browser: window.ysdk.environment.browser,
      i18n: window.ysdk.environment.i18n,
      payload: window.ysdk.environment.payload,  
    };
    return YGDefold.allocateString(JSON.stringify(environment));
  },

//#endregion

//#region Adv

  JS_ShowFullscreenAdv: function (handler, onOpen, onClose, onError, onOffline) {
    window.ysdk.adv.showFullscreenAdv({
        callbacks: {
            onOpen: function() {
              {{{ makeDynCall('viiiiii', 'handler') }}}(onOpen, onClose, onError, onOffline, 0, YGDefold.allocateString(''));
            },
            onClose: function(wasShown) {
              {{{ makeDynCall('viiiiii', 'handler') }}}(onOpen, onClose, onError, onOffline, 1, YGDefold.allocateJSON(wasShown));
            },
            onError: function(error) {
              {{{ makeDynCall('viiiiii', 'handler') }}}(onOpen, onClose, onError, onOffline, 2, YGDefold.allocateString(error.toString()));
            },
            onOffline: function() {
              {{{ makeDynCall('viiiiii', 'handler') }}}(onOpen, onClose, onError, onOffline, 3, YGDefold.allocateString(''));
            }
        }
    });
  },

  JS_ShowRewardedVideo: function (handler, onOpen, onRewarded, onClose, onError) {   
    window.ysdk.adv.showRewardedVideo({
        callbacks: {
            onOpen: function() {
              {{{ makeDynCall('viiiiii', 'handler') }}}(onOpen, onRewarded, onClose, onError, 0, YGDefold.allocateString(''));
            },
            onRewarded: function() {
              {{{ makeDynCall('viiiiii', 'handler') }}}(onOpen, onRewarded, onClose, onError, 1, YGDefold.allocateString(''));
            },
            onClose: function() {
              {{{ makeDynCall('viiiiii', 'handler') }}}(onOpen, onRewarded, onClose, onError, 2, YGDefold.allocateString(''));
            },
            onError: function(error) { 
              {{{ makeDynCall('viiiiii', 'handler') }}}(onOpen, onRewarded, onClose, onError, 3, YGDefold.allocateString(error.toString()));
            }
        }
    });
  },

  JS_GetBannerAdvStatus: function(handler, callback) {
    ysdk.adv.getBannerAdvStatus()
      .then(function (response) {
        {{{ makeDynCall('viii', 'handler') }}}(callback, response.stickyAdvIsShowing, YGDefold.allocateString(response.reason ?? ''));
      })
      .catch(function () {
        {{{ makeDynCall('viii', 'handler') }}}(callback, 0, YGDefold.allocateString(''));
      });
  },

  JS_ShowBannerAdv: function () {
    ysdk.adv.showBannerAdv();
  },

  JS_HideBannerAdv: function () {
    ysdk.adv.hideBannerAdv();
  },

//#endregion

//#region Events

  JS_InitEvents: function (callEventCallback, destroyEventCallback) {
    const EVENTS = {
      "GAME_API_PAUSE": new Map(),
      "GAME_API_RESUME": new Map(),
      "EXIT": new Map(),
      "HISTORY_BACK": new Map()
    };

    YGDefold.events = {
      checkEventName: function (eventName) {
        const handlers = EVENTS[eventName];
    
        if (handlers === undefined) {
          console.error(`Unknown event name ${eventName}. Acceptable values: ${Object.keys(EVENTS).join(", ")}.`)
          return false;
        }

        return true;
      },

      registerCallback: function (eventName, cPointer, callback) {
        EVENTS[eventName].set(cPointer, callback);
      },

      destroyCallback: function (eventName, cPointer) {
        const handlers = EVENTS[eventName];

        const callback = handlers.get(cPointer);

        {{{ makeDynCall('vi', 'destroyEventCallback') }}}(callback);

        handlers.delete(cPointer);
      },
    }

    ysdk.on("game_api_pause", function () {
      for (const [, callback] of EVENTS["GAME_API_PAUSE"]) {
        {{{ makeDynCall('vi', 'callEventCallback') }}}(callback);
      }
    });

    ysdk.on("game_api_resume", function () {
      for (const [, callback] of EVENTS["GAME_API_RESUME"]) {
        {{{ makeDynCall('vi', 'callEventCallback') }}}(callback);
      }
    });

    ysdk.on("EXIT", function () {
      for (const [, callback] of EVENTS["EXIT"]) {
        {{{ makeDynCall('vi', 'callEventCallback') }}}(callback);
      }
    });

    ysdk.on("HISTORY_BACK", function () {
      for (const [, callback] of EVENTS["HISTORY_BACK"]) {
        {{{ makeDynCall('vi', 'callEventCallback') }}}(callback);
      }
    });
  },

  JS_OnEvent: function (ceventName, cPointer, callback) {
    const eventName = UTF8ToString(ceventName);

    if (YGDefold.events.checkEventName(eventName)) {
      YGDefold.events.registerCallback(eventName, cPointer, callback)
    }
  },

  JS_OffEvent: function (ceventName, cPointer) {
    const eventName = UTF8ToString(ceventName);

    if (YGDefold.events.checkEventName(eventName)) {
      YGDefold.events.destroyCallback(eventName, cPointer);
    }
  },

  JS_DispatchEvent: function (ceventName, cdetail) {
    const eventName = UTF8ToString(ceventName);
    const detail = JSON.parse(UTF8ToString(cdetail));
    ysdk.dispatchEvent(eventName, detail);
  },

//#endregion

//#region Leaderboard

  JS_GetLeaderboardDescription: function (handler, callback, cleaderboardName) {
    const leaderboardName = UTF8ToString(cleaderboardName);
    
    window.ysdk.getLeaderboards()
      .then(function (lb) {
        return lb.getLeaderboardDescription(leaderboardName);
      })
      .then(function (res) {
        const description = {
          app_id: res.appID,
          default: res.default,
          invert_sort_order: res.description.invert_sort_order,
          decimal_offset: res.description.score_format.options.decimal_offset,
          type: res.description.type,
          name: res.name,
          title: res.title,  
        };
        console.log(res,description)
        {{{ makeDynCall('viii', 'handler') }}}(callback, 1, YGDefold.allocateJSON(description))
      })
      .catch(function () {
        {{{ makeDynCall('viii', 'handler') }}}(callback, 0, 0)
      });
  },

  JS_SetLeaderboardScore: function (cleaderboardName, cscore, cextraData) {
    const leaderboardName = UTF8ToString(cleaderboardName);
    const score = parseFloat(UTF8ToString(cscore));
    const extraData = UTF8ToString(cextraData) ?? undefined;

    window.ysdk.getLeaderboards()
      .then(function (lb) {
        return lb.setLeaderboardScore(leaderboardName, score, extraData);
      });
  },

  JS_GetLeaderboardPlayerEntry: function (handler, callback, cleaderboardName) {
    const leaderboardName = UTF8ToString(cleaderboardName);
    
    window.ysdk.getLeaderboards()
      .then(function (lb) {
        return lb.getLeaderboardPlayerEntry(leaderboardName);
      })
      .then(function (res) {
        const player_entry = {
          score: res.score,
          extraData: res.extraData,
          rank: res.rank,
          avatar_src: {
            small: res.player.getAvatarSrc("small"),
            medium: res.player.getAvatarSrc("medium"),
            large: res.player.getAvatarSrc("large"),
          },
          avatar_srcset: {
            small: res.player.getAvatarSrcSet("small"),
            medium: res.player.getAvatarSrcSet("medium"),
            large: res.player.getAvatarSrcSet("large"),
          },
          lang: res.player.lang,
          public_name: res.player.public_name,
          unique_id: res.player.unique_id,
          formattedScore: res.formattedScore,
        }
        {{{ makeDynCall('viii', 'handler') }}}(callback, 1, YGDefold.allocateJSON(player_entry))
      })
      .catch(function () {
        {{{ makeDynCall('viii', 'handler') }}}(callback, 0, 0)
      });
  },

  JS_GetLeaderboardEntries: function (handler, callback, cleaderboardName, cparams) {
    const leaderboardName = UTF8ToString(cleaderboardName);
    const params = cparams ? JSON.parse(UTF8ToString(cparams)) : undefined;

    window.ysdk.getLeaderboards()
      .then(function (lb) {
        console.log("3", lb,  {
          includeUser: params?.include_user ?? false,
          quantityAround: params?.quantity_around ?? 5,
          quantityTop: params?.quantity_top ?? 5,
        })
        return lb.getLeaderboardEntries(
          leaderboardName,
          {
            includeUser: params?.include_user ?? false,
            quantityAround: params?.quantity_around ?? 5,
            quantityTop: params?.quantity_top ?? 5,
          }
        );
      })
      .then(function (res) {
        console.log("4", res)
        const entries = {
          leaderboard: {
            app_id: res.leaderboard.app_id,
            default: res.leaderboard.default,
            invert_sort_order: res.leaderboard.description.invert_sort_order,
            decimal_offset: res.leaderboard.description.score_format.options.decimal_offset,
            type: res.leaderboard.description.type,
            name: res.leaderboard.description.name,
            title: res.leaderboard.description.title,  
          },
          ranges: res.ranges,
          user_rank: res.userRank,
          entries: res.entries.map(function (entry) {
            return {
              score: entry.score,
              extraData: entry.extraData,
              rank: entry.rank,
              avatar_src: {
                small: entry.player.getAvatarSrc("small"),
                medium: entry.player.getAvatarSrc("medium"),
                large: entry.player.getAvatarSrc("large"),
              },
              avatar_srcset: {
                small: entry.player.getAvatarSrcSet("small"),
                medium: entry.player.getAvatarSrcSet("medium"),
                large: entry.player.getAvatarSrcSet("large"),
              },
              lang: entry.player.lang,
              public_name: entry.player.publicName,
              unique_id: entry.player.uniqueID,
              formattedScore: entry.formattedScore,
            };
          }),
        }
        console.log("5", entries);
        {{{ makeDynCall('viii', 'handler') }}}(callback, 1, YGDefold.allocateJSON(entries))
      })
      .catch(function () {
        {{{ makeDynCall('viii', 'handler') }}}(callback, 0, 0)
      });
  },

//#endregion

//#region Shortcut

  JS_CanShowPrompt: function (handler, callback) {
    ysdk.shortcut
      .canShowPrompt()
      .then(function (prompt) {
          {{{ makeDynCall('vii', 'handler') }}}(callback, 1, prompt.canShow)
      })
      .catch(function () {
        {{{ makeDynCall('vii', 'handler') }}}(callback, 0, 0)
      });
  },

  JS_ShowPrompt: function (handler, callback) {
    ysdk.shortcut
      .showPrompt()
      .then(function (result) {
          {{{ makeDynCall('vii', 'handler') }}}(callback, 1, result.outcome === 'accepted')
      })
      .catch(function () {
        {{{ makeDynCall('vii', 'handler') }}}(callback, 0, 0)
      });
  },

//#endregion

//#region Screen

  JS_Screen_Fullscreen_GetStatus: function() {
    return YGDefold.allocateString(window.ysdk.screen.fullscreen.status);
  },

  JS_Screen_Fullscreen_Request: function() {
    window.ysdk.screen.fullscreen.request();
  },

  JS_Screen_Fullscreen_Exit: function() {
    window.ysdk.screen.fullscreen.exit();
  },

  JS_Screen_Orientation_Get: function() {
    return YGDefold.allocateString(window.ysdk.screen.orientation.value);
  },

  JS_Screen_Orientation_Set: function(cvalue) {
    window.ysdk.screen.orientation.value = UTF8ToString(cvalue);
  },

//#endregion

//#region Clipboard

  JS_ClipboardWriteText: function(ctext) {
    const text = UTF8ToString(ctext);
    window.ysdk.clipboard.writeText(text);
  },

//#endregion

//#region Device Info

  JS_GetDeviceInfo: function () {
    const deviceInfo = {
      type: window.ysdk.deviceInfo.type,
      isMobile: window.ysdk.deviceInfo.type === 'mobile',
      isDesktop: window.ysdk.deviceInfo.type === 'desktop',
      isTablet: window.ysdk.deviceInfo.type === 'tablet',
      isTV: window.ysdk.deviceInfo.type === 'tv',
    };
    return YGDefold.allocateString(JSON.stringify(deviceInfo));
  },

//#endregion

//#region Flags

  JS_GetFlags: function (handler, callback, cparams) {
    const params = cparams ? JSON.parse(UTF8ToString(cparams)) : {};

    window.ysdk
      .getFlags(params)
      .then(function (flags) {
        {{{ makeDynCall('viii', 'handler') }}}(callback, 1, YGDefold.allocateJSON(flags))
      })
      .catch(function () {
        {{{ makeDynCall('viii', 'handler') }}}(callback, 0, 0)
      });
  },

//#endregion

//#region Server Time

  JS_GetServerTime: function (handler, callback) {
    return window.ysdk.serverTime() ?? 0;
  }

//#endregion
};

autoAddDeps(LisGamesSDKLib, '$YGDefold');
mergeInto(LibraryManager.library, LisGamesSDKLib);
