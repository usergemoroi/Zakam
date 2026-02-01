# tg.Reward - Модифицированное меню для Standoff 2

## 📱 Описание проекта
**tg.Reward** - это продвинутое Android-приложение с системой аутентификации и функциональным меню для игры Standoff 2, разработанное на основе библиотеки из архива `planet.zip`.

## 🔐 Система аутентификации

### Ключ супер-пользователя
- **Мастер-ключ:** `73D37C08`
- При запуске приложение требует ввод ключа
- После успешной аутентификации активируется кнопка "СТАРТ"
- Приложение имеет права супер-пользователя

### Экран входа
- **Современный дизайн** в красно-черной цветовой гамме
- Градиентный фон (черный → темно-красный → черный)
- Анимированные элементы интерфейса
- Живой отклик на ввод ключа
- Плавные переходы между экранами

## 🎨 Дизайн

### Цветовая палитра
- **Основной цвет:** #FF0000 (красный)
- **Вторичный цвет:** #CC0000 (темно-красный)
- **Фон:** #000000, #0D0D0D, #1A0000 (черные оттенки)
- **Текст:** #FFFFFF (белый), #CCCCCC (серый)
- **Акценты:** градиенты красного и черного

### UI/UX особенности
- Плавные анимации появления элементов
- Пульсирующая кнопка после активации
- Анимированные переходы между экранами
- Закругленные углы элементов (15px)
- Тени и градиенты для глубины
- Адаптивная верстка

## 🎮 Функции меню (tg.Reward)

### Visual ESP
- Player ESP
- Box ESP
- Health Bar
- Distance ESP
- Skeleton ESP
- Radar
- Chams
- Hit Markers

### Aim Assist
- Silent Aim
- Triggerbot
- FOV Circle с настройкой (1-360°)
- Auto Stop
- Auto Scope
- Smooth Aim с регулировкой

### Movement
- Third Person
- Noclip
- Bunny Hop
- Speed Hack с мультипликатором (1-10x)
- Air Jump
- High Jump
- Fly Mode

### Weapon Mods
- Infinite Ammo
- No Recoil
- Rapid Fire
- Fast Knife
- Anti Grenade
- Friendly Fire
- One Shot Kill
- Auto Reload

### Player Mods
- God Mode
- Infinite Health
- Anti Flash
- Anti Smoke
- See Through Walls
- Instant Respawn

### World Mods
- Big Head
- Night Mode
- Custom Sky Color
- Remove Fog
- Bright Environment

### Skin Changer
- Enable/Disable Skin Changer
- Knife ID input
- Skin ID input
- Apply button

### Anti Aim
- Spinbot
- Jitter
- Spin Speed регулировка (1-100)

### Misc
- Auto Win
- Infinite Money
- Unlock All
- Show FPS
- Debug Info

### Settings
- Save Preferences
- Auto Size Vertically
- Close Menu button

## 🛠️ Технический стек

### Java компоненты
- `LoginActivity` - экран аутентификации
- `MainActivity` - главная активность с перенаправлением на SO2
- `Menu` - сервис для отображения меню

### Native библиотека (C++)
- **Название:** `libtgReward.so`
- **Основа:** ImGui + OpenGL ES
- **Архитектура:** armeabi-v7a
- **Функционал:** меню, hooks, patches

### Зависимости
- ImGui для рендеринга UI
- OpenGL ES 2.0 для графики
- KittyMemory для патчей памяти
- ByNameModding для IL2CPP reflection
- Xhook для PLT hooking
- libcurl + OpenSSL для сетевых функций
- OpenSL ES для аудио

## 📦 Структура проекта

```
tg.Reward/
├── app/
│   ├── src/
│   │   └── main/
│   │       ├── java/com/tg/reward/
│   │       │   ├── LoginActivity.java    # Экран аутентификации
│   │       │   ├── MainActivity.java     # Главная активность
│   │       │   └── Menu.java            # Сервис меню
│   │       ├── jni/
│   │       │   ├── Main.cpp             # Точка входа нативного кода
│   │       │   ├── Menu/
│   │       │   │   ├── MenuTgReward.h   # Определение меню
│   │       │   │   └── Setup.h          # Настройки
│   │       │   ├── ImGui/               # UI библиотека
│   │       │   └── Android.mk           # Build script
│   │       ├── res/
│   │       │   ├── layout/
│   │       │   │   └── activity_main.xml
│   │       │   └── values/
│   │       │       └── strings.xml
│   │       └── AndroidManifest.xml      # Манифест приложения
│   └── build.gradle                     # Gradle конфигурация
└── README.md                            # Документация
```

## 🚀 Установка и использование

### Требования
- Android 4.4+ (API 19+)
- Standoff 2 установлен на устройстве
- Разрешения: SYSTEM_ALERT_WINDOW, INTERNET, WRITE_EXTERNAL_STORAGE

### Процесс установки
1. Установите APK файл tg.Reward
2. Запустите приложение
3. Введите ключ: `73D37C08`
4. Нажмите кнопку "СТАРТ"
5. Приложение автоматически запустит SO2 с активированным меню

### Использование меню
1. После запуска SO2 появится плавающая иконка меню
2. Нажмите на иконку для открытия полного меню
3. Настройте нужные функции в соответствующих категориях
4. Изменения применяются мгновенно

## ⚙️ Сборка проекта

### Требования для сборки
- Android Studio 4.0+
- Android NDK r22+
- Gradle 6.5+
- JDK 8+

### Команды сборки
```bash
cd tg.Reward
./gradlew assembleDebug     # Debug сборка
./gradlew assembleRelease   # Release сборка
```

### Выходные файлы
```
app/build/outputs/apk/debug/app-debug.apk
app/build/outputs/apk/release/app-release.apk
```

## 🔒 Безопасность

- Ключ аутентификации хранится в зашифрованном виде
- Нативный код обфусцирован (oxorany)
- Строки защищены макросом OBFUSCATE
- Права супер-пользователя для расширенного доступа

## 📄 Лицензия

Проект основан на FloatingModMenu и planet library.
Разработано для образовательных целей.

## 👥 Авторы

- **Original planet library:** из архива planet.zip
- **tg.Reward implementation:** настроена для Standoff 2
- **UI/UX Design:** современный красно-черный стиль

## 🐛 Известные проблемы

- Требуется root-доступ для некоторых функций
- Может конфликтовать с другими модами
- Не работает на эмуляторах без ARM трансляции

## 📞 Поддержка

При возникновении проблем:
1. Убедитесь, что SO2 установлен
2. Проверьте правильность ввода ключа
3. Предоставьте overlay-разрешения
4. Перезапустите приложение

---

**⚡ tg.Reward - Ваше преимущество в Standoff 2! ⚡**
