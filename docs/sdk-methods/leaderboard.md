# Лидерборды

Вы можете показывать на странице игры персонализированные лидерборды с результатами лучших игроков и местом в рейтинге авторизованного пользователя.

Чтобы у вас заработали описанные ниже запросы, проверьте, что выполнены условия:

* вы [подключили и настроили SDK](https://yandex.ru/dev/games/doc/ru/sdk/sdk-about#use) и его объект доступен через переменную `ysdk`;
* в консоли разработчика [создан](https://yandex.ru/dev/games/doc/ru/concepts/leaderboards) лидерборд.

{% hint style="info" %}
Если в консоли нет лидерборда с соответствующим именем в поле **Техническое название лидерборда**, запросы будут выдавать ошибку 404.
{% endhint %}

## Описание лидерборда <a href="#description" id="description"></a>

Чтобы получить описание лидерборда по его имени, используйте метод `ysdk.leaderboards.get_description()`:

<pre class="language-lua"><code class="lang-lua">ysdk.leaderboards.get_description(
    <a data-footnote-ref href="#user-content-fn-1">leaderboard_name</a>: string, 
    callback: function
)
</code></pre>

`callback` — function — обработчик вызванного метода. Имеет вид:

```lua
function(self, description: table|nil): nil
```

*   `description: table` — описание лидерборда. Содержит свойства:

    <pre class="language-lua"><code class="lang-lua">description: {
      <a data-footnote-ref href="#user-content-fn-2">app_id</a>: string,
      <a data-footnote-ref href="#user-content-fn-3">dеfault</a>: boolean,
      <a data-footnote-ref href="#user-content-fn-4">invert_sort_order</a>: boolean,
      <a data-footnote-ref href="#user-content-fn-5">decimal_offset</a>: integer,
      <a data-footnote-ref href="#user-content-fn-6">type</a>: string,
      <a data-footnote-ref href="#user-content-fn-7">name</a>: string,
      <a data-footnote-ref href="#user-content-fn-8">title</a>: {
        en: string,
        ru: string
      }
    }
    </code></pre>

#### Пример

```lua
function display_leaderboard()
  ysdk.leaderboards.get_description("highscores",
    function (self, description)
      if description then
        print(
          description.name,
          description.title.en
        )
    end
  end)
end
```

## Новый результат <a href="#set-score" id="set-score"></a>

{% hint style="info" %}
Запрос доступен только для авторизованных пользователей. При необходимости воспользуйтесь [авторизацией](player.md#auth).
{% endhint %}

Чтобы установить игроку новый результат, используйте метод `ysdk.leaderboards.set_score()`:

<pre class="language-lua"><code class="lang-lua">ysdk.leaderboards.set_score(
    <a data-footnote-ref href="#user-content-fn-9">leaderboard_name</a>: string,
    <a data-footnote-ref href="#user-content-fn-10">score</a>: integer,
    <a data-footnote-ref href="#user-content-fn-11">extraData</a>: string|nil
)
</code></pre>

{% hint style="info" %}
Запрос можно отправлять не чаще, чем раз в секунду. В противном случае он будет отклонен с ошибкой.
{% endhint %}

## Получение рейтинга <a href="#get-entry" id="get-entry"></a>

{% hint style="info" %}
Запрос доступен только для авторизованных пользователей. При необходимости воспользуйтесь [авторизацией](player.md#auth).
{% endhint %}

Чтобы получить рейтинг пользователя, используйте метод `ysdk.leaderboards.get_player_entry()`:

<pre class="language-lua"><code class="lang-lua">ysdk.leaderboards.get_player_entry(
    <a data-footnote-ref href="#user-content-fn-12">leaderboard_name</a>: string, 
    callback: function
)
</code></pre>

`callback: function` — обработчик вызванного метода. Имеет вид:

```lua
function(self, player_entry: table|nil): nil
```

*   `player_entry: table` — рейтинг пользователя. Содержит свойства:

    <pre class="language-lua"><code class="lang-lua">player_entry: {
      <a data-footnote-ref href="#user-content-fn-13">score</a>: integer,
      <a data-footnote-ref href="#user-content-fn-14">extraData</a>: string,
      rank: integer,
      avatar_src: {
        small: string,
        medium: string,
        large: string,
      },
      avatar_srcset: {
        small: string,
        medium: string,
        large: string,
      },
      lang: string,
      public_name: string,
      unique_id: string,
      formatted_score: string
    }
    </code></pre>

#### Пример

```lua
function display_high_score()
  ysdk.leaderboards.get_player_entry("highscores",
    function (self, player_entry)
      if player_entry then
        print("highscore: " .. player_entry.score)
      end
    end)
end
```

## Записи лидерборда <a href="#get-entries" id="get-entries"></a>

Чтобы вывести рейтинг пользователей, используйте метод`ysdk.leaderboards.get_entries()`:

<pre class="language-lua"><code class="lang-lua">ysdk.leaderboards.get_entries(
    <a data-footnote-ref href="#user-content-fn-15">leaderboardName</a>: string, 
    callback: function, 
    options: {
        <a data-footnote-ref href="#user-content-fn-16">include_user</a>: boolean|nil,
        <a data-footnote-ref href="#user-content-fn-17">quantity_around</a>: number|nil,
        <a data-footnote-ref href="#user-content-fn-18">quantity_top</a>: number|nil
    }
)
</code></pre>

`callback: function` — обработчик вызванного метода. Имеет вид:

```lua
function(self, entries: table|nil): nil
```

*   `entries: table` — рейтинг пользователей. Содержит свойства:

    <pre class="language-lua"><code class="lang-lua">entries: {
      <a data-footnote-ref href="#user-content-fn-19">leaderboard</a>: {
        ...
      },
      <a data-footnote-ref href="#user-content-fn-20">ranges</a>: [
        {
          start: integer,
          size: integer
        }
      ],
      <a data-footnote-ref href="#user-content-fn-21">userRank</a>: integer,
      <a data-footnote-ref href="#user-content-fn-22">entries</a>: [
        {
          <a data-footnote-ref href="#user-content-fn-23">score</a>: integer,
          <a data-footnote-ref href="#user-content-fn-24">extraData</a>: string,
          rank: integer,
          avatar_src: {
            small: string,
            medium: string,
            large: string,
          },
          avatar_srcset: {
            small: string,
            medium: string,
            large: string,
          },
          lang: string,
          public_name: string,
          unique_id: string,
          formatted_score: string
        },
        ...
      ]
    }
    </code></pre>



[^1]: Название лидерборда.

[^2]: Идентификатор приложения.

[^3]: Если `true`, то лидерборд является основным.

[^4]: Направление сортировки:

    * `false` — места отсортированы по убыванию;
    * `true` — места отсортированы по возрастанию.

[^5]: Размер десятичной части счета. Например, при `decimal_offset: 2` число 1234 будет отображаться как 12.34.

[^6]: Тип результата лидерборда. Доступные параметры: `numeric` (число), `time` (секунды).

[^7]: Имя лидерборда.

[^8]: Локализованные названия. [Возможные параметры массива](https://yandex.ru/dev/games/doc/ru/concepts/languages-and-domains).

[^9]: Имя лидерборда.

[^10]: Значение результата. Принимается только тип integer. Не может быть отрицательным. Если тип лидерборда — time, то значения необходимо передавать в миллисекундах.

[^11]: Описание пользователя. Необязательный параметр.

[^12]: Название лидерборда.

[^13]: Значение результата. Принимается только тип integer. Не может быть отрицательным. Если тип лидерборда — time, то значения необходимо передавать в миллисекундах.

[^14]: Описание пользователя. Необязательный параметр.

[^15]: Название лидерборда.

[^16]: Определяет, включать ли авторизованного пользователя в ответ:

    * `true` — включать в ответ;
    * `false` (по умолчанию) — не включать

[^17]: Количество записей ниже и выше пользователя по лидерборду, которое нужно вернуть. Минимальное значение — 1, максимальное — 10. По умолчанию возвращается 5.

[^18]: Количество записей из топа лидерборда. Минимальное значение — 1, максимальное — 20. По умолчанию возвращается 5.

[^19]: [Описание лидерборда](leaderboard.md#description)

[^20]: Интервалы мест в ответе.

[^21]: Место пользователя в рейтинге. Если отсутствует, либо запрос на топ без включения пользователя, то равен 0.

[^22]: Результаты по запросу.

[^23]: Значение результата. Принимается только тип `integer`. Не может быть отрицательным. Если тип лидерборда — `time`, то значения необходимо передавать в миллисекундах.

[^24]: Описание пользователя. Необязательный параметр.
