# Переменные окружения

## Переменные окружения

Вы можете получать информацию об окружении, в котором работает игра. Для этого используется объект `ysdk.environment`.

<pre class="language-lua"><code class="lang-lua">{
  <a data-footnote-ref href="#user-content-fn-1">app</a>: {
    <a data-footnote-ref href="#user-content-fn-2">id</a>: string
  },
  <a data-footnote-ref href="#user-content-fn-3">browser</a>: {
    <a data-footnote-ref href="#user-content-fn-4">lang</a>: string
  },
  <a data-footnote-ref href="#user-content-fn-5">i18n</a>: {
    <a data-footnote-ref href="#user-content-fn-6">lang</a>: string;
    <a data-footnote-ref href="#user-content-fn-7">tld</a>: string;
  },
  <a data-footnote-ref href="#user-content-fn-8">payload</a>: string|nil;
}
</code></pre>

**Объект environment**

Содержит переменные окружения игры.

| **Параметр** | **Тип**     | **Описание**                                                                                                                                                                                            |
| ------------ | ----------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `app`        | table       | Данные игры.                                                                                                                                                                                            |
| `browser`    | table       | Данные браузера.                                                                                                                                                                                        |
| `i18n`       | table       | Интернационализация на сервисе.                                                                                                                                                                         |
| `payload`    | string\|nil | Значение параметра `payload` из адреса игры. Необязательный параметр. Например, для игры `https://yandex.ru/games/app/123?payload=test` значение `test` можно получить так: `ysdk.environment.payload`. |

**Структура app**

| **Параметр** | **Тип** | **Описание**        |
| ------------ | ------- | ------------------- |
| `id`         | string  | Идентификатор игры. |

**Структура browser**

<table data-header-hidden data-full-width="false"><thead><tr><th></th><th></th><th></th></tr></thead><tbody><tr><td><strong>Параметр</strong></td><td><strong>Тип</strong></td><td><strong>Описание</strong></td></tr><tr><td><code>lang</code></td><td>string</td><td>Приоритетный язык браузера в формате ISO 639-1.</td></tr></tbody></table>

**Структура i18n**

| Параметр | Тип    | Описание                                                                                                                                                                                                                                                                                               |
| -------- | ------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| `lang`   | string | [Язык интерфейса Яндекс Игр](https://yandex.ru/dev/games/doc/ru/concepts/languages-and-domains#languages) в формате ISO 639-1. Например, `"tr"` означает, что игра сейчас запущена в турецком интерфейсе Яндекс Игр. Рекомендуем использовать этот параметр для определения языка пользователя в игре. |
| `tld`    | string | Домен верхнего уровня. Например, `"com"` означает, что игра сейчас запущена на международном домене Яндекс Игр. При размещении игры на своем домене учтите, что она должна корректно открываться на любом yandex-домене.                                                                               |

[^1]: Данные игры.

[^2]: Идентификатор игры.

[^3]: Данные браузера.

[^4]: Приоритетный язык браузера в формате ISO 639-1.

[^5]: Интернационализация на сервисе.

[^6]: [Язык интерфейса Яндекс Игр](https://yandex.ru/dev/games/doc/ru/concepts/languages-and-domains#languages) в формате ISO 639-1. Например, `"tr"` означает, что игра сейчас запущена в турецком интерфейсе Яндекс Игр. Рекомендуем использовать этот параметр для определения языка пользователя в игре.

[^7]: Домен верхнего уровня. Например, `"com"` означает, что игра сейчас запущена на международном домене Яндекс Игр. При размещении игры на своем домене учтите, что она должна корректно открываться на любом yandex-домене.

[^8]: Значение параметра `payload` из адреса игры. Необязательный параметр. Например, для игры `https://yandex.ru/games/app/123?payload=test` значение `test` можно получить так: `ysdk.environment.payload`.
