# 📦 Папка для готовых APK файлов

## Описание

Эта папка предназначена для хранения собранных и подписанных APK файлов проекта tg.Reward.

## Структура файлов

После успешной сборки здесь должны находиться:

### Debug версии (для тестирования)
- `tg.Reward-debug.apk` - отладочная версия с debug символами

### Release версии (для распространения)
- `tg.Reward-v1.0-arm64.apk` - подписанная версия для arm64-v8a
- `tg.Reward-v1.0-arm32.apk` - подписанная версия для armeabi-v7a (опционально)
- `tg.Reward-v1.0-universal.apk` - универсальная версия для всех архитектур

## Как собрать APK

Смотрите подробные инструкции в файле `/home/engine/project/BUILD_INSTRUCTIONS.md`

### Быстрая сборка

```bash
cd /home/engine/project/tg.Reward
./build.sh
```

Или вручную:

```bash
export JAVA_HOME=/usr/lib/jvm/java-11-openjdk-amd64
export ANDROID_SDK_ROOT=/opt/android-sdk
export ANDROID_HOME=/opt/android-sdk
export ANDROID_NDK_HOME=/opt/android-sdk/ndk/22.0.7026061

gradle-7.2/bin/gradle clean assembleDebug
cp app/build/outputs/apk/debug/app-debug.apk ../тутапк/tg.Reward-debug.apk
```

## Установка на устройство

### Через ADB
```bash
adb install tg.Reward-debug.apk
```

### Вручную
1. Скопируйте APK файл на Android устройство
2. Откройте файл через файловый менеджер
3. Разрешите установку из неизвестных источников при необходимости
4. Следуйте инструкциям установщика

## Требования к устройству

- **Android**: 4.4+ (API 19+)
- **Архитектура**: ARM64-v8a (рекомендуется) или ARMv7
- **RAM**: минимум 2GB
- **Свободное место**: 100MB+
- **Root**: не обязательно, но рекомендуется для полной функциональности

## Функциональность

### Основные возможности tg.Reward:
- ✅ Система аутентификации с ключом доступа
- ✅ JNI инъекция в Standoff 2
- ✅ 80+ игровых функций в 9 категориях
- ✅ Современный UI/UX интерфейс меню
- ✅ Поддержка хуков и перехватов
- ✅ Безопасная инъекция без конфликтов

### Категории функций:
1. Visual ESP (Player ESP, Box ESP, Health Bar, Distance)
2. Aim Assist (Silent Aim, Triggerbot, FOV настройки)
3. Movement (Noclip, Speed Hack, Fly)
4. Combat (God Mode, Infinite Ammo, No Recoil)
5. Skin Changer (Оружие, персонажи, аксессуары)
6. Bypass (Anti-Ban, Anti-Kick)
7. Misc (Teleport, Wallhack, No Fog)
8. Settings (Настройки меню, сохранение конфигов)
9. Info (Версия, статистика, логи)

## Безопасность

APK файлы в этой папке:
- Подписаны цифровой подписью
- Проверены на вредоносный код
- Оптимизированы для целевой платформы
- Содержат обфусцированный код

## Лицензия

Проект распространяется согласно лицензии, указанной в корневом каталоге проекта.

---

**Версия**: 1.0  
**Дата**: 2026-02-01  
**Проект**: tg.Reward - JNI Injection для Standoff 2
