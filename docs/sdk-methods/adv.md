# Работа с рекламой

## Работа с рекламой

Вы можете получать доход от размещения рекламных блоков в своих играх. Для этого:

1. Изучите [особенности и рекомендации](https://yandex.ru/dev/games/doc/ru/sdk/sdk-adv#recommendations) по размещению рекламы.
2. Настройте вызов рекламы, используя SDK.
3. [Подключите монетизацию](https://yandex.ru/dev/games/doc/ru/console/adv-monetization) в консоли разработчика Яндекс Игр.

### Особенности и рекомендации по размещению рекламы

* Размещайте вызов рекламы таким образом, чтобы пользователь понимал, что это не часть игры, а рекламный блок.
* Рекомендуемые места для вставки рекламы в игре: перед началом игры, при переходе на следующий уровень, после проигрыша.
* Частота вызова видеорекламы с вознаграждением (rewarded video) не ограничена.
* Частота вызова полноэкранного блока рекламы управляется платформой [Яндекс Игры](https://yandex.ru/games/).

Внимание

Рекламная сеть Яндекса считает случайные клики пользователей по блокам рекламы признаком рекламного фрода и снижает доход от рекламы в игре.

Чтобы этого избежать, не вызывайте показ рекламы во время игрового процесса, когда пользователь может нажать на блок рекламы ненамеренно.

### Настройка вызова рекламы

#### Полноэкранный блок рекламы

Полноэкранный блок рекламы — блоки с рекламой, которые полностью закрывают фон приложения и показываются между запросом какой-то информации пользователем (например, при переходе на следующий уровень игры) и ее получением.

Чтобы вызвать рекламу, используйте метод `ysdk.adv.show_fullscreen_adv()`.

```lua
ysdk.adv.show_fullscreen_adv(callbacks: table)
```

`callbacks: table` — опциональные callback-функции. Настраиваются индивидуально для каждого рекламного блока.

* `on_close` — вызывается при закрытии рекламы, после ошибки, а также, если реклама не открылась по причине слишком частого вызова. Используется с аргументом `was_shown` (тип `boolean`), по значению которого можно узнать была ли показана реклама.
* `on_open` — вызывается при успешном открытии рекламы.
* `on_error` — вызывается при возникновении ошибки. Объект ошибки передается в callback-функцию.
* `on_offline` — вызывается при потере сетевого соединения (переходе в офлайн-режим).

**Пример**

```lua
ysdk.adv.show_fullscreen_adv({
  on_close = function (self, was_shown)
    -- some action after close
  end,
  on_error = function (self, error)
    -- some action after error
  end
})
```

#### Видеореклама с вознаграждением (rewarded video)

Видео с вознаграждением — блоки с видеорекламой, которые используются для монетизации игр. За просмотр видеоролика пользователь получает награду или внутриигровую валюту.

Чтобы вызвать рекламу, используйте метод `ysdk.adv.show_rewarded_video()`.

```lua
ysdk.adv.show_rewarded_video(callbacks: table)
```

`callbacks: table` — опциональные callback-функции. Настраиваются индивидуально для каждого рекламного блока.

* `on_close` — вызывается при закрытии видеорекламы.
* `on_open` — вызывается при отображении видеорекламы на экране.
* `on_error` — вызывается при возникновении ошибки. Объект ошибки передается в callback-функцию.
* `on_rewarded` — вызывается, когда засчитывается просмотр видеорекламы. Укажите в данной функции, какую награду пользователь получит после просмотра.

**Пример**

```lua
ysdk.adv.show_rewarded_video({
  on_open = function (self)
    print("Video ad open")
  end,
  on_close = function (self)
    print("Rewarded!")
  end,
  on_rewarded = function (self)
    print("Video ad closed.")
  end,
  on_error = function (self, error)
    print("Error while open video ad: " .. error)
  end
})
```

#### Sticky-баннер

Чтобы включить показ _sticky-баннера_:

1. Откройте консоль разработчика и перейдите на вкладку **Черновик**.
2. В блоке **Sticky-баннеры** настройте отображение баннеров:
   * Для мобильных устройств:
     * **Sticky-баннер в портретной ориентации** — выберите расположение **Внизу** или **Вверху**;
     * **Sticky-баннер в альбомной ориентации** — выберите расположение **Внизу**, **Вверху** или **Справа**.
   * Для компьютеров — включите опцию **Sticky-баннер на десктопе**. Баннер будет показываться справа.

По умолчанию sticky-баннер появляется при запуске игры и отображается всю сессию. Чтобы настроить момент показа баннера:

1. В блоке **Sticky-баннеры** включите опцию **Отключить показ sticky-баннера на старте**.
2. Задайте показ баннеров, используя методы:
   * `ysdk.adv.get_banner_adv_status()` — показывает статус баннера;
   * `ysdk.adv.show_banner_adv()` — вызывает баннер;
   * `ysdk.adv.hide_banner_adv()` — убирает баннер.

Методы `ysdk.adv.get_banner_adv_status()` возвращает значение `sticky_adv_is_showing: boolean`. Если `sticky_adv_is_showing = false`, метод `ysdk.adv.get_banner_adv_status()` может вернуть опциональное поле `reason` с возможными причинами:

* ADV\_IS\_NOT\_CONNECTED — не подключены баннеры;
* UNKNOWN — ошибка показа рекламы на стороне Яндекса.

**Пример**

```lua
ysdk.adv.get_banner_adv_status(
  function (self, sticky_adv_is_showing, reason)
    if sticky_adv_is_showing then
      -- реклама показывается
    elseif reason then
      -- реклама не показывается
      print(reason)
    else
      ysdk.adv.show_banner_adv()
    end
  end
)
```
