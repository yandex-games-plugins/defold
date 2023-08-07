# Внутриигровые покупки

Вы можете получать доход, предоставив пользователям возможность совершать покупки в игре. Например, дополнительное время на прохождение уровня или аксессуары для игрового персонажа. Для этого:

* [Подключите внутриигровые покупки](https://yandex.ru/dev/games/doc/ru/console/purchases#connect) в консоли разработчика Яндекс Игр.
* Настройте в SDK возможность работы с покупками.

## Портальная валюта <a href="#currency" id="currency"></a>

Ян (Yan) — это портальная валюта платформы [Яндекс Игры](https://yandex.ru/games/) для оплаты внутриигровых покупок. Яны хранятся на едином для всех игр балансе игрока, который можно пополнить с помощью банковских карт. Курс яна к рублю динамический.

{% hint style="info" %}
Для международных платежей коэффициент яна к валюте будет зависеть от страны игрока.
{% endhint %}

Пополнить баланс можно:

* в шапке каталога;
* в профиле игрока;
* во время покупки в игре.

Пользователи также могут получать яны бонусом за участие в акциях или покупку фиксированных паков.

Совершать внутриигровые покупки могут как авторизованные на Яндексе пользователи, так и неавторизованные. Авторизоваться пользователь может непосредственно во время игры, в том числе и в момент совершения покупки.

Порядок и условия выплаты лицензионного вознаграждения разработчику в связи с введением портальной валюты не изменятся.

## Условия подключения <a href="#conditions" id="conditions"></a>

Требования к подключению покупок зависят от резиденства вашего юридического лица.



{% tabs %}
{% tab title="Резидент РФ" %}
Для настройки и тестирования покупок необходимо подписать «Акт приема-передачи неисключительных прав на использование Игры».

После добавления покупок и публикации черновика игры отправьте письмо с запросом формы акта на почту [games-partners@yandex-team.com](mailto:games-partners@yandex-team.com). В письме обязательно укажите название и идентификатор (ID) игры.

В ответ на ваше письмо будет отправлена форма «Акт приема-передачи неисключительных прав на использование Игры». Эту форму необходимо заполнить, подписать и отправить скан (или фото хорошего качества) в ответ на наше письмо.

Только после получения подписанного акта внутриигровые покупки можно будет настраивать и тестировать.
{% endtab %}

{% tab title="Нерезидент РФ" %}
После добавления покупок и публикации черновика игры отправьте письмо с запросом о подключении покупок на почту [games-partners@yandex-team.com](mailto:games-partners@yandex-team.com). В письме обязательно укажите название и идентификатор (ID) игры, а также страну резидентства вашего юридического лица.
{% endtab %}
{% endtabs %}

## Процесс покупки <a href="#payments-purchase" id="payments-purchase"></a>

Активировать внутриигровую покупку можно следующим методом:

```lua
ysdk.payments.create_purchase(callback, options)
```

`callback` — function — callback вызванного метода. Имеет вид:

```lua
function(self, purchase: table|nil, signature: string|nil): nil
```

* `purchase: table` — информация о покупке. Содержит свойства:
  * `product_id: string` — идентификатор товара.
  * `purchase_token: string` — токен для использования покупки.
  * `developer_payload: string|nil` — дополнительные данные о покупке.
* `signature: string|nil` — данные о покупке и подпись для [проверки подлинности игрока](https://yandex.ru/dev/games/doc/ru/sdk/sdk-purchases#purchase-data-example).

`options` — параметры метода. Содержит свойства:

* `id: string` — идентификатор товара, который [задан в консоли разработчика](https://yandex.ru/dev/games/doc/ru/console/purchases#connect).
* `developer_payload: string` — опциональный параметр. Дополнительная информация о покупке, которую вы хотите передавать на свой сервер (будет передана в параметре _signature_).
* `signed: boolean|nil` — опциональный параметр. Предназначен для защиты игры [от накруток](https://yandex.ru/dev/games/doc/ru/sdk/sdk-purchases#signature).

#### Пример

```lua
function buy_item(id)
  ysdk.payments.create_purchase(
    function(self, purchase, signature)
      if purchase then
        print(purchase.product_id, signature)
      end
    end,
    { id, signed = true }
  )
end
```

## Получение списка купленных товаров <a href="#getpurchases" id="getpurchases"></a>

Чтобы узнать, какие покупки игрок уже совершил, используйте метод:

<pre class="language-lua"><code class="lang-lua">ysdk.payments.getPurchases(
    callback: function, 
    options : {
        <a data-footnote-ref href="#user-content-fn-1">signed</a>: boolean|nil
    }
)
</code></pre>

`callback` — function — callback вызванного метода. Имеет вид:

```lua
function(self, purchase: Purchase[]|nil, signature: string|nil): nil
```

* `Purchase` — информация о покупке. Содержит свойства:
  * `product_id: string` — идентификатор товара.
  * `purchase_token: string` — токен для использования покупки.
  * `developer_payload: string|nil` — дополнительные данные о покупке.
* `signature: string|nil` — данные о покупке и подпись для проверки подлинности игрока.

#### Пример

```lua
function display_puchases()
  ysdk.payments.get_purchases(function(self, purchases)
    if purchases then
      for k, v in pairs(purchases) do print(k, v) end
    end
  end)
end
```

## Получение каталога всех товаров <a href="#getcatalog" id="getcatalog"></a>

Чтобы получить список доступных покупок и их стоимость, используйте метод `ysdk.payments.getCatalog()`.

```lua
ysdk.payments.getCatalog(callback: function)
```

`callback` — function — callback вызванного метода. Имеет вид:

```lua
function(self, products: Product[]|nil): nil
```

*   `products: table[]` — информация о товарах. Содержит свойства:

    <pre class="language-lua"><code class="lang-lua">products = [
        {
            <a data-footnote-ref href="#user-content-fn-2">id</a>: string,
            <a data-footnote-ref href="#user-content-fn-3">title</a>: string,
            <a data-footnote-ref href="#user-content-fn-4">description</a>: string,
            <a data-footnote-ref href="#user-content-fn-5">image_uri</a>: string,
            <a data-footnote-ref href="#user-content-fn-6">price</a>: string,
            <a data-footnote-ref href="#user-content-fn-7">price_value</a>: string,
            <a data-footnote-ref href="#user-content-fn-8">price_currency_code</a>: string,
            <a data-footnote-ref href="#user-content-fn-9">price_currency_image</a>: {
                <a data-footnote-ref href="#user-content-fn-10">small</a>: string,
                <a data-footnote-ref href="#user-content-fn-11">medium</a>: string,
                <a data-footnote-ref href="#user-content-fn-12">svg</a>: string
            }
        },
        ...
    ]
    </code></pre>

#### Пример

```lua
function display_shop()
  ysdk.payments.get_catalog(function(self, products)
    if products then
      for k, v in pairs(products) do print(v.title, v.price, v.description) end
    end
  end)
end
```

## Обработка покупки и начисление внутриигровой валюты <a href="#consumepurchase" id="consumepurchase"></a>

Существуют два типа покупок — постоянные (например, отключение рекламы) и используемые (например, внутриигровая валюта).

Для обработки постоянных покупок применяйте метод `ysdk.payments.get_purchases()`.

Для обработки используемых покупок применяйте метод `ysdk.payments.consume_purchase()`.

```lua
ysdk.payments.consume_purchase(purchase_token: string)
```

{% hint style="danger" %}
После вызова метода `ysdk.ayments.consume_purchase()` обработанная покупка удаляется без возможности восстановления. Поэтому сначала модифицируйте данные игрока методами `ysdk.player.set_stats()` или `ysdk.player.increment_stats()`, а затем обрабатывайте покупку.
{% endhint %}

#### Пример

```lua
function buy_item(id)
  ysdk.payments.create_purchase(
    function(self, purchase)
      if purchase then
        ysdk.payments.consume_puchase(purchase.purchase_token)
      end
    end,
    { id }
  )
end
```

[^1]: Опциональный параметр. Предназначен для защиты игры [от накруток](https://yandex.ru/dev/games/doc/ru/sdk/sdk-purchases#signature).

[^2]: Идентификатор товара.

[^3]: Название товара.

[^4]: Описание товара.

[^5]: URL изображения.

[^6]: Cтоимость товара в формате <цена> <код валюты>. Например, «25 YAN».

[^7]: Cтоимость товара в формате <цена>. Например, «25».

[^8]: Код валюты («YAN»).

[^9]: Ссылки на иконки валюты.

[^10]: Иконка маленького размера.

[^11]: Иконка среднего размера.

[^12]: Иконка в формате SVG.
