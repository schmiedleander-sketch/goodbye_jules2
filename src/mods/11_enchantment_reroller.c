/**
 * Mod 11: Free Enchantment Reroller
 * Removes gold cost from the Enchantsmith and guarantees maximum tier 3 rolls.
 */
#include "../../include/mcd2_mod_sdk.h"

DECLARE_MCD2_MOD(
    "mcd2_enchantment_reroller",
    "Free Enchantment Reroller",
    "2.0.0",
    "MCD2Modder",
    "Zero gold cost at the Enchantsmith village merchant and guarantees Tier 3 rolls."
)

typedef struct {
    uint32_t slot_index;
    int32_t gold_cost;
    int32_t guaranteed_tier;
} MCD2_RerollContext;

MCD2_API MCD2_Result MCD2_ModInit(void) {
    return MCD2_SUCCESS;
}

MCD2_API void MCD2_ModShutdown(void) {
}

MCD2_API void MCD2_OnEnchantsmithReroll(MCD2_RerollContext* ctx) {
    if (!ctx) return;
    ctx->gold_cost = 0;
    ctx->guaranteed_tier = 3; // Maximum enchantment tier
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    (void)hinstDLL; (void)lpvReserved; (void)fdwReason;
    return TRUE;
}
