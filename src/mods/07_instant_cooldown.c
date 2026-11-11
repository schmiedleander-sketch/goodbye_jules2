/**
 * Mod 07: Instant Cooldown
 * Eliminates cooldowns for artifacts, potion flasks, and class abilities.
 */
#include "../../include/mcd2_mod_sdk.h"

DECLARE_MCD2_MOD(
    "mcd2_instant_cooldown",
    "Instant Artifact & Potion Cooldown",
    "2.0.0",
    "MCD2Modder",
    "Zero artifact recovery delay and instant healing potion replenishment."
)

typedef struct {
    float artifact_slot_cd[3];
    float potion_cd;
} MCD2_CooldownState;

static MCD2_CooldownState g_CD = {0};

MCD2_API MCD2_Result MCD2_ModInit(void) {
    return MCD2_SUCCESS;
}

MCD2_API void MCD2_ModShutdown(void) {
}

MCD2_API void MCD2_OnCooldownUpdate(MCD2_CooldownState* cd) {
    if (!cd) return;
    cd->artifact_slot_cd[0] = 0.0f;
    cd->artifact_slot_cd[1] = 0.0f;
    cd->artifact_slot_cd[2] = 0.0f;
    cd->potion_cd = 0.0f;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    (void)hinstDLL; (void)lpvReserved; (void)fdwReason;
    return TRUE;
}
