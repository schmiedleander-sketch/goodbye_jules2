/**
 * Mod 14: Boss Health Bar & Phase HUD
 * Detailed boss health percentages, phases, and shield breakdown overlay metrics.
 */
#include "../../include/mcd2_mod_sdk.h"

DECLARE_MCD2_MOD(
    "mcd2_boss_health_bar",
    "Boss Health Bar & Phase Overlay",
    "2.0.0",
    "MCD2Modder",
    "Numeric HP meters, damage intake rate, and invulnerability phase countdowns."
)

typedef struct {
    uint64_t boss_id;
    char boss_name[64];
    float current_health;
    float max_health;
    int32_t current_phase;
    bool is_invulnerable_phase;
} MCD2_BossHUDInfo;

static MCD2_BossHUDInfo g_ActiveBoss = {0};

MCD2_API MCD2_Result MCD2_ModInit(void) {
    return MCD2_SUCCESS;
}

MCD2_API void MCD2_ModShutdown(void) {
}

MCD2_API void MCD2_UpdateBossStatus(uint64_t id, const char* name, float hp, float max_hp, int32_t phase) {
    g_ActiveBoss.boss_id = id;
    if (name) snprintf(g_ActiveBoss.boss_name, sizeof(g_ActiveBoss.boss_name), "%s", name);
    g_ActiveBoss.current_health = hp;
    g_ActiveBoss.max_health = max_hp;
    g_ActiveBoss.current_phase = phase;
}

MCD2_API const MCD2_BossHUDInfo* MCD2_GetBossHUDInfo(void) {
    return &g_ActiveBoss;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    (void)hinstDLL; (void)lpvReserved; (void)fdwReason;
    return TRUE;
}
