#include "mcd_mod_sdk.h"
#include "mcd_config.h"
#include <stdio.h>

static MCD_ModInfo g_mod_info = {
    .id = "mcd_godmode",
    .name = "God Mode & Invulnerability",
    .version = "1.0.0",
    .author = "MCD Modding Team",
    .description = "Prevents player damage, negates lethal hits, and locks health at maximum.",
    .category = "Gameplay / Cheat",
    .is_active = true,
    .hotkey = 0x70 /* VK_F1 */
};

static MCD_Config g_config;
static uintptr_t g_damage_hook_addr = 0;
static uint8_t g_original_bytes[8];
static bool g_hook_installed = false;

MCD_EXPORT const MCD_ModInfo* MCD_GetModInfo(void) {
    return &g_mod_info;
}

MCD_EXPORT bool MCD_ModInit(void) {
    MCD_Config_Load(&g_config, "configs/godmode.ini");
    g_mod_info.is_active = MCD_Config_GetBool(&g_config, "enabled", true);
    g_mod_info.hotkey = MCD_Config_GetInt(&g_config, "hotkey_vk", 0x70);

    /* In Minecraft Dungeons (Dungeons-Win64-Shipping.exe), hook TakeDamage function */
    g_damage_hook_addr = MCD_FindPattern("Dungeons-Win64-Shipping.exe", "\x89\x4B\x30\x48\x8B\x5C\x24", "xxxxxxx");
    if (g_damage_hook_addr) {
        memcpy(g_original_bytes, (void*)g_damage_hook_addr, sizeof(g_original_bytes));
        if (g_mod_info.is_active) {
            MCD_NopMemory((void*)g_damage_hook_addr, 3);
            g_hook_installed = true;
        }
    }
    return true;
}

MCD_EXPORT void MCD_ModShutdown(void) {
    if (g_hook_installed && g_damage_hook_addr) {
        MCD_PatchMemory((void*)g_damage_hook_addr, g_original_bytes, 3);
        g_hook_installed = false;
    }
}

MCD_EXPORT void MCD_ModUpdate(float delta_time) {
    (void)delta_time;
}

MCD_EXPORT bool MCD_ToggleMod(bool enable) {
    g_mod_info.is_active = enable;
    if (g_damage_hook_addr) {
        if (enable && !g_hook_installed) {
            MCD_NopMemory((void*)g_damage_hook_addr, 3);
            g_hook_installed = true;
        } else if (!enable && g_hook_installed) {
            MCD_PatchMemory((void*)g_damage_hook_addr, g_original_bytes, 3);
            g_hook_installed = false;
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
