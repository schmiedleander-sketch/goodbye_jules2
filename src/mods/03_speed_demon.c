/**
 * Mod 03: Speed Demon
 * Boosts player movement speed, sprint burst, and melee/ranged attack speed.
 */
#include "../../include/mcd2_mod_sdk.h"

DECLARE_MCD2_MOD(
    "mcd2_speed_demon",
    "Speed Demon Overdrive",
    "2.0.0",
    "MCD2Modder",
    "Doubles movement velocity and triples attack action speeds."
)

static float g_SpeedMult = 2.25f;
static float g_AttackMult = 2.50f;

MCD2_API MCD2_Result MCD2_ModInit(void) {
    return MCD2_SUCCESS;
}

MCD2_API void MCD2_ModShutdown(void) {
}

MCD2_API void MCD2_OnGameTick(float delta_time, MCD2_PlayerState* player) {
    if (!player) return;
    (void)delta_time;
    player->movement_speed_mult = g_SpeedMult;
    player->attack_speed_mult = g_AttackMult;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    (void)hinstDLL; (void)lpvReserved;
    if (fdwReason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hinstDLL);
        MCD2_ModInit();
    }
    return TRUE;
}
