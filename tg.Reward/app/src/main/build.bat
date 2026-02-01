@echo off
setlocal

set NDK_ROOT=C:\Android\ndk
set NDK_BUILD=%NDK_ROOT%\ndk-build.cmd

set JNI_PATH=.\jni
set ANDROID_MK_PATH=%JNI_PATH%\Android.mk
set APPLICATION_MK_PATH=%JNI_PATH%\Application.mk

%NDK_BUILD% NDK_PROJECT_PATH=. NDK_APPLICATION_MK=%APPLICATION_MK_PATH% APP_BUILD_SCRIPT=%ANDROID_MK_PATH%

pause
