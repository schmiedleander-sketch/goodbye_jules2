#include "mcd_mod_sdk.h"
#include "mcd_config.h"
#include <stdio.h>

static MCD_ModInfo g_mod_info = {
    .id = "mcd_speed_hack",
    .name = "Movement Speed & Roll Distance Multiplier",
    .version = "1.0.0",
    .author = "MCD Modding Team",
    .description = "Customizable hero movement speed and extended roll jump distance (default: 2.5x).",
    .category = "Movement / Utility",
    .is_active = true,
    .hotkey = 0x74 /* VK_F5 */
};

static MCD_Config g_config;
static float g_speed_multiplier = 2.5f;
static float g_roll_multiplier = 2.0f;
static uintptr_t g_speed_addr = 0;
static uint8_t g_orig_bytes[8];
static bool g_patched = false;

MCD_EXPORT const MCD_ModInfo* MCD_GetModInfo(void) {
    return &g_mod_info;
}

MCD_EXPORT float MCD_GetSpeedMultiplier(void) {
    return g_mod_info.is_active ? g_speed_multiplier : 1.0f;
}

MCD_EXPORT float MCD_GetRollMultiplier(void) {
    return g_mod_info.is_active ? g_roll_multiplier : 1.0f;
}

MCD_EXPORT bool MCD_ModInit(void) {
    MCD_Config_Load(&g_config, "configs/speed_hack.ini");
    g_mod_info.is_active = MCD_Config_GetBool(&g_config, "enabled", true);
    g_mod_info.hotkey = MCD_Config_GetInt(&g_config, "hotkey_vk", 0x74);
    g_speed_multiplier = MCD_Config_GetFloat(&g_config, "speed_multiplier", 2.5f);
    g_roll_multiplier = MCD_Config_GetFloat(&g_config, "roll_multiplier", 2.0f);

    g_speed_addr = MCD_FindPattern("Dungeons-Win64-Shipping.exe", "\xF3\x0F\x59\x83\x90\x02\x00\x00", "xxxxxxxx");
    if (g_speed_addr) {
        memcpy(g_orig_bytes, (void*)g_speed_addr, sizeof(g_orig_bytes));
        g_patched = true;
    }
    return true;
}

MCD_EXPORT void MCD_ModShutdown(void) {
    if (g_patched && g_speed_addr) {
        MCD_PatchMemory((void*)g_speed_addr, g_orig_bytes, sizeof(g_orig_bytes));
        g_patched = false;
    }
}

MCD_EXPORT void MCD_ModUpdate(float delta_time) {
    (void)delta_time;
}

MCD_EXPORT bool MCD_ToggleMod(bool enable) {
    g_mod_info.is_active = enable;
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
