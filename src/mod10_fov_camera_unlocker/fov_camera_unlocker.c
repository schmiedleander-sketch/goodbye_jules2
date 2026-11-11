#include "mcd_mod_sdk.h"
#include "mcd_config.h"
#include <stdio.h>

static MCD_ModInfo g_mod_info = {
    .id = "mcd_fov_camera_unlocker",
    .name = "FOV & Camera Distance Unlocker",
    .version = "1.0.0",
    .author = "MCD Modding Team",
    .description = "Custom field-of-view (FOV), camera distance, pitch angle, and isometric zoom override.",
    .category = "Camera / Visual",
    .is_active = true,
    .hotkey = 0x79 /* VK_F10 */
};

static MCD_Config g_config;
static float g_target_fov = 95.0f;
static float g_camera_distance = 1800.0f;
static float g_camera_pitch = -55.0f;

MCD_EXPORT const MCD_ModInfo* MCD_GetModInfo(void) {
    return &g_mod_info;
}

MCD_EXPORT float MCD_GetCameraFOV(void) {
    return g_mod_info.is_active ? g_target_fov : 70.0f;
}

MCD_EXPORT float MCD_GetCameraDistance(void) {
    return g_mod_info.is_active ? g_camera_distance : 1200.0f;
}

MCD_EXPORT float MCD_GetCameraPitch(void) {
    return g_mod_info.is_active ? g_camera_pitch : -60.0f;
}

MCD_EXPORT bool MCD_ModInit(void) {
    MCD_Config_Load(&g_config, "configs/fov_camera_unlocker.ini");
    g_mod_info.is_active = MCD_Config_GetBool(&g_config, "enabled", true);
    g_mod_info.hotkey = MCD_Config_GetInt(&g_config, "hotkey_vk", 0x79);
    g_target_fov = MCD_Config_GetFloat(&g_config, "fov", 95.0f);
    g_camera_distance = MCD_Config_GetFloat(&g_config, "camera_distance", 1800.0f);
    g_camera_pitch = MCD_Config_GetFloat(&g_config, "camera_pitch", -55.0f);
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
