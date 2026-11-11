/**
 * Mod 04: Emerald Multiplier
 * Intercepts emerald and gold drops and multiplies value by configurable multiplier (default 10x).
 */
#include "../../include/mcd2_mod_sdk.h"

DECLARE_MCD2_MOD(
    "mcd2_emerald_multiplier",
    "Emerald & Gold Multiplier",
    "2.0.0",
    "MCD2Modder",
    "Multiplies all ground emerald drops and chest gold rewards by 10x."
)

static int32_t g_Multiplier = 10;

MCD2_API MCD2_Result MCD2_ModInit(void) {
    return MCD2_SUCCESS;
}

MCD2_API void MCD2_ModShutdown(void) {
}

MCD2_API void MCD2_OnLootDrop(MCD2_LootEvent* loot) {
    if (!loot) return;
    if (loot->emerald_value > 0) {
        loot->emerald_value *= g_Multiplier;
    }
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    (void)hinstDLL; (void)fdwReason; (void)lpvReserved;
    return TRUE;
}
