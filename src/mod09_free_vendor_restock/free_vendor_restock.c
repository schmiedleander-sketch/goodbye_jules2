#include "mcd_mod_sdk.h"
#include "mcd_config.h"
#include <stdio.h>

static MCD_ModInfo g_mod_info = {
    .id = "mcd_free_vendor_restock",
    .name = "Free Vendor Restock & Instant Blacksmith",
    .version = "1.0.0",
    .author = "MCD Modding Team",
    .description = "Vendors restock items for 0 emeralds/gold, and Blacksmith completes gear upgrades in 0 missions.",
    .category = "Camp / Vendors",
    .is_active = true,
    .hotkey = 0x78 /* VK_F9 */
};

static MCD_Config g_config;
static bool g_instant_blacksmith = true;
static int g_restock_cost = 0;

MCD_EXPORT const MCD_ModInfo* MCD_GetModInfo(void) {
    return &g_mod_info;
}

MCD_EXPORT int MCD_GetRestockCost(int default_cost) {
    if (!g_mod_info.is_active) return default_cost;
    return g_restock_cost;
}

MCD_EXPORT int MCD_GetBlacksmithRequiredMissions(int default_missions) {
    if (!g_mod_info.is_active || !g_instant_blacksmith) return default_missions;
    return 0;
}

MCD_EXPORT bool MCD_ModInit(void) {
    MCD_Config_Load(&g_config, "configs/free_vendor_restock.ini");
    g_mod_info.is_active = MCD_Config_GetBool(&g_config, "enabled", true);
    g_mod_info.hotkey = MCD_Config_GetInt(&g_config, "hotkey_vk", 0x78);
    g_instant_blacksmith = MCD_Config_GetBool(&g_config, "instant_blacksmith", true);
    g_restock_cost = MCD_Config_GetInt(&g_config, "restock_cost", 0);
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
