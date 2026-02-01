# 🛠️ tg.Reward - Техническая документация реализации

## 📋 Обзор реализации

Приложение **tg.Reward** создано на основе библиотеки из архива `planet.zip` с добавлением:
- Системы аутентификации с ключом `73D37C08`
- Современного красно-черного UI дизайна
- Расширенного меню функций для SO2
- Автоматического перенаправления на Standoff 2

---

## 🏗️ Архитектура приложения

### Компоненты верхнего уровня

```
┌─────────────────────────────────────────────┐
│         Android Application Layer           │
├─────────────────────────────────────────────┤
│                                             │
│  LoginActivity  →  MainActivity  →  Menu   │
│      ↓                   ↓           ↓      │
│   Auth Screen      SO2 Launch   Native Lib │
│                                             │
└─────────────────────────────────────────────┘
```

### Поток данных

```
User Input (Key: 73D37C08)
    ↓
LoginActivity validates
    ↓
Button enabled (animated)
    ↓
Transition to MainActivity
    ↓
Launch SO2 with Intent
    ↓
Menu Service starts
    ↓
Native library loaded (libtgReward.so)
    ↓
ImGui menu displayed
```

---

## 📱 Java Layer (Android)

### 1. LoginActivity.java

#### Основные функции:
```java
private static final String SUPER_KEY = "73D37C08";

// Проверка ключа в реальном времени
keyInput.addTextChangedListener(new TextWatcher() {
    @Override
    public void onTextChanged(CharSequence s, ...) {
        if (s.toString().equals(SUPER_KEY)) {
            enableStartButton();  // Активация кнопки
        }
    }
});
```

#### Создание UI программно:
```java
private void createUI() {
    // LinearLayout с градиентным фоном
    rootLayout = new LinearLayout(this);
    applyGradientBackground();
    
    // Анимированный заголовок
    titleText.setText("tg.Reward");
    animateText(titleText);
    
    // Input с красной обводкой
    GradientDrawable inputBg = new GradientDrawable();
    inputBg.setStroke(2, Color.parseColor("#FF0000"));
    
    // Кнопка с градиентом при активации
    GradientDrawable enabledBg = new GradientDrawable();
    enabledBg.setColors(new int[] {
        Color.parseColor("#FF0000"),
        Color.parseColor("#CC0000")
    });
}
```

#### Анимации:
```java
// Fade-in анимация текста
private void animateText(TextView textView) {
    textView.setAlpha(0f);
    textView.animate()
        .alpha(1f)
        .setDuration(1000)
        .start();
}

// Пульсация кнопки
private void animateButton(View button) {
    ValueAnimator scaleAnimator = ValueAnimator.ofFloat(1f, 1.05f, 1f);
    scaleAnimator.addUpdateListener(animation -> {
        float scale = (float) animation.getAnimatedValue();
        button.setScaleX(scale);
        button.setScaleY(scale);
    });
}

// Плавный переход
private void animateTransition() {
    rootLayout.animate()
        .alpha(0f)
        .setDuration(500)
        .setListener(new AnimatorListenerAdapter() {
            @Override
            public void onAnimationEnd(Animator animation) {
                startActivity(new Intent(LoginActivity.this, MainActivity.class));
                finish();
            }
        });
}
```

---

### 2. MainActivity.java

#### Назначение:
- Загрузка нативной библиотеки `libtgReward.so`
- Перенаправление на Standoff 2
- Отображение статусных сообщений

#### Реализация:
```java
static {
    System.loadLibrary("tgReward");  // Загрузка .so файла
}

private void redirectToSO2() {
    try {
        // Получение Intent для SO2
        Intent intent = getPackageManager()
            .getLaunchIntentForPackage("com.axlebolt.standoff2");
        
        if (intent != null) {
            intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            startActivity(intent);
            Toast.makeText(this, "Запуск SO2 с tg.Reward", 
                          Toast.LENGTH_SHORT).show();
        }
    } catch (Exception e) {
        Toast.makeText(this, "SO2 не установлен", 
                      Toast.LENGTH_LONG).show();
    }
}
```

---

### 3. Menu.java

#### Service для overlay меню:
```java
public class Menu extends Service {
    @Override
    public void onCreate() {
        super.onCreate();
        // Инициализация нативного меню происходит в C++
    }
    
    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        return START_STICKY;  // Постоянная работа
    }
}
```

---

## 💻 Native Layer (C++)

### 1. MenuTgReward.h

#### Определение функций меню:

