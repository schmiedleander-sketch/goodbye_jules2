/**
 * Mod 13: No Clip Ghost
 * Disables world collision meshes and allows phase traversing through barriers and gates.
 */
#include "../../include/mcd2_mod_sdk.h"

DECLARE_MCD2_MOD(
    "mcd2_no_clip_ghost",
    "Ghost Walk & No Clip",
    "2.0.0",
    "MCD2Modder",
    "Toggles collision volume checks, enabling phase traversal through doors, walls, and gates."
)

static bool g_NoClipActive = true;

MCD2_API MCD2_Result MCD2_ModInit(void) {
    g_NoClipActive = true;
    return MCD2_SUCCESS;
}

MCD2_API void MCD2_ModShutdown(void) {
    g_NoClipActive = false;
}

MCD2_API void MCD2_OnGameTick(float delta_time, MCD2_PlayerState* player) {
    if (!player) return;
    (void)delta_time;
    player->no_clip = g_NoClipActive;
}

MCD2_API void MCD2_ToggleNoClip(void) {
    g_NoClipActive = !g_NoClipActive;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    (void)hinstDLL; (void)lpvReserved; (void)fdwReason;
    return TRUE;
}
