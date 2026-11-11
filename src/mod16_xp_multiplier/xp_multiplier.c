#include "mcd_mod_sdk.h"
#include "mcd_config.h"
#include <stdio.h>

static MCD_ModInfo g_mod_info = {
    .id = "mcd_xp_multiplier",
    .name = "Experience & Leveling Multiplier",
    .version = "1.0.0",
    .author = "MCD Modding Team",
    .description = "Accelerates character progression with configurable XP boost multipliers (default: 5x).",
    .category = "Progression / XP",
    .is_active = true,
    .hotkey = 0x58 /* VK_X */
};

static MCD_Config g_config;
static float g_xp_multiplier = 5.0f;

MCD_EXPORT const MCD_ModInfo* MCD_GetModInfo(void) {
    return &g_mod_info;
}

MCD_EXPORT float MCD_GetXpMultiplier(void) {
    return g_mod_info.is_active ? g_xp_multiplier : 1.0f;
}

MCD_EXPORT int MCD_CalculateXpGain(int base_xp) {
    if (!g_mod_info.is_active) return base_xp;
    return (int)(base_xp * g_xp_multiplier);
}

MCD_EXPORT bool MCD_ModInit(void) {
    MCD_Config_Load(&g_config, "configs/xp_multiplier.ini");
    g_mod_info.is_active = MCD_Config_GetBool(&g_config, "enabled", true);
    g_mod_info.hotkey = MCD_Config_GetInt(&g_config, "hotkey_vk", 0x58);
    g_xp_multiplier = MCD_Config_GetFloat(&g_config, "xp_multiplier", 5.0f);
    return true;
}

MCD_EXPORT void MCD_ModShutdown(void) {
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
