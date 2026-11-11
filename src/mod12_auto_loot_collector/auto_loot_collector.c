#include "mcd_mod_sdk.h"
#include "mcd_config.h"
#include <stdio.h>

static MCD_ModInfo g_mod_info = {
    .id = "mcd_auto_loot_collector",
    .name = "Auto Loot Vacuum Collector",
    .version = "1.0.0",
    .author = "MCD Modding Team",
    .description = "Instantly vacuums dropped emeralds, gold, arrows, consumables, and gear items straight to player inventory.",
    .category = "Loot / Quality of Life",
    .is_active = true,
    .hotkey = 0x7B /* VK_F12 */
};

static MCD_Config g_config;
static float g_vacuum_radius = 5000.0f;
static bool g_loot_gear = true;
static bool g_loot_emeralds = true;
static bool g_loot_arrows = true;

MCD_EXPORT const MCD_ModInfo* MCD_GetModInfo(void) {
    return &g_mod_info;
}

MCD_EXPORT float MCD_GetVacuumRadius(void) {
    return g_mod_info.is_active ? g_vacuum_radius : 0.0f;
}

MCD_EXPORT bool MCD_ShouldLootGear(void) {
    return g_mod_info.is_active && g_loot_gear;
}

MCD_EXPORT bool MCD_ShouldLootEmeralds(void) {
    return g_mod_info.is_active && g_loot_emeralds;
}

MCD_EXPORT bool MCD_ShouldLootArrows(void) {
    return g_mod_info.is_active && g_loot_arrows;
}

MCD_EXPORT bool MCD_ModInit(void) {
    MCD_Config_Load(&g_config, "configs/auto_loot_collector.ini");
    g_mod_info.is_active = MCD_Config_GetBool(&g_config, "enabled", true);
    g_mod_info.hotkey = MCD_Config_GetInt(&g_config, "hotkey_vk", 0x7B);
    g_vacuum_radius = MCD_Config_GetFloat(&g_config, "vacuum_radius", 5000.0f);
    g_loot_gear = MCD_Config_GetBool(&g_config, "loot_gear", true);
    g_loot_emeralds = MCD_Config_GetBool(&g_config, "loot_emeralds", true);
    g_loot_arrows = MCD_Config_GetBool(&g_config, "loot_arrows", true);
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
