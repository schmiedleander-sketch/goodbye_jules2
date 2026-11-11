/**
 * Mod 06: One-Hit Kill
 * Multiplies player attack output by 1,000,000x and bypasses mob damage resistance.
 */
#include "../../include/mcd2_mod_sdk.h"

DECLARE_MCD2_MOD(
    "mcd2_one_hit_kill",
    "One-Hit Kill & Armor Pierce",
    "2.0.0",
    "MCD2Modder",
    "Annihilates regular mobs and bosses in a single attack with true critical damage."
)

static bool g_Enabled = true;

MCD2_API MCD2_Result MCD2_ModInit(void) {
    g_Enabled = true;
    return MCD2_SUCCESS;
}

MCD2_API void MCD2_ModShutdown(void) {
    g_Enabled = false;
}

MCD2_API void MCD2_OnDamageCalculated(MCD2_DamageEvent* dmg) {
    if (!g_Enabled || !dmg) return;
    if (dmg->attacker_id == 0) { // Player is attacker
        dmg->modified_damage = 9999999.0f;
        dmg->is_critical = true;
    }
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    (void)hinstDLL; (void)lpvReserved; (void)fdwReason;
    return TRUE;
}
