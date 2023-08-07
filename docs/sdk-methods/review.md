# Оценка игры

Вы можете попросить пользователя оценить игру и написать комментарий во всплывающем окне (появится в момент запроса оценки, закрывая фон приложения). Всплывающее окно не будет показано, если пользователь не авторизован или оценивал игру ранее.

Прежде чем запросить оценку игры, убедитесь, что опция доступна для этого пользователя.

## Проверка возможности запросить оценку

Чтобы узнать, можно ли запросить оценку игры, используйте метод `ysdk.feedback.can_review()`.

```lua
ysdk.feedback.can_review(callback: function)
```

`callback: function` — обработчик вызванного метода. Имеет вид:

```lua
function(self, can_review: boolean, reason: string|nil): nil
```

* `can_review: boolean` — можно ли запросить или нет.
* `reason: string|nil` — причина, почему нельзя запросить рекламу. Возможные значения:
  * `NO_AUTH` — The user isn't logged in.
  * `GAME_RATED` — The user already rated the game.
  * `REVIEW_ALREADY_REQUESTED` — A request was sent, now awaiting the user's action.
  * `REVIEW_WAS_REQUESTED` — A request was sent and the user performed an action (gave a rating or closed the pop-up window).
  * `UNKNOWN` — A request wasn't sent because an error occurred on the Yandex side.

## Запрос оценки <a href="#request-review" id="request-review"></a>

{% hint style="danger" %}
Запросить оценку игры можно только один раз за сессию. Обязательно используйте метод `ysdk.feedback.can_review()` перед выполнением запроса.
{% endhint %}

Чтобы предложить пользователю оценить игру, используйте метод `ysdk.feedback.request_review()`.

```lua
ysdk.player.open_auth_dialog(callback)
```

`callback: function` — обработчик вызванного метода. Имеет вид:

<pre class="language-lua"><code class="lang-lua">function(self, <a data-footnote-ref href="#user-content-fn-1">feedback_sent</a>: boolean): nil
</code></pre>

* `feedback_sent: boolean` — оценил ли пользователь игру (`true`) или закрыл всплывающее окно (`false`).

#### Пример

```lua
ysdk.feedback.can_review(function (self, can_review, reason)
  if can_review then
    ysdk.feedback.request_review(function (self, feedback_sent)
      if feedback_sent then
        print("Reward")
      end
    end)
  else
    print(reason)
  end
end)
```

[^1]: Оценил ли пользователь игру (`true`) или закрыл всплывающее окно (`false`).
