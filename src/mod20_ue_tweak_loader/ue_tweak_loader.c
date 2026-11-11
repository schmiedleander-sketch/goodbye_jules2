#include "mcd_mod_sdk.h"
#include "mcd_config.h"
#include <stdio.h>
#include <string.h>

static MCD_ModInfo g_mod_info = {
    .id = "mcd_ue_tweak_loader",
    .name = "UE Engine Tweak & Master Mod Loader",
    .version = "1.0.0",
    .author = "MCD Modding Team",
    .description = "Central engine orchestrator: unlocks 144+ FPS caps, disables chromatic aberration/motion blur, and manages mod configs.",
    .category = "System / Engine Loader",
    .is_active = true,
    .hotkey = 0x75 /* VK_F6 / Config Reload */
};

typedef struct {
    char mod_names[20][64];
    bool mod_enabled[20];
    size_t count;
} ModRegistry;

static MCD_Config g_config;
static ModRegistry g_registry;
static int g_target_max_fps = 0; /* 0 = unlocked */
static bool g_disable_motion_blur = true;
static bool g_disable_vignette = true;

MCD_EXPORT const MCD_ModInfo* MCD_GetModInfo(void) {
    return &g_mod_info;
}

MCD_EXPORT int MCD_GetTargetFPS(void) {
    return g_mod_info.is_active ? g_target_max_fps : 60;
}

MCD_EXPORT bool MCD_IsMotionBlurDisabled(void) {
    return g_mod_info.is_active && g_disable_motion_blur;
}

MCD_EXPORT bool MCD_IsVignetteDisabled(void) {
    return g_mod_info.is_active && g_disable_vignette;
}

MCD_EXPORT size_t MCD_GetLoadedModCount(void) {
    return g_registry.count;
}

MCD_EXPORT bool MCD_RegisterMod(const char* mod_name, bool enabled) {
    if (g_registry.count >= 20 || !mod_name) return false;
    strncpy(g_registry.mod_names[g_registry.count], mod_name, sizeof(g_registry.mod_names[0]) - 1);
    g_registry.mod_enabled[g_registry.count] = enabled;
    g_registry.count++;
    return true;
}

MCD_EXPORT bool MCD_ModInit(void) {
    MCD_Config_Load(&g_config, "configs/ue_tweak_loader.ini");
    g_mod_info.is_active = MCD_Config_GetBool(&g_config, "enabled", true);
    g_target_max_fps = MCD_Config_GetInt(&g_config, "target_fps", 0);
    g_disable_motion_blur = MCD_Config_GetBool(&g_config, "disable_motion_blur", true);
    g_disable_vignette = MCD_Config_GetBool(&g_config, "disable_vignette", true);

    g_registry.count = 0;
    MCD_RegisterMod("mcd_godmode", true);
    MCD_RegisterMod("mcd_emerald_gold_multiplier", true);
    MCD_RegisterMod("mcd_unlimited_arrows", true);
    MCD_RegisterMod("mcd_artifact_cooldown", true);
    MCD_RegisterMod("mcd_speed_hack", true);
    MCD_RegisterMod("mcd_one_hit_kill", true);
    MCD_RegisterMod("mcd_drop_rate_booster", true);
    MCD_RegisterMod("mcd_free_enchantment", true);
    MCD_RegisterMod("mcd_free_vendor_restock", true);
    MCD_RegisterMod("mcd_fov_camera_unlocker", true);
    MCD_RegisterMod("mcd_mob_freeze_aura", true);
    MCD_RegisterMod("mcd_auto_loot_collector", true);
    MCD_RegisterMod("mcd_dev_console_unlocker", true);
    MCD_RegisterMod("mcd_skip_mission_timer", true);
    MCD_RegisterMod("mcd_custom_item_spawner", true);
    MCD_RegisterMod("mcd_xp_multiplier", true);
    MCD_RegisterMod("mcd_nightmare_difficulty", true);
    MCD_RegisterMod("mcd_sound_visual_notifier", true);
    MCD_RegisterMod("mcd_no_roll_cooldown", true);
    MCD_RegisterMod("mcd_ue_tweak_loader", true);

    return true;
}

MCD_EXPORT void MCD_ModShutdown(void) {
    g_registry.count = 0;
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
