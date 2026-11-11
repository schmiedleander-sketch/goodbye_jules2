/**
 * Mod 15: Custom Loot Filter
 * Color-coded ground beam highlights and auto-vacuum for high-tier loot.
 */
#include "../../include/mcd2_mod_sdk.h"

DECLARE_MCD2_MOD(
    "mcd2_custom_loot_filter",
    "Custom Loot Filter & Beam Highlighter",
    "2.0.0",
    "MCD2Modder",
    "Configurable ground item beams, audio pings for uniques, and proximity vacuum."
)

typedef struct {
    bool highlight_uniques;
    bool highlight_gilded;
    bool auto_pickup_emeralds;
    float pickup_radius;
} MCD2_LootFilterConfig;

static MCD2_LootFilterConfig g_FilterConfig = {
    .highlight_uniques = true,
    .highlight_gilded = true,
    .auto_pickup_emeralds = true,
    .pickup_radius = 500.0f
};

MCD2_API MCD2_Result MCD2_ModInit(void) {
    return MCD2_SUCCESS;
}

MCD2_API void MCD2_ModShutdown(void) {
}

MCD2_API bool MCD2_ShouldHighlightItem(const MCD2_LootEvent* loot) {
    if (!loot) return false;
    if (loot->rarity >= 2) return true; // Unique or higher
    return false;
}

MCD2_API const MCD2_LootFilterConfig* MCD2_GetLootFilterConfig(void) {
    return &g_FilterConfig;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    (void)hinstDLL; (void)lpvReserved; (void)fdwReason;
    return TRUE;
}
