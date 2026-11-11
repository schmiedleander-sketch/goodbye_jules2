/**
 * Mod 12: XP Booster
 * Accelerates character progression and adventure pass / seasonal experience gains.
 */
#include "../../include/mcd2_mod_sdk.h"

DECLARE_MCD2_MOD(
    "mcd2_xp_booster",
    "XP & Leveling Progression Booster",
    "2.0.0",
    "MCD2Modder",
    "Multiplies character leveling and adventure pass XP gains by 5x."
)

static float g_XPMultiplier = 5.0f;

MCD2_API MCD2_Result MCD2_ModInit(void) {
    return MCD2_SUCCESS;
}

MCD2_API void MCD2_ModShutdown(void) {
}

MCD2_API int32_t MCD2_CalculateXPGain(int32_t base_xp) {
    return (int32_t)(base_xp * g_XPMultiplier);
}

MCD2_API void MCD2_SetXPMultiplier(float mult) {
    if (mult > 0.0f) g_XPMultiplier = mult;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    (void)hinstDLL; (void)lpvReserved; (void)fdwReason;
    return TRUE;
}
