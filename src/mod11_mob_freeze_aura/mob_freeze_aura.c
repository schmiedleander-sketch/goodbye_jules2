#include "mcd_mod_sdk.h"
#include "mcd_config.h"
#include <stdio.h>

static MCD_ModInfo g_mod_info = {
    .id = "mcd_mob_freeze_aura",
    .name = "Mob Freeze & AI Stun Aura",
    .version = "1.0.0",
    .author = "MCD Modding Team",
    .description = "Creates a passive aura around player that paralyzes and freezes mob AI in range.",
    .category = "Combat / Defense",
    .is_active = true,
    .hotkey = 0x7A /* VK_F11 */
};

static MCD_Config g_config;
static float g_freeze_radius = 1500.0f;
static bool g_freeze_bosses = false;

MCD_EXPORT const MCD_ModInfo* MCD_GetModInfo(void) {
    return &g_mod_info;
}

MCD_EXPORT float MCD_GetFreezeRadius(void) {
    return g_mod_info.is_active ? g_freeze_radius : 0.0f;
}

MCD_EXPORT bool MCD_ShouldFreezeBosses(void) {
    return g_mod_info.is_active && g_freeze_bosses;
}

MCD_EXPORT bool MCD_ModInit(void) {
    MCD_Config_Load(&g_config, "configs/mob_freeze_aura.ini");
    g_mod_info.is_active = MCD_Config_GetBool(&g_config, "enabled", true);
    g_mod_info.hotkey = MCD_Config_GetInt(&g_config, "hotkey_vk", 0x7A);
    g_freeze_radius = MCD_Config_GetFloat(&g_config, "freeze_radius", 1500.0f);
    g_freeze_bosses = MCD_Config_GetBool(&g_config, "freeze_bosses", false);
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
