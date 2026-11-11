#include "mcd_mod_sdk.h"
#include "mcd_config.h"
#include <stdio.h>

static MCD_ModInfo g_mod_info = {
    .id = "mcd_dev_console_unlocker",
    .name = "Unreal Developer Console Unlocker",
    .version = "1.0.0",
    .author = "MCD Modding Team",
    .description = "Enables UE4 native developer console (tilde ~ key) allowing cheat commands, dump commands, and debugging.",
    .category = "Developer / Debug",
    .is_active = true,
    .hotkey = 0xC0 /* VK_OEM_3 (tilde ~) */
};

static MCD_Config g_config;
static uintptr_t g_console_flag_addr = 0;
static uint8_t g_orig_byte = 0;
static bool g_patched = false;

MCD_EXPORT const MCD_ModInfo* MCD_GetModInfo(void) {
    return &g_mod_info;
}

MCD_EXPORT bool MCD_ModInit(void) {
    MCD_Config_Load(&g_config, "configs/dev_console_unlocker.ini");
    g_mod_info.is_active = MCD_Config_GetBool(&g_config, "enabled", true);
    g_mod_info.hotkey = MCD_Config_GetInt(&g_config, "hotkey_vk", 0xC0);

    g_console_flag_addr = MCD_FindPattern("Dungeons-Win64-Shipping.exe", "\xC6\x41\x20\x00\x48\x8B\x5C\x24", "xxxxxxxx");
    if (g_console_flag_addr) {
        g_orig_byte = *(uint8_t*)(g_console_flag_addr + 3);
        if (g_mod_info.is_active) {
            uint8_t enable_val = 0x01;
            MCD_PatchMemory((void*)(g_console_flag_addr + 3), &enable_val, 1);
            g_patched = true;
        }
    }
    return true;
}

MCD_EXPORT void MCD_ModShutdown(void) {
    if (g_patched && g_console_flag_addr) {
        MCD_PatchMemory((void*)(g_console_flag_addr + 3), &g_orig_byte, 1);
        g_patched = false;
    }
}

MCD_EXPORT void MCD_ModUpdate(float delta_time) {
    (void)delta_time;
}

MCD_EXPORT bool MCD_ToggleMod(bool enable) {
    g_mod_info.is_active = enable;
    if (g_console_flag_addr) {
        uint8_t val = enable ? 0x01 : 0x00;
        MCD_PatchMemory((void*)(g_console_flag_addr + 3), &val, 1);
        g_patched = enable;
    }
    return g_mod_info.is_active;
}

MCD_EXPORT bool MCD_IsModEnabled(void) {
    return g_mod_info.is_active;
}

MCD_EXPORT void MCD_OnKeyEvent(int key_code, bool is_down) {
    if (is_down && key_code == g_mod_info.hotkey) {
        MCD_ToggleMod(!g_mod_info.is_active);
    }
}

#ifdef _WIN32
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    (void)hinstDLL;
    (void)lpvReserved;
    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            MCD_ModInit();
            break;
        case DLL_PROCESS_DETACH:
            MCD_ModShutdown();
            break;
    }
    return TRUE;
}
#endif
