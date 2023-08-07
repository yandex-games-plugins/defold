# Данные игрока

Вы можете сохранять данные состояния игры (пройденные уровни, опыт, внутриигровые покупки и т. д.) на сервере Яндекса или передавать их на [свой сервер](https://yandex.ru/dev/games/doc/ru/concepts/criteria#server-rules). Также вы можете персонализировать игру, используя некоторые данные из профиля пользователя на Яндексе, например, имя.

## Информация об игроке

<pre class="language-lua"><code class="lang-lua">ysdk.player.get_info(
    callback: function, 
    options: {
        <a data-footnote-ref href="#user-content-fn-1">scopes</a>: boolean|nil,
        <a data-footnote-ref href="#user-content-fn-2">signed</a>: boolean|nil
    }
)
</code></pre>

`callback: function` — callback вызванного метода. Имеет вид:

```lua
function(self, player: table|nil, signature: string|nil): nil
```

*   `player: table` — информация об игроке. Содержит свойства:

    <pre class="language-lua"><code class="lang-lua">player = {
        <a data-footnote-ref href="#user-content-fn-3">logged_in</a>: boolean,
        <a data-footnote-ref href="#user-content-fn-4">unique_id</a>: string,
        <a data-footnote-ref href="#user-content-fn-5">name</a>: string,
        <a data-footnote-ref href="#user-content-fn-6">photo</a>: {
            <a data-footnote-ref href="#user-content-fn-7">small</a>: string, 
            <a data-footnote-ref href="#user-content-fn-8">medium</a>: string,
            <a data-footnote-ref href="#user-content-fn-9">large</a>: string
        }
    }
    </code></pre>

#### Пример

```lua
function init_player()
  ysdk.player.get_info(function(self, player)
      if player then
        display_player(self, player)
      else
        ysdk.player.open_auth_dialog(function(self, authorized)
          ysdk.player.get_info(display_player, {})
        end)
      end
    end,
    {})
end

function display_player(player)
  if player then
    print(player.name, signature)
  end
end
```

## Авторизация пользователя <a href="#auth" id="auth"></a>

Если игрок не авторизован, вы можете использовать метод `ysdk.player.open_auth_dialog()`, чтобы вызвать окно авторизации.

```lua
ysdk.player.open_auth_dialog(callback: function)
```

`callback: function` — callback вызванного метода. Имеет вид:

```lua
function(self, authorized: boolean): nil
```

* `authorized: boolean` — игрок авторизовался или нет.

## Внутриигровые данные <a href="#ingame-data" id="ingame-data"></a>

Для работы с внутриигровыми данными пользователя используйте методы объекта `Player`:

*   `ysdk.player.set_data(data, flush)` — сохраняет данные пользователя. Максимальный размер данных не должен превышать 200 KБ.

    * `data: table` — содержащит пары ключ-значение.
    * `flush: boolean` — определяет очередность отправки данных. При значении «true» данные будут отправлены на сервер немедленно; «false» (значение по умолчанию) — запрос на отправку данных будет поставлен в очередь.

    Метод возвращает `Promise`, который показывает, удалось сохранить данные или нет.

    При значении параметра `flush: false` возвращаемый результат показывает только валидность данных (сама отправка поставлена в очередь и будет осуществлена позже). При этом метод `ysdk.player.get_data()` вернет данные, установленные последним вызовом `ysdk.player.set_data()`, даже если они еще не были отправлены.
* `ysdk.player.get_data(callback, keys)` — запрашивает внутриигровые данные пользователя, сохраненные в базе данных Яндекса.
  * `callback: fun(self, data: table<string, any>)` — функция-обработчик для работы с полученными внутриигровыми данными пользователя.
  * `keys: table<number, string>` — список ключей, которые необходимо вернуть. Если параметр `keys` отсутствует, то метод возвращает все внутриигровые данные пользователя.
* `ysdk.player.set_stats(stats)` — сохраняет численные данные пользователя. Максимальный размер данных не должен превышать 10 КБ.
  * `stats: table<string, number>` — содержит пары ключ-значение, где каждое значение должно быть числом.

{% hint style="success" %}
Используйте данный метод для часто изменяемых числовых значений (баллы, очки опыта, внутриигровая валюта) вместо [ysdk.player.set\_data()](https://yandex.ru/dev/games/doc/ru/sdk/sdk-player#ingame-data).
{% endhint %}

* `ysdk.player.increment_stats(increments)` — изменяет внутриигровые данные пользователя. Максимальный размер данных не должен превышать 10 КБ.
  * `increments: table<string, number>` — объект, который содержит пары ключ-значение, где каждое значение должно быть числом.
* `ysdk.player.get_stats(callback, keys)` — получить численные данные пользователя, сохраненные в базе данных Яндекса.
* `callback: fun(self, data: table<string, number>|nil)` — функция-обработчик для работы с полученными численные данными пользователя.
* `keys: string[]` — список ключей, которые необходимо вернуть. Если параметр `keys` отсутствует, то метод возвращает все внутриигровые данные пользователя.

## Идентификаторы пользователя

```lua
ysdk.player.get_ids_per_game(callback: function)
```

`callback: function` — callback вызванного метода. Имеет вид:

```lua
function(self, ids: {appID: number, userID: string}[]): nil
```

* `ids` - идентификаторы пользователя во всех играх разработчика, в которых от пользователя было получено явное согласие на передачу персональных данных. Содержит свойства:
  * `app_id: string` — идентификатор приложения.
  * `user_id: string` — идентификатор пользователя.

#### Пример

```lua
function log_ids()
  ysdk.player.get_ids_per_game(function(self, ids)
    for _, value in ipairs(ids) do
      print(value.app_id, value.user_id)
    end
  end)
end
```

[^1]: Стандартное значение - `true`. Если равен `false` или пользователь откажется предоставлять доступ, вы получите только идентификатор пользователя.

[^2]: Предназначен чтобы авторизовать пользователя и сохранять данные состояния игры на своем сервере. [Это позволит вам использовать подпись для проверки подлинности игрока и избежать возможных накруток.](https://yandex.ru/dev/games/doc/ru/sdk/sdk-purchases#signature)

[^3]: Автороизован ли игрок.

[^4]: Уникальный идентификатор пользователя.

[^5]: Имя пользователя.

[^6]: Ссылки на фото пользователя.

[^7]: Фото маленького размера.

[^8]: Фото среднего размера.

[^9]: Фото большого размера.
