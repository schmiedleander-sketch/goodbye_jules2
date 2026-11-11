#include "mcd_mod_sdk.h"
#include "mcd_config.h"
#include <stdio.h>

static MCD_ModInfo g_mod_info = {
    .id = "mcd_sound_visual_notifier",
    .name = "Secret & Chest ESP Notifier",
    .version = "1.0.0",
    .author = "MCD Modding Team",
    .description = "Displays visual outline markers and plays chime cues near secret chests, runes, and pigs.",
    .category = "Exploration / ESP",
    .is_active = true,
    .hotkey = 0x56 /* VK_V */
};

static MCD_Config g_config;
static float g_detection_radius = 4000.0f;
static bool g_highlight_chests = true;
static bool g_highlight_secrets = true;
static bool g_play_audio_cue = true;

MCD_EXPORT const MCD_ModInfo* MCD_GetModInfo(void) {
    return &g_mod_info;
}

MCD_EXPORT float MCD_GetDetectionRadius(void) {
    return g_mod_info.is_active ? g_detection_radius : 0.0f;
}

MCD_EXPORT bool MCD_ShouldHighlightChests(void) {
    return g_mod_info.is_active && g_highlight_chests;
}

MCD_EXPORT bool MCD_ShouldHighlightSecrets(void) {
    return g_mod_info.is_active && g_highlight_secrets;
}

MCD_EXPORT bool MCD_ShouldPlayAudioCue(void) {
    return g_mod_info.is_active && g_play_audio_cue;
}

MCD_EXPORT bool MCD_ModInit(void) {
    MCD_Config_Load(&g_config, "configs/sound_visual_notifier.ini");
    g_mod_info.is_active = MCD_Config_GetBool(&g_config, "enabled", true);
    g_mod_info.hotkey = MCD_Config_GetInt(&g_config, "hotkey_vk", 0x56);
    g_detection_radius = MCD_Config_GetFloat(&g_config, "detection_radius", 4000.0f);
    g_highlight_chests = MCD_Config_GetBool(&g_config, "highlight_chests", true);
    g_highlight_secrets = MCD_Config_GetBool(&g_config, "highlight_secrets", true);
    g_play_audio_cue = MCD_Config_GetBool(&g_config, "play_audio_cue", true);
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
