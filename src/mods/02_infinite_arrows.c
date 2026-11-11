/**
 * Mod 02: Infinite Arrows
 * Keeps arrow quiver topped up and bypasses ammo decrement routines.
 */
#include "../../include/mcd2_mod_sdk.h"

DECLARE_MCD2_MOD(
    "mcd2_infinite_arrows",
    "Infinite Arrows & Quiver Refill",
    "2.0.0",
    "MCD2Modder",
    "Infinite quiver capacity, never runs out of arrows or special ammunition."
)

static bool g_Enabled = true;

MCD2_API MCD2_Result MCD2_ModInit(void) {
    g_Enabled = true;
    return MCD2_SUCCESS;
}

MCD2_API void MCD2_ModShutdown(void) {
    g_Enabled = false;
}

MCD2_API void MCD2_OnGameTick(float delta_time, MCD2_PlayerState* player) {
    if (!g_Enabled || !player) return;
    (void)delta_time;
    if (player->arrows < 999) {
        player->arrows = 999;
    }
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    (void)hinstDLL; (void)lpvReserved;
    if (fdwReason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hinstDLL);
        MCD2_ModInit();
    } else if (fdwReason == DLL_PROCESS_DETACH) {
        MCD2_ModShutdown();
    }
    return TRUE;
}
