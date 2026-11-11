#include "mcd_mod_sdk.h"
#include "mcd_config.h"
#include <stdio.h>

static MCD_ModInfo g_mod_info = {
    .id = "mcd_free_enchantment",
    .name = "Free Enchantment & Unlimited Rerolls",
    .version = "1.0.0",
    .author = "MCD Modding Team",
    .description = "Upgrades enchantments with 0 enchantment point cost and allows infinite Enchantsmith rerolls with 0 gold.",
    .category = "Economy / Crafting",
    .is_active = true,
    .hotkey = 0x77 /* VK_F8 */
};

static MCD_Config g_config;
static uintptr_t g_enchant_cost_addr = 0;
static uint8_t g_orig_bytes[6];
static bool g_hooked = false;

MCD_EXPORT const MCD_ModInfo* MCD_GetModInfo(void) {
    return &g_mod_info;
}

MCD_EXPORT int MCD_GetEnchantmentCost(int base_cost) {
    if (!g_mod_info.is_active) return base_cost;
    return 0;
}

MCD_EXPORT int MCD_GetRerollGoldCost(int base_cost) {
    if (!g_mod_info.is_active) return base_cost;
    return 0;
}

MCD_EXPORT bool MCD_ModInit(void) {
    MCD_Config_Load(&g_config, "configs/free_enchantment.ini");
    g_mod_info.is_active = MCD_Config_GetBool(&g_config, "enabled", true);
    g_mod_info.hotkey = MCD_Config_GetInt(&g_config, "hotkey_vk", 0x77);

    g_enchant_cost_addr = MCD_FindPattern("Dungeons-Win64-Shipping.exe", "\x29\x53\x40\x8B\x43\x40", "xxxxxx");
    if (g_enchant_cost_addr) {
        memcpy(g_orig_bytes, (void*)g_enchant_cost_addr, sizeof(g_orig_bytes));
        if (g_mod_info.is_active) {
            MCD_NopMemory((void*)g_enchant_cost_addr, 3);
            g_hooked = true;
        }
    }
    return true;
}

MCD_EXPORT void MCD_ModShutdown(void) {
    if (g_hooked && g_enchant_cost_addr) {
        MCD_PatchMemory((void*)g_enchant_cost_addr, g_orig_bytes, 3);
        g_hooked = false;
    }
}

MCD_EXPORT void MCD_ModUpdate(float delta_time) {
    (void)delta_time;
}

MCD_EXPORT bool MCD_ToggleMod(bool enable) {
    g_mod_info.is_active = enable;
    if (g_enchant_cost_addr) {
        if (enable && !g_hooked) {
            MCD_NopMemory((void*)g_enchant_cost_addr, 3);
            g_hooked = true;
        } else if (!enable && g_hooked) {
            MCD_PatchMemory((void*)g_enchant_cost_addr, g_orig_bytes, 3);
            g_hooked = false;
        }
    }
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
