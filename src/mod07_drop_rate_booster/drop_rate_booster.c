#include "mcd_mod_sdk.h"
#include "mcd_config.h"
#include <stdio.h>

static MCD_ModInfo g_mod_info = {
    .id = "mcd_drop_rate_booster",
    .name = "Drop Rate & Rarity Booster",
    .version = "1.0.0",
    .author = "MCD Modding Team",
    .description = "Forces 100% Unique and Gilded item drop rates from chests, mobs, and mission end rewards.",
    .category = "Loot / Drops",
    .is_active = true,
    .hotkey = 0x76 /* VK_F7 */
};

static MCD_Config g_config;
static float g_unique_rate = 1.0f;
static float g_gilded_rate = 0.5f;
static bool g_always_max_slots = true;

MCD_EXPORT const MCD_ModInfo* MCD_GetModInfo(void) {
    return &g_mod_info;
}

MCD_EXPORT float MCD_GetUniqueDropRate(void) {
    return g_mod_info.is_active ? g_unique_rate : 0.05f;
}

MCD_EXPORT float MCD_GetGildedDropRate(void) {
    return g_mod_info.is_active ? g_gilded_rate : 0.02f;
}

MCD_EXPORT bool MCD_IsAlwaysMaxSlots(void) {
    return g_mod_info.is_active && g_always_max_slots;
}

MCD_EXPORT bool MCD_ModInit(void) {
    MCD_Config_Load(&g_config, "configs/drop_rate_booster.ini");
    g_mod_info.is_active = MCD_Config_GetBool(&g_config, "enabled", true);
    g_mod_info.hotkey = MCD_Config_GetInt(&g_config, "hotkey_vk", 0x76);
    g_unique_rate = MCD_Config_GetFloat(&g_config, "unique_drop_rate", 1.0f);
    g_gilded_rate = MCD_Config_GetFloat(&g_config, "gilded_drop_rate", 0.5f);
    g_always_max_slots = MCD_Config_GetBool(&g_config, "always_max_slots", true);
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
