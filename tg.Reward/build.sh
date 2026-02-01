#!/bin/bash

# 🔨 Скрипт автоматической сборки tg.Reward APK
# Версия: 1.0
# Дата: 2026-02-01

set -e  # Выход при ошибке

# Цвета для вывода
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}================================${NC}"
echo -e "${BLUE}🚀 tg.Reward APK Builder${NC}"
echo -e "${BLUE}================================${NC}\n"

# Проверка Java
echo -e "${YELLOW}[1/6]${NC} Проверка Java..."
if ! command -v java &> /dev/null; then
    echo -e "${RED}❌ Java не найдена. Установите OpenJDK 11${NC}"
    exit 1
fi
echo -e "${GREEN}✓${NC} Java найдена: $(java -version 2>&1 | head -n 1)"

# Проверка Android SDK
echo -e "\n${YELLOW}[2/6]${NC} Проверка Android SDK..."
if [ ! -d "/opt/android-sdk" ]; then
    echo -e "${RED}❌ Android SDK не найден в /opt/android-sdk${NC}"
    echo -e "${YELLOW}Установите SDK согласно BUILD_INSTRUCTIONS.md${NC}"
    exit 1
fi
echo -e "${GREEN}✓${NC} Android SDK найден"

# Проверка Android NDK
echo -e "\n${YELLOW}[3/6]${NC} Проверка Android NDK..."
if [ ! -d "/opt/android-sdk/ndk/22.0.7026061" ]; then
    echo -e "${RED}❌ Android NDK r22 не найден${NC}"
    exit 1
fi
echo -e "${GREEN}✓${NC} Android NDK r22 найден"

# Настройка переменных окружения
echo -e "\n${YELLOW}[4/6]${NC} Настройка переменных окружения..."
export JAVA_HOME=/usr/lib/jvm/java-11-openjdk-amd64
export ANDROID_SDK_ROOT=/opt/android-sdk
export ANDROID_HOME=/opt/android-sdk
export ANDROID_NDK_HOME=/opt/android-sdk/ndk/22.0.7026061
export PATH=$PATH:/opt/android-sdk/platform-tools
echo -e "${GREEN}✓${NC} Переменные окружения установлены"

# Проверка Gradle
echo -e "\n${YELLOW}[5/6]${NC} Проверка Gradle..."
if [ ! -f "gradle-7.2/bin/gradle" ]; then
    echo -e "${YELLOW}Gradle 7.2 не найден. Загружаю...${NC}"
    wget -q https://services.gradle.org/distributions/gradle-7.2-bin.zip
    unzip -q gradle-7.2-bin.zip
    rm gradle-7.2-bin.zip
    echo -e "${GREEN}✓${NC} Gradle 7.2 загружен"
else
    echo -e "${GREEN}✓${NC} Gradle 7.2 найден"
fi

# Сборка APK
echo -e "\n${YELLOW}[6/6]${NC} Сборка APK..."
echo -e "${BLUE}Это может занять несколько минут...${NC}\n"

# Очистка предыдущих сборок
echo -e "  ${YELLOW}→${NC} Очистка предыдущих сборок..."
gradle-7.2/bin/gradle clean --no-daemon -q

# Компиляция нативного кода
echo -e "  ${YELLOW}→${NC} Компиляция нативного кода (C++/JNI)..."
cd app/src/main/jni
$ANDROID_NDK_HOME/ndk-build \
    NDK_PROJECT_PATH=. \
    APP_BUILD_SCRIPT=./Android.mk \
    NDK_APPLICATION_MK=./Application.mk \
    -j$(nproc) || {
    echo -e "${RED}❌ Ошибка компиляции нативного кода${NC}"
    exit 1
}
cd ../../../..

# Сборка APK
echo -e "  ${YELLOW}→${NC} Сборка Debug APK..."
gradle-7.2/bin/gradle assembleDebug --no-daemon || {
    echo -e "${RED}❌ Ошибка сборки APK${NC}"
    exit 1
}

# Копирование APK в папку тутапк
echo -e "  ${YELLOW}→${NC} Копирование APK в папку тутапк..."
mkdir -p ../тутапк
cp app/build/outputs/apk/debug/app-debug.apk ../тутапк/tg.Reward-debug.apk

# Вывод информации о собранном APK
echo -e "\n${GREEN}================================${NC}"
echo -e "${GREEN}✅ Сборка успешно завершена!${NC}"
echo -e "${GREEN}================================${NC}\n"

APK_PATH="../тутапк/tg.Reward-debug.apk"
APK_SIZE=$(du -h "$APK_PATH" | cut -f1)

echo -e "${BLUE}📦 Информация о APK:${NC}"
echo -e "  Файл: ${GREEN}$APK_PATH${NC}"
echo -e "  Размер: ${GREEN}$APK_SIZE${NC}"
echo -e "  Архитектура: ${GREEN}arm64-v8a${NC}"
echo -e "  Версия: ${GREEN}Debug${NC}"

echo -e "\n${BLUE}📱 Установка на устройство:${NC}"
echo -e "  ${YELLOW}adb install $APK_PATH${NC}"

echo -e "\n${BLUE}🔍 Проверка APK:${NC}"
echo -e "  ${YELLOW}aapt dump badging $APK_PATH | grep package${NC}"

echo -e "\n${GREEN}Готово!${NC} 🎉\n"
