/**
 * Mod 01: God Mode
 * Makes player invulnerable to physical, magic, explosion, and void damage.
 * Auto-refills emergency shield and health every game tick.
 */
#include "../../include/mcd2_mod_sdk.h"

DECLARE_MCD2_MOD(
    "mcd2_god_mode",
    "God Mode & Emergency Aegis",
    "2.0.0",
    "MCD2Modder",
    "Grants invulnerability, permanent health shield, and nullifies fatal damage."
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
    player->is_invulnerable = true;
    if (player->health < player->max_health) {
        player->health = player->max_health;
    }
    if (player->shield < player->max_shield) {
        player->shield = player->max_shield;
    }
}

MCD2_API void MCD2_OnDamageCalculated(MCD2_DamageEvent* dmg) {
    if (!g_Enabled || !dmg) return;
    if (dmg->target_id == 0) { // Player target
        dmg->modified_damage = 0.0f;
    }
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    (void)hinstDLL; (void)lpvReserved;
    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hinstDLL);
            MCD2_ModInit();
            break;
        case DLL_PROCESS_DETACH:
            MCD2_ModShutdown();
            break;
    }
    return TRUE;
}
