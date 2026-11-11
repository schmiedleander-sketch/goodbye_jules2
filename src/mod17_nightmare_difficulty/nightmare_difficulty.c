#include "mcd_mod_sdk.h"
#include "mcd_config.h"
#include <stdio.h>

static MCD_ModInfo g_mod_info = {
    .id = "mcd_nightmare_difficulty",
    .name = "Nightmare Difficulty Modifier",
    .version = "1.0.0",
    .author = "MCD Modding Team",
    .description = "Ultra-hardcore mode: scales mob health, mob speed, elite spawn frequencies, and raid density.",
    .category = "Difficulty / Hardcore",
    .is_active = true,
    .hotkey = 0x4E /* VK_N */
};

static MCD_Config g_config;
static float g_mob_health_scale = 3.0f;
static float g_mob_damage_scale = 2.5f;
static float g_elite_spawn_chance = 0.60f;

MCD_EXPORT const MCD_ModInfo* MCD_GetModInfo(void) {
    return &g_mod_info;
}

MCD_EXPORT float MCD_GetMobHealthMultiplier(void) {
    return g_mod_info.is_active ? g_mob_health_scale : 1.0f;
}

MCD_EXPORT float MCD_GetMobDamageMultiplier(void) {
    return g_mod_info.is_active ? g_mob_damage_scale : 1.0f;
}

MCD_EXPORT float MCD_GetEliteSpawnChance(void) {
    return g_mod_info.is_active ? g_elite_spawn_chance : 0.15f;
}

MCD_EXPORT bool MCD_ModInit(void) {
    MCD_Config_Load(&g_config, "configs/nightmare_difficulty.ini");
    g_mod_info.is_active = MCD_Config_GetBool(&g_config, "enabled", true);
    g_mod_info.hotkey = MCD_Config_GetInt(&g_config, "hotkey_vk", 0x4E);
    g_mob_health_scale = MCD_Config_GetFloat(&g_config, "mob_health_scale", 3.0f);
    g_mob_damage_scale = MCD_Config_GetFloat(&g_config, "mob_damage_scale", 2.5f);
    g_elite_spawn_chance = MCD_Config_GetFloat(&g_config, "elite_spawn_chance", 0.60f);
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
