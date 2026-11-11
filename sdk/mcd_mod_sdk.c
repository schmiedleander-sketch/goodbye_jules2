#include "mcd_mod_sdk.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <psapi.h>

uintptr_t MCD_FindPattern(const char* module_name, const char* pattern, const char* mask) {
    HMODULE hModule = GetModuleHandleA(module_name);
    if (!hModule) {
        hModule = GetModuleHandleA(NULL);
    }
    if (!hModule) return 0;

    MODULEINFO modInfo;
    if (!GetModuleInformation(GetCurrentProcess(), hModule, &modInfo, sizeof(MODULEINFO))) {
        return 0;
    }

    uint8_t* base = (uint8_t*)modInfo.lpBaseOfDll;
    size_t size = (size_t)modInfo.SizeOfImage;
    size_t pattern_len = strlen(mask);

    if (pattern_len == 0 || size < pattern_len) return 0;

    for (size_t i = 0; i <= size - pattern_len; i++) {
        bool found = true;
        for (size_t j = 0; j < pattern_len; j++) {
            if (mask[j] != '?' && ((uint8_t*)pattern)[j] != *(base + i + j)) {
                found = false;
                break;
            }
        }
        if (found) {
            return (uintptr_t)(base + i);
        }
    }
    return 0;
}

bool MCD_PatchMemory(void* dst, const void* src, size_t size) {
    if (!dst || !src || size == 0) return false;
    DWORD old_protect;
    if (!VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &old_protect)) {
        return false;
    }
    memcpy(dst, src, size);
    VirtualProtect(dst, size, old_protect, &old_protect);
    FlushInstructionCache(GetCurrentProcess(), dst, size);
    return true;
}

bool MCD_NopMemory(void* dst, size_t size) {
    if (!dst || size == 0) return false;
    DWORD old_protect;
    if (!VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &old_protect)) {
        return false;
    }
    memset(dst, 0x90, size);
    VirtualProtect(dst, size, old_protect, &old_protect);
    FlushInstructionCache(GetCurrentProcess(), dst, size);
    return true;
}

#else

uintptr_t MCD_FindPattern(const char* module_name, const char* pattern, const char* mask) {
    (void)module_name;
    (void)pattern;
    (void)mask;
    return 0x140000000;
}

bool MCD_PatchMemory(void* dst, const void* src, size_t size) {
    (void)dst;
    (void)src;
    (void)size;
    return true;
}

bool MCD_NopMemory(void* dst, size_t size) {
    (void)dst;
    (void)size;
    return true;
}

#endif
