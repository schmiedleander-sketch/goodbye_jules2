/**
 * Mod 19: Infinite Lives
 * Prevents player defeat counter / Night Beacon decrement on death.
 */
#include "../../include/mcd2_mod_sdk.h"

DECLARE_MCD2_MOD(
    "mcd2_infinite_lives",
    "Infinite Lives & Defeat Immunity",
    "2.0.0",
    "MCD2Modder",
    "Locks remaining team lives to maximum, completely eliminating 'Night is Falling' game-overs."
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
    if (player->lives_remaining < 4) {
        player->lives_remaining = 4;
    }
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    (void)hinstDLL; (void)lpvReserved; (void)fdwReason;
    return TRUE;
}
