LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := curl
LOCAL_SRC_FILES := libraries/$(TARGET_ARCH_ABI)/libcurl.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := crypto
LOCAL_SRC_FILES := libraries/$(TARGET_ARCH_ABI)/libcrypto.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := ssl
LOCAL_SRC_FILES := libraries/$(TARGET_ARCH_ABI)/libssl.a
include $(PREBUILT_STATIC_LIBRARY)

# --- main module tgReward ---
include $(CLEAR_VARS)
LOCAL_MODULE    := tgReward

LOCAL_CFLAGS := -w -s -Wno-error=format-security -fvisibility=hidden -fpermissive -fexceptions
LOCAL_CPPFLAGS := -w -s -Wno-error=format-security -fvisibility=hidden -Werror -std=c++17
LOCAL_CPPFLAGS += -Wno-error=c++11-narrowing -fpermissive -Wall -fexceptions

# Линки
LOCAL_LDFLAGS += -Wl,--gc-sections,--strip-all
# используем системный zlib через -lz
LOCAL_LDLIBS := -llog -landroid -lEGL -lGLESv2 -lz -lOpenSLES
LOCAL_ARM_MODE := arm

# Добавляем все статические зависимости
LOCAL_STATIC_LIBRARIES := curl crypto ssl

# Инклуды
LOCAL_C_INCLUDES += $(LOCAL_PATH)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/ImGui
LOCAL_C_INCLUDES += $(LOCAL_PATH)/ImGui/backends

# Исходники
LOCAL_SRC_FILES := Main.cpp \
    ImGui/imgui.cpp \
    ImGui/imgui_draw.cpp \
    ImGui/imgui_demo.cpp \
    ImGui/imgui_widgets.cpp \
    ImGui/imgui_tables.cpp \
    ImGui/backends/imgui_impl_opengl3.cpp \
    ImGui/backends/imgui_impl_android.cpp \
    xdl/xdl.c \
    xdl/xdl_iterate.c \
    xdl/xdl_linker.c \
    xdl/xdl_lzma.c \
    xdl/xdl_util.c \
    map/Map.cpp \
    KittyMemory/KittyMemory.cpp \
    KittyMemory/MemoryPatch.cpp \
    KittyMemory/MemoryBackup.cpp \
    KittyMemory/KittyUtils.cpp \
    Plthook/plthook_elf.c \
    Xhook/xh_core.c \
    Xhook/xh_elf.c \
    Xhook/xh_jni.c \
    Xhook/xh_log.c \
    Xhook/xh_util.c \
    Xhook/xh_version.c \
    Xhook/xhook.c

include $(BUILD_SHARED_LIBRARY)