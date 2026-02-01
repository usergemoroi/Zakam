#ifndef UTILS
#define UTILS

#include <jni.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include "Logger.h"
typedef unsigned long DWORD;
static uintptr_t libBase;
const char* libName = oxorany("libunity.so");
bool libLoaded = oxorany(false);

DWORD findLibrary(const char *library) {
    char filename[0xFF] = {oxorany(0)},
            buffer[1024] = {oxorany(0)};
    FILE *fp = NULL;
    DWORD address = oxorany(0);

    sprintf(filename, oxorany("/proc/self/maps"));

    fp = fopen(filename, oxorany("rt"));
    if (fp == NULL) {
        perror(oxorany("fopen"));
        goto done;
    }

    while (fgets(buffer, sizeof(buffer), fp)) {
        if (strstr(buffer, library)) {
            address = (DWORD) strtoul(buffer, NULL, oxorany(16));
            goto done;
        }
    }

    done:

    if (fp) {
        fclose(fp);
    }

    return address;
}

DWORD getAbsoluteAddress(const char *libraryName, DWORD relativeAddr) {
    libBase = findLibrary(libraryName);
    if (libBase == oxorany(0))
        return oxorany(0);
    return (reinterpret_cast<DWORD>(libBase + relativeAddr));
}


jboolean isGameLibLoaded(JNIEnv *env, jobject thiz) {
    return libLoaded;
}

bool isLibraryLoaded(const char *libraryName) {
    //libLoaded = true;
    char line[512] = {oxorany(0)};
    FILE *fp = fopen(oxorany("/proc/self/maps"), oxorany("rt"));
    if (fp != NULL) {
        while (fgets(line, sizeof(line), fp)) {
            std::string a = line;
            if (strstr(line, libraryName)) {
                libLoaded = oxorany(true);
                return oxorany(true);
            }
        }
        fclose(fp);
    }
    return oxorany(false);
}
DWORD getRealOffset(DWORD address) {
    if (libBase == oxorany(0)) {
        libBase = findLibrary(libName);
    }
    return (libBase + address);
}

uintptr_t string2Offset(const char *c) {
    int base = oxorany(16);
    // See if this function catches all possibilities.
    // If it doesn't, the function would have to be amended
    // whenever you add a combination of architecture and
    // compiler that is not yet addressed.
    static_assert(sizeof(uintptr_t) == sizeof(unsigned long)
                  || sizeof(uintptr_t) == sizeof(unsigned long long),
                  "Please add string to handle conversion for this architecture.");

    // Now choose the correct function ...
    if (sizeof(uintptr_t) == sizeof(unsigned long)) {
        return strtoul(c, nullptr, base);
    }

    // All other options exhausted, sizeof(uintptr_t) == sizeof(unsigned long long))
    return strtoull(c, nullptr, base);
}

namespace ToastLength {
    inline const int LENGTH_LONG = oxorany(1);
    inline const int LENGTH_SHORT = oxorany(0);
}

#endif
