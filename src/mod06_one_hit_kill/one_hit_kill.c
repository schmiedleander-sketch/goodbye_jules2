#include "mcd_mod_sdk.h"
#include "mcd_config.h"
#include <stdio.h>

static MCD_ModInfo g_mod_info = {
    .id = "mcd_one_hit_kill",
    .name = "One Hit Kill & Super Damage",
    .version = "1.0.0",
    .author = "MCD Modding Team",
    .description = "Deals massive critical damage to hostile mobs and bosses instantly defeating them in one strike.",
    .category = "Combat / Cheat",
    .is_active = true,
    .hotkey = 0x75 /* VK_F6 */
};

static MCD_Config g_config;
static float g_damage_multiplier = 999999.0f;
static uintptr_t g_dmg_calc_addr = 0;
static uint8_t g_orig_bytes[8];
static bool g_hooked = false;

MCD_EXPORT const MCD_ModInfo* MCD_GetModInfo(void) {
    return &g_mod_info;
}

MCD_EXPORT float MCD_GetDamageMultiplier(void) {
    return g_mod_info.is_active ? g_damage_multiplier : 1.0f;
}

MCD_EXPORT bool MCD_ModInit(void) {
    MCD_Config_Load(&g_config, "configs/one_hit_kill.ini");
    g_mod_info.is_active = MCD_Config_GetBool(&g_config, "enabled", true);
    g_mod_info.hotkey = MCD_Config_GetInt(&g_config, "hotkey_vk", 0x75);
    g_damage_multiplier = MCD_Config_GetFloat(&g_config, "damage_multiplier", 999999.0f);

    g_dmg_calc_addr = MCD_FindPattern("Dungeons-Win64-Shipping.exe", "\xF3\x0F\x59\x44\x24\x40\xF3\x0F", "xxxxxxxx");
    if (g_dmg_calc_addr) {
        memcpy(g_orig_bytes, (void*)g_dmg_calc_addr, sizeof(g_orig_bytes));
        g_hooked = true;
    }
    return true;
}

MCD_EXPORT void MCD_ModShutdown(void) {
    if (g_hooked && g_dmg_calc_addr) {
        MCD_PatchMemory((void*)g_dmg_calc_addr, g_orig_bytes, sizeof(g_orig_bytes));
        g_hooked = false;
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