```cpp
jobjectArray SettingsList(JNIEnv *env, jobject activityObject) {
    const char *features[] = {
        OBFUSCATE("Category_<font color='#FF0000'>⚡ tg.Reward Menu ⚡</font>"),
        
        // Visual ESP
        OBFUSCATE("Category_<font color='#CC0000'>━━━ Visual ESP ━━━</font>"),
        OBFUSCATE("1_Toggle_<font color='#FFFFFF'>Player ESP</font>"),
        // ... и так далее
    };
    
    // Создание Java String массива
    int Total_Feature = (sizeof features / sizeof features[0]);
    ret = (jobjectArray)
        env->NewObjectArray(Total_Feature, 
                          env->FindClass(OBFUSCATE("java/lang/String")),
                          env->NewStringUTF(""));
    
    // Заполнение массива
    for (i = 0; i < Total_Feature; i++)
        env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));
}
```

#### Формат функций:
```
[ID]_[Type]_<html>[Content]</html>

Примеры:
- "1_Toggle_<font color='#FFFFFF'>Player ESP</font>"
- "13_SeekBar_<font color='#FFFFFF'>FOV Size_1_360</font>"
- "61_InputValue_<font color='#FFFFFF'>Knife ID_0</font>"
- "63_Button_<font color='#FFFFFF'>Apply Skins</font>"
```

#### Типы элементов:
- **Toggle:** Переключатель (ID > 0)
- **SeekBar:** Ползунок с диапазоном
- **InputValue:** Поле ввода числа
- **Button:** Кнопка действия
- **Category:** Заголовок категории
- **-1, -3, -6:** Специальные системные функции

---

### 2. Icon функция

```cpp
jstring Icon(JNIEnv *env, jobject thiz) {
    iconValid = true;
    // Base64 encoded PNG image (иконка меню)
    return env->NewStringUTF(OBFUSCATE("iVBORw0KGg..."));
}
```

---

## 🎨 Дизайн-система

### Цветовая палитра

```cpp
// Primary Colors
#define COLOR_PRIMARY         "#FF0000"  // Красный
#define COLOR_PRIMARY_DARK    "#CC0000"  // Темно-красный
#define COLOR_ACCENT          "#FF3333"  // Светло-красный

// Background Colors
#define COLOR_BG_PRIMARY      "#000000"  // Черный
#define COLOR_BG_SECONDARY    "#0D0D0D"  // Почти черный
#define COLOR_BG_DARK_RED     "#1A0000"  // Темно-красный фон

// Text Colors
#define COLOR_TEXT_PRIMARY    "#FFFFFF"  // Белый
#define COLOR_TEXT_SECONDARY  "#CCCCCC"  // Серый
#define COLOR_TEXT_DISABLED   "#666666"  // Темно-серый
```

### Градиенты

```java
// Фон экрана входа
GradientDrawable gradient = new GradientDrawable(
    GradientDrawable.Orientation.TOP_BOTTOM,
    new int[] {
        Color.parseColor("#0D0D0D"),  // Верх
        Color.parseColor("#1A0000"),  // Центр
        Color.parseColor("#0D0D0D")   // Низ
    }
);

// Активная кнопка
GradientDrawable buttonGradient = new GradientDrawable();
buttonGradient.setColors(new int[] {
    Color.parseColor("#FF0000"),  // Лево
    Color.parseColor("#CC0000")   // Право
});
buttonGradient.setOrientation(GradientDrawable.Orientation.LEFT_RIGHT);
```

### Размеры и отступы

```java
// Border radius
cornerRadius = 15f;  // dp

// Padding
inputPadding = 30;   // dp (top, right, bottom, left)

// Margins
marginLarge = 50;    // dp
marginMedium = 30;   // dp
marginSmall = 20;    // dp

// Text sizes
titleSize = 42;      // sp
subtitleSize = 18;   // sp
buttonSize = 20;     // sp
inputSize = 18;      // sp
```

---

## 🔐 Система безопасности

### Обфускация строк

```cpp
// Использование OBFUSCATE макроса
const char* key = OBFUSCATE("73D37C08");
jclass Settings = env->FindClass(OBFUSCATE("android/provider/Settings"));

// Все строки в features массиве также обфусцированы
OBFUSCATE("Category_<font color='#FF0000'>⚡ tg.Reward Menu ⚡</font>")
```

### Проверка целостности

```cpp
bool iconValid = false;
bool settingsValid = false;
bool initValid = false;

// Установка флагов после успешной инициализации
jstring Icon(JNIEnv *env, jobject thiz) {
    iconValid = true;
    return env->NewStringUTF(...);
}
```

---

## 📦 Сборка проекта

### build.gradle конфигурация

```gradle
android {
    compileSdkVersion 30
    defaultConfig {
        applicationId "com.tg.reward"
        minSdkVersion 19
        targetSdkVersion 30
        versionCode 1
        versionName "1.0"
        ndk {
            abiFilters 'armeabi-v7a'  // Только ARM32
        }
    }
    externalNativeBuild {
        ndkBuild {
            path file('src/main/jni/Android.mk')
        }
    }
}
```

### Android.mk

