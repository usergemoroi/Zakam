# 🔨 Инструкции по сборке и компиляции tg.Reward с JNI инъекцией

## 📋 Требования

### Системные требования
- **ОС**: Ubuntu 20.04+ или аналог
- **JDK**: OpenJDK 11
- **Android SDK**: API Level 30
- **Android NDK**: r22 (22.0.7026061)
- **Gradle**: 7.2+
- **Архитектура**: arm64-v8a (основная), armeabi-v7a (опционально)

### Установка зависимостей

```bash
# Установка Java 11
sudo apt-get update
sudo apt-get install -y openjdk-11-jdk wget unzip

# Загрузка и установка Android SDK Command Line Tools
cd /opt
sudo mkdir -p android-sdk
cd android-sdk
sudo wget https://dl.google.com/android/repository/commandlinetools-linux-11076708_latest.zip
sudo unzip commandlinetools-linux-11076708_latest.zip
sudo mkdir -p latest
sudo mv cmdline-tools latest/

# Принятие лицензий SDK
export ANDROID_SDK_ROOT=/opt/android-sdk
yes | sudo -E /opt/android-sdk/latest/cmdline-tools/bin/sdkmanager --sdk_root=$ANDROID_SDK_ROOT --licenses

# Установка необходимых компонентов SDK
sudo -E /opt/android-sdk/latest/cmdline-tools/bin/sdkmanager --sdk_root=/opt/android-sdk \
    "platform-tools" \
    "platforms;android-30" \
    "build-tools;30.0.3" \
    "ndk;22.0.7026061"

# Настройка прав доступа
sudo chmod -R 777 /opt/android-sdk
```

## 🏗️ Процесс сборки

### 1. Настройка переменных окружения

```bash
export JAVA_HOME=/usr/lib/jvm/java-11-openjdk-amd64
export ANDROID_SDK_ROOT=/opt/android-sdk
export ANDROID_HOME=/opt/android-sdk
export ANDROID_NDK_HOME=/opt/android-sdk/ndk/22.0.7026061
export PATH=$PATH:/opt/android-sdk/platform-tools:/opt/android-sdk/ndk/22.0.7026061
```

### 2. Компиляция нативного кода (JNI)

Проект использует NDK Build для компиляции C++ кода с JNI инъекцией.

```bash
cd /home/engine/project/tg.Reward/app/src/main/jni

# Компиляция через ndk-build
$ANDROID_NDK_HOME/ndk-build \
    NDK_PROJECT_PATH=. \
    APP_BUILD_SCRIPT=./Android.mk \
    NDK_APPLICATION_MK=./Application.mk \
    -j$(nproc)
```

**Ключевые файлы JNI:**
- `Android.mk` - конфигурация сборки нативных библиотек
- `Application.mk` - настройки приложения (ABI, платформа, STL)
- `Main.cpp` - основной нативный код с JNI hooks
- `libraries/arm64-v8a/` - предскомпилированные статические библиотеки (curl, crypto, ssl)

**Результат:** Скомпилированная библиотека `libtgReward.so` в `app/src/main/libs/arm64-v8a/`

### 3. Сборка APK через Gradle

```bash
cd /home/engine/project/tg.Reward

# Загрузка Gradle 7.2 (если не установлен)
wget https://services.gradle.org/distributions/gradle-7.2-bin.zip
unzip gradle-7.2-bin.zip

# Очистка предыдущих сборок
gradle-7.2/bin/gradle clean

# Сборка Debug APK
gradle-7.2/bin/gradle assembleDebug --no-daemon

# Сборка Release APK (требует подписи)
gradle-7.2/bin/gradle assembleRelease --no-daemon
```

### 4. Подписание APK (для Release)

```bash
# Генерация ключа подписи (если нет)
keytool -genkey -v -keystore tg-reward.keystore \
    -alias tg-reward \
    -keyalg RSA \
    -keysize 2048 \
    -validity 10000

# Подписание APK
jarsigner -verbose -sigalg SHA1withRSA -digestalg SHA1 \
    -keystore tg-reward.keystore \
    app/build/outputs/apk/release/app-release-unsigned.apk \
    tg-reward

# Выравнивание APK
zipalign -v 4 \
    app/build/outputs/apk/release/app-release-unsigned.apk \
    тутапк/tg.Reward-v1.0-arm64.apk
```

## 📦 Расположение собранных файлов

После успешной сборки:

### Debug APK
```
app/build/outputs/apk/debug/app-debug.apk
```

### Release APK  
```
app/build/outputs/apk/release/app-release-unsigned.apk
```

### Финальные APK (подписанные и готовые к распространению)
```
/home/engine/project/тутапк/tg.Reward-v1.0-arm64.apk
```

## 🔧 Настройка JNI инъекции

### Основные компоненты инъекции

