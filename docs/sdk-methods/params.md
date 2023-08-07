# Другие объекты и параметры SDK

## **Объект screen**

Содержит настройки для работы с экраном:

<pre class="language-lua"><code class="lang-lua">{
    fullscreen: {
        <a data-footnote-ref href="#user-content-fn-1">status</a>: function(): "on"|"off"
        <a data-footnote-ref href="#user-content-fn-2">request</a>: function(): nil,
        <a data-footnote-ref href="#user-content-fn-3">exit</a>: function(): nil
    },
    <a data-footnote-ref href="#user-content-fn-4">orientation</a>: {
        <a data-footnote-ref href="#user-content-fn-5">get</a>: function(): "portrait"|"landscape",
        <a data-footnote-ref href="#user-content-fn-6">set</a>: function(value: "portrait"|"landscape")
    }
}
</code></pre>

{% hint style="warning" %}
#### Внимание

Яндекс Игры могут автоматически запускаться в полноэкранном режиме, однако многие браузеры запрещают переключать режим без команды пользователя.

В правом верхнем углу экрана Яндекс Игр уже реализована кнопка перехода в полноэкранный режим, поэтому используйте параметры объекта `screen.fullscreen` для обработки кнопок непосредственно в игре.
{% endhint %}

## Объект clipboard

Предназначен для записи строки в буфер обмена при помощи метода `ysdk.clipboard.write_text(text: string)`.

## Объект deviceI\_info

Предназначен для получения информации об устройстве пользователя при помощи метода `ysdk.device_info`.

```lua
{
    type: "mobile"|"desktop"|"tablet"|"tv",
    isMobile: boolean,
    isDesktop: boolean,
    isTablet: boolean,
    isTV: boolean,
}
```

[^1]: Текущее состояние: `"on"` или `"off"`.

[^2]: Запрос перехода в полноэкранный режим.

[^3]: Запрос выхода из полноэкранного режима.

[^4]: Настройки экрана во время игры.

[^5]: Получить текущую ориентацию экрана.

[^6]: Принудительно задать ориентацию экрана.