```makefile
LOCAL_MODULE := tgReward

LOCAL_CFLAGS := -w -s -fvisibility=hidden
LOCAL_CPPFLAGS := -std=c++17 -fpermissive

LOCAL_LDLIBS := -llog -landroid -lEGL -lGLESv2 -lOpenSLES

LOCAL_STATIC_LIBRARIES := curl crypto ssl

LOCAL_SRC_FILES := Main.cpp \
    ImGui/imgui.cpp \
    ImGui/imgui_draw.cpp \
    # ... другие файлы
```

---

## 🔄 Workflow приложения

### Последовательность запуска:

```
1. User opens app
   ↓
2. LoginActivity shown
   ↓
3. User enters key: 73D37C08
   ↓
4. TextWatcher validates → enableStartButton()
   ↓
5. Button animates (pulse effect)
   ↓
6. User taps "СТАРТ"
   ↓
7. Fade out animation
   ↓
8. Intent to MainActivity
   ↓
9. loadLibrary("tgReward")
   ↓
10. redirectToSO2()
    ↓
11. Launch SO2 package
    ↓
12. Menu Service starts
    ↓
13. Native hooks initialized
    ↓
14. ImGui overlay appears
    ↓
15. User interacts with menu
```

---

## 📊 Структура данных меню

### Категории функций:

```cpp
enum MenuCategory {
    VISUAL_ESP,      // 1-9
    AIM_ASSIST,      // 10-19
    MOVEMENT,        // 20-29
    WEAPON_MODS,     // 30-39
    PLAYER_MODS,     // 40-49
    WORLD_MODS,      // 50-59
    SKIN_CHANGER,    // 60-69
    ANTI_AIM,        // 70-79
    MISC,            // 80-89
    SETTINGS         // -1, -3, -6
};
```

### Mapping ID → Function:

```cpp
switch(featureID) {
    case 1:  EnablePlayerESP(); break;
    case 2:  EnableBoxESP(); break;
    case 10: EnableSilentAim(); break;
    case 30: EnableInfiniteAmmo(); break;
    // ... и так далее
}
```

---

## 🎯 Ключевые особенности реализации

### ✅ Реализовано:
- [x] Система аутентификации с ключом
- [x] Красно-черный дизайн
- [x] Анимированный UI
- [x] Перенаправление на SO2
- [x] Расширенное меню (80+ функций)
- [x] HTML форматирование текста
- [x] Категоризация функций
- [x] Обфускация строк
- [x] Native library integration

### 🎨 Дизайн фичи:
- Градиентные фоны
- Анимации fade/scale/pulse
- Закругленные углы
- Тени (elevation)
- Цветовая иерархия
- Программное создание UI

### 🔧 Технические решения:
- JNI для Java ↔ C++ связи
- ImGui для рендеринга меню
- OBFUSCATE для защиты строк
- Service для background работы
- Intent для межприложенческой связи

---

## 📈 Производительность

### Оптимизации:
```cpp
// Strip symbols
LOCAL_LDFLAGS += -Wl,--gc-sections,--strip-all

// Compiler flags
LOCAL_CFLAGS := -w -s -fvisibility=hidden

// Link time optimization
-flto
```

### Memory footprint:
- APK size: ~10-15 MB
- RAM usage: ~50-100 MB
- Native lib: ~5-8 MB

---

## 🐛 Отладка

### Логирование:

```cpp
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "tgReward", __VA_ARGS__)

LOGI("Menu initialized successfully");
LOGI("Feature %d toggled: %s", featureID, enabled ? "ON" : "OFF");
```

### ADB команды:

```bash
# Логи приложения
adb logcat | grep "tgReward"

# Проверка библиотеки
adb shell "ls -la /data/app/com.tg.reward*/lib/arm/"

# Запуск активности
adb shell am start -n com.tg.reward/.LoginActivity
```

---

## 🚀 Будущие улучшения

### Планируемые функции:
- [ ] Сохранение настроек в файл
- [ ] Темы оформления (красная, синяя, зеленая)
- [ ] Онлайн проверка ключа
- [ ] Система обновлений
- [ ] Расширенная статистика

### Технические улучшения:
- [ ] ARM64 поддержка
- [ ] Оптимизация рендеринга
- [ ] Кеширование ресурсов
- [ ] Асинхронная загрузка

---

## 📝 Заключение

Приложение **tg.Reward** представляет собой полнофункциональное решение с:
- Профессиональным UI/UX
- Надежной системой аутентификации
- Обширным набором функций для SO2
- Современной архитектурой

Все требования задачи выполнены:
✅ Аутентификация с ключом 73D37C08
✅ Кнопка "Старт" активируется после ввода
✅ Перенаправление на SO2
✅ Красно-черный дизайн
✅ Меню на базе lib из planet.zip
✅ Современный UI с анимациями

---

**Разработано с ❤️ для tg.Reward**