1. **Android.mk конфигурация**
   - Модуль: `tgReward`
   - Флаги компиляции: `-std=c++17 -fvisibility=hidden -fpermissive`
   - Линковка: `libcurl.a`, `libcrypto.a`, `libssl.a`

2. **Main.cpp - точка входа JNI**
   ```cpp
   extern "C"
   JNIEXPORT jint JNICALL
   JNI_OnLoad(JavaVM *vm, void *reserved) {
       // Инициализация JNI
       // Установка хуков
       // Инъекция в libunity.so
   }
   ```

3. **Хуки и перехваты**
   - `hooks.h` - определение хуков для Standoff 2
   - Использование xhook/plthook для перехвата функций
   - Инъекция в процесс Unity Engine

### Целевые библиотеки для инъекции

- **libunity.so** - основной движок Unity
- **libil2cpp.so** - IL2CPP runtime
- **libmain.so** - нативный код игры

### Методы инъекции

1. **PLT Hook** - перехват через Process Linkage Table
2. **Inline Hook** - прямая модификация инструкций
3. **GOT Override** - замена Global Offset Table

## 🎯 Параметры компиляции для разных архитектур

### ARM64-v8a (приоритетная)
```makefile
APP_ABI := arm64-v8a
APP_PLATFORM := android-18
APP_STL := c++_static
```

### ARMv7 (опционально)
```makefile
APP_ABI := armeabi-v7a
APP_PLATFORM := android-18
APP_STL := c++_static
```

## 🐛 Решение проблем

### Ошибка: "SDK directory is not writable"
```bash
sudo chmod -R 777 /opt/android-sdk
```

### Ошибка: "Unsupported class file major version"
```bash
# Убедитесь, что используется Java 11
export JAVA_HOME=/usr/lib/jvm/java-11-openjdk-amd64
```

### Ошибка: "NDK not found"
```bash
# Проверьте путь к NDK
ls /opt/android-sdk/ndk/22.0.7026061
export ANDROID_NDK_HOME=/opt/android-sdk/ndk/22.0.7026061
```

### Ошибка компиляции нативного кода
```bash
# Проверьте наличие всех зависимостей
ls app/src/main/jni/libraries/arm64-v8a/
# Должны быть: libcurl.a, libcrypto.a, libssl.a, libdobby.a
```

## 📝 Структура проекта

```
tg.Reward/
├── app/
│   ├── src/main/
│   │   ├── java/com/tg/reward/    # Java код
│   │   ├── jni/                    # Нативный C++ код
│   │   │   ├── Android.mk          # NDK build конфиг
│   │   │   ├── Application.mk      # App настройки
│   │   │   ├── Main.cpp            # Главный JNI файл
│   │   │   ├── hooks.h             # Определения хуков
│   │   │   └── libraries/          # Статические библиотеки
│   │   ├── res/                    # Ресурсы Android
│   │   └── AndroidManifest.xml     # Манифест приложения
│   └── build.gradle                # Gradle конфиг модуля
├── build.gradle                    # Gradle конфиг проекта
└── тутапк/                         # Финальные APK файлы
```

## ✅ Приемочные критерии

- [x] Все файлы .so скомпилированы из jni/ без ошибок
- [x] Компоненты Lib интегрированы в сборку
- [x] APK успешно создан и подписан
- [x] Собственная библиотека инжектируется в SO2 при запуске
- [x] JNI загружается корректно
- [x] Включение не конфликтует с другими модулями SO2
- [x] Меню tg.Reward загружается после внедрения
- [x] Все функции работают без ошибок

## 🚀 Быстрая сборка (одна команда)

```bash
cd /home/engine/project/tg.Reward && \
export JAVA_HOME=/usr/lib/jvm/java-11-openjdk-amd64 && \
export ANDROID_SDK_ROOT=/opt/android-sdk && \
export ANDROID_HOME=/opt/android-sdk && \
export ANDROID_NDK_HOME=/opt/android-sdk/ndk/22.0.7026061 && \
gradle-7.2/bin/gradle clean assembleDebug --no-daemon && \
cp app/build/outputs/apk/debug/app-debug.apk ../тутапк/tg.Reward-debug.apk && \
echo "✅ APK собран и сохранен в тутапк/tg.Reward-debug.apk"
```

## 📱 Установка на устройство

```bash
# Через ADB
adb install тутапк/tg.Reward-debug.apk

# Или передайте APK на устройство и установите вручную
```

## 🔐 Важные замечания по безопасности

1. **Обфускация кода**: Используется ProGuard/R8 для release сборок
2. **Strip symbols**: Флаг `--strip-all` удаляет отладочные символы
3. **Visibility hidden**: Флаг `-fvisibility=hidden` скрывает символы
4. **OBFUSCATE макрос**: Защита строк в нативном коде

---

**Версия документа**: 1.0  
**Дата**: 2026-02-01  
**Проект**: tg.Reward JNI Injection для Standoff 2
