/**
 * Mod 05: Custom FOV & Camera
 * Unlocks isometric camera restriction, allowing custom FOV, pitch, free orbit, and zoom distance.
 */
#include "../../include/mcd2_mod_sdk.h"

DECLARE_MCD2_MOD(
    "mcd2_custom_fov_camera",
    "Enhanced Camera & Custom FOV",
    "2.0.0",
    "MCD2Modder",
    "Unlocks field-of-view, zoom limits, and provides free-look cinematic perspective."
)

static MCD2_CameraState g_Cam = {
    .fov = 95.0f,
    .zoom_distance = 1800.0f,
    .pitch_angle = -55.0f,
    .yaw_angle = 45.0f,
    .height_offset = 250.0f,
    .free_cam_enabled = false
};

MCD2_API MCD2_Result MCD2_ModInit(void) {
    return MCD2_SUCCESS;
}

MCD2_API void MCD2_ModShutdown(void) {
}

MCD2_API MCD2_CameraState* MCD2_GetCameraState(void) {
    return &g_Cam;
}

MCD2_API void MCD2_SetCameraZoom(float zoom) {
    g_Cam.zoom_distance = zoom;
}

MCD2_API void MCD2_SetCameraFOV(float fov) {
    g_Cam.fov = fov;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    (void)hinstDLL; (void)lpvReserved; (void)fdwReason;
    return TRUE;
}
