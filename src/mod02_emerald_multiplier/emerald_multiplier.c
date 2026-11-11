#include "mcd_mod_sdk.h"
#include "mcd_config.h"
#include <stdio.h>

static MCD_ModInfo g_mod_info = {
    .id = "mcd_emerald_gold_multiplier",
    .name = "Emerald & Gold Multiplier",
    .version = "1.0.0",
    .author = "MCD Modding Team",
    .description = "Multiplies emerald and gold drops by a configurable factor (default: 10x).",
    .category = "Economy / Currency",
    .is_active = true,
    .hotkey = 0x71 /* VK_F2 */
};

static MCD_Config g_config;
static int g_emerald_mult = 10;
static int g_gold_mult = 5;
static uintptr_t g_currency_addr = 0;
static uint8_t g_original_code[6];
static bool g_hooked = false;

MCD_EXPORT const MCD_ModInfo* MCD_GetModInfo(void) {
    return &g_mod_info;
}

MCD_EXPORT int MCD_GetEmeraldMultiplier(void) {
    return g_mod_info.is_active ? g_emerald_mult : 1;
}

MCD_EXPORT int MCD_GetGoldMultiplier(void) {
    return g_mod_info.is_active ? g_gold_mult : 1;
}

MCD_EXPORT bool MCD_ModInit(void) {
    MCD_Config_Load(&g_config, "configs/emerald_multiplier.ini");
    g_mod_info.is_active = MCD_Config_GetBool(&g_config, "enabled", true);
    g_mod_info.hotkey = MCD_Config_GetInt(&g_config, "hotkey_vk", 0x71);
    g_emerald_mult = MCD_Config_GetInt(&g_config, "emerald_multiplier", 10);
    g_gold_mult = MCD_Config_GetInt(&g_config, "gold_multiplier", 5);

    g_currency_addr = MCD_FindPattern("Dungeons-Win64-Shipping.exe", "\x01\x53\x28\x8B\x43\x28", "xxxxxx");
    if (g_currency_addr) {
        memcpy(g_original_code, (void*)g_currency_addr, sizeof(g_original_code));
        g_hooked = true;
    }
    return true;
}

MCD_EXPORT void MCD_ModShutdown(void) {
    if (g_hooked && g_currency_addr) {
        MCD_PatchMemory((void*)g_currency_addr, g_original_code, sizeof(g_original_code));
        g_hooked = false;
    }
}

MCD_EXPORT void MCD_ModUpdate(float delta_time) {
    (void)delta_time;
}

MCD_EXPORT bool MCD_ToggleMod(bool enable) {
    g_mod_info.is_active = enable;
    return g_mod_info.is_active;
}

MCD_EXPORT bool MCD_IsModEnabled(void) {
    return g_mod_info.is_active;
}

MCD_EXPORT void MCD_OnKeyEvent(int key_code, bool is_down) {
    if (is_down && key_code == g_mod_info.hotkey) {
        MCD_ToggleMod(!g_mod_info.is_active);
    }
}

#ifdef _WIN32
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    (void)hinstDLL;
    (void)lpvReserved;
    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            MCD_ModInit();
            break;
        case DLL_PROCESS_DETACH:
            MCD_ModShutdown();
            break;
    }
    return TRUE;
}
#endif
