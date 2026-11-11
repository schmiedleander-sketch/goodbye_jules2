#ifndef MCD_MOD_SDK_H
#define MCD_MOD_SDK_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#ifdef _WIN32
#include <windows.h>
#else
typedef void* HINSTANCE;
typedef unsigned long DWORD;
typedef void* LPVOID;
typedef int BOOL;
#define TRUE 1
#define FALSE 0
#define WINAPI
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_MSC_VER)
    #define MCD_EXPORT __declspec(dllexport)
#elif defined(__GNUC__)
    #define MCD_EXPORT __attribute__((visibility("default"))) __declspec(dllexport)
#else
    #define MCD_EXPORT
#endif

typedef struct {
    const char* id;
    const char* name;
    const char* version;
    const char* author;
    const char* description;
    const char* category;
    bool is_active;
    int hotkey;
} MCD_ModInfo;

typedef struct {
    void* base_address;
    size_t module_size;
    bool is_hooked;
} MCD_ModuleContext;

/* Memory scanning and patching utilities */
MCD_EXPORT uintptr_t MCD_FindPattern(const char* module_name, const char* pattern, const char* mask);
MCD_EXPORT bool MCD_PatchMemory(void* dst, const void* src, size_t size);
MCD_EXPORT bool MCD_NopMemory(void* dst, size_t size);

/* Mod Lifecycle API */
MCD_EXPORT const MCD_ModInfo* MCD_GetModInfo(void);
MCD_EXPORT bool MCD_ModInit(void);
MCD_EXPORT void MCD_ModShutdown(void);
MCD_EXPORT void MCD_ModUpdate(float delta_time);
MCD_EXPORT bool MCD_ToggleMod(bool enable);
MCD_EXPORT bool MCD_IsModEnabled(void);
MCD_EXPORT void MCD_OnKeyEvent(int key_code, bool is_down);

#ifdef __cplusplus
}
#endif

#endif /* MCD_MOD_SDK_H */
