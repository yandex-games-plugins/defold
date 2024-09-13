# Changelog

All notable changes to this project will be documented in this file.

## [1.2.2] - 2024.09.13

### Fixed

- Fixed broken leaderboards methods

## [1.2.1] - 2024.09.06

### Fixed

- Compilation error in HMTL5 target

## [1.2.0] - 2024.07.26

### Added

- Completions for Defold code editor
- Support for `Server time` API
- Support for player's paying status information
- Support for [GameplayAPI](https://yandex.ru/dev/games/doc/ru/sdk/sdk-game-events#gameplay)
- Updated README to include information about the new documentation
- Parameter `keys` is now optional in `ysdk.player.get_data` and `ysdk.player.get_stats`
- New parameter `callback` for `ysdk.payments.consume_purchase`

### Fixed

- String allocation for newer versions of Defold
- Error serialization in `ysdk.adv.show_fullscreen_adv` and `ysdk.adv.show_rewarded_video`

## [1.1.0] - 2024.01.4

### Added

- Support for [Remote Config](https://yandex.ru/dev/games/doc/ru/sdk/sdk-config)
