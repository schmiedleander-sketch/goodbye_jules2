#include "mcd_mod_sdk.h"
#include "mcd_config.h"
#include <stdio.h>

static MCD_ModInfo g_mod_info = {
    .id = "mcd_skip_mission_timer",
    .name = "Skip Mission & Ambush Timers",
    .version = "1.0.0",
    .author = "MCD Modding Team",
    .description = "Instantly clears arena defense timers, ambush survival clocks, and mission gate countdowns.",
    .category = "Missions / Progression",
    .is_active = true,
    .hotkey = 0x54 /* VK_T */
};

static MCD_Config g_config;
static bool g_auto_complete_ambushes = true;

MCD_EXPORT const MCD_ModInfo* MCD_GetModInfo(void) {
    return &g_mod_info;
}

MCD_EXPORT bool MCD_ShouldAutoCompleteAmbushes(void) {
    return g_mod_info.is_active && g_auto_complete_ambushes;
}

MCD_EXPORT float MCD_OverrideTimerValue(float current_timer) {
    if (!g_mod_info.is_active) return current_timer;
    return 0.0f;
}

MCD_EXPORT bool MCD_ModInit(void) {
    MCD_Config_Load(&g_config, "configs/skip_mission_timer.ini");
    g_mod_info.is_active = MCD_Config_GetBool(&g_config, "enabled", true);
    g_mod_info.hotkey = MCD_Config_GetInt(&g_config, "hotkey_vk", 0x54);
    g_auto_complete_ambushes = MCD_Config_GetBool(&g_config, "auto_complete_ambushes", true);
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
