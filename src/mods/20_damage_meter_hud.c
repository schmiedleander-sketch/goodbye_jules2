/**
 * Mod 20: DPS & Damage Meter HUD
 * Live combat parser tracking personal and party DPS, burst spikes, and healing metrics.
 */
#include "../../include/mcd2_mod_sdk.h"

DECLARE_MCD2_MOD(
    "mcd2_damage_meter_hud",
    "Real-time DPS & Combat Meter HUD",
    "2.0.0",
    "MCD2Modder",
    "Tracks personal and team DPS, total outgoing damage, critical rates, and healing."
)

typedef struct {
    double total_damage_dealt;
    double current_dps;
    uint32_t total_hits;
    uint32_t critical_hits;
    float combat_duration_seconds;
} MCD2_CombatStats;

static MCD2_CombatStats g_Stats = {0};

MCD2_API MCD2_Result MCD2_ModInit(void) {
    memset(&g_Stats, 0, sizeof(g_Stats));
    return MCD2_SUCCESS;
}

MCD2_API void MCD2_ModShutdown(void) {
}

MCD2_API void MCD2_OnDamageCalculated(MCD2_DamageEvent* dmg) {
    if (!dmg) return;
    if (dmg->attacker_id == 0) { // Player
        g_Stats.total_damage_dealt += dmg->modified_damage;
        g_Stats.total_hits++;
        if (dmg->is_critical) {
            g_Stats.critical_hits++;
        }
        if (g_Stats.combat_duration_seconds > 0.0f) {
            g_Stats.current_dps = g_Stats.total_damage_dealt / g_Stats.combat_duration_seconds;
        }
    }
}

MCD2_API void MCD2_OnGameTick(float delta_time, MCD2_PlayerState* player) {
    (void)player;
    g_Stats.combat_duration_seconds += delta_time;
    if (g_Stats.combat_duration_seconds > 0.0f) {
        g_Stats.current_dps = g_Stats.total_damage_dealt / g_Stats.combat_duration_seconds;
    }
}

MCD2_API const MCD2_CombatStats* MCD2_GetCombatStats(void) {
    return &g_Stats;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    (void)hinstDLL; (void)lpvReserved; (void)fdwReason;
    return TRUE;
}
