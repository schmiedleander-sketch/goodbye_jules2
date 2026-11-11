/**
 * Mod 08: Auto-Salvage
 * Automatically salvages common and uncommon junk loot into emeralds.
 */
#include "../../include/mcd2_mod_sdk.h"

DECLARE_MCD2_MOD(
    "mcd2_auto_salvage",
    "Smart Auto-Salvage Utility",
    "2.0.0",
    "MCD2Modder",
    "Automatically disassembles non-unique low-tier items directly into emerald currency."
)

static int32_t g_MinRarityToKeep = 2; // Keep Rare and Unique

MCD2_API MCD2_Result MCD2_ModInit(void) {
    return MCD2_SUCCESS;
}

MCD2_API void MCD2_ModShutdown(void) {
}

MCD2_API void MCD2_OnLootDrop(MCD2_LootEvent* loot) {
    if (!loot) return;
    if (loot->rarity < g_MinRarityToKeep) {
        loot->should_salvage = true;
    }
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    (void)hinstDLL; (void)lpvReserved; (void)fdwReason;
    return TRUE;
}
