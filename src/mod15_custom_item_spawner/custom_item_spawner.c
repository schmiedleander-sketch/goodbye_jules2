#include "mcd_mod_sdk.h"
#include "mcd_config.h"
#include <stdio.h>
#include <string.h>

static MCD_ModInfo g_mod_info = {
    .id = "mcd_custom_item_spawner",
    .name = "Custom Item & Gear Spawner",
    .version = "1.0.0",
    .author = "MCD Modding Team",
    .description = "Injects any weapon, armor, or artifact with customizable power level, gilded rarity, and enchantments.",
    .category = "Items / Inventory",
    .is_active = true,
    .hotkey = 0x49 /* VK_I */
};

typedef struct {
    char item_id[64];
    int power_level;
    int rarity; /* 0=Common, 1=Rare, 2=Unique, 3=Gilded */
    int enchantment_slots;
} SpawnRequest;

static MCD_Config g_config;
static SpawnRequest g_last_request;

MCD_EXPORT const MCD_ModInfo* MCD_GetModInfo(void) {
    return &g_mod_info;
}

MCD_EXPORT bool MCD_SpawnItem(const char* item_id, int power_level, int rarity) {
    if (!g_mod_info.is_active || !item_id) return false;
    strncpy(g_last_request.item_id, item_id, sizeof(g_last_request.item_id) - 1);
    g_last_request.power_level = power_level;
    g_last_request.rarity = rarity;
    g_last_request.enchantment_slots = 3;
    return true;
}

MCD_EXPORT const SpawnRequest* MCD_GetLastSpawnRequest(void) {
    return &g_last_request;
}

MCD_EXPORT bool MCD_ModInit(void) {
    MCD_Config_Load(&g_config, "configs/custom_item_spawner.ini");
    g_mod_info.is_active = MCD_Config_GetBool(&g_config, "enabled", true);
    g_mod_info.hotkey = MCD_Config_GetInt(&g_config, "hotkey_vk", 0x49);
    strncpy(g_last_request.item_id, MCD_Config_GetString(&g_config, "default_item", "FighterBindings"), sizeof(g_last_request.item_id) - 1);
    g_last_request.power_level = MCD_Config_GetInt(&g_config, "default_power", 263);
    g_last_request.rarity = MCD_Config_GetInt(&g_config, "default_rarity", 3);
    g_last_request.enchantment_slots = 3;
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
