#include "mcd_mod_sdk.h"
#include "mcd_config.h"
#include <stdio.h>

static MCD_ModInfo g_mod_info = {
    .id = "mcd_artifact_cooldown",
    .name = "Artifact Cooldown Eliminator",
    .version = "1.0.0",
    .author = "MCD Modding Team",
    .description = "Instantly resets cooldowns on all equipped artifacts (Death Cap, Boots, Iron Hide, etc.).",
    .category = "Combat / Artifacts",
    .is_active = true,
    .hotkey = 0x73 /* VK_F4 */
};

static MCD_Config g_config;
static uintptr_t g_cooldown_addr = 0;
static uint8_t g_orig_bytes[5];
static bool g_patched = false;

MCD_EXPORT const MCD_ModInfo* MCD_GetModInfo(void) {
    return &g_mod_info;
}

MCD_EXPORT bool MCD_ModInit(void) {
    MCD_Config_Load(&g_config, "configs/artifact_cooldown.ini");
    g_mod_info.is_active = MCD_Config_GetBool(&g_config, "enabled", true);
    g_mod_info.hotkey = MCD_Config_GetInt(&g_config, "hotkey_vk", 0x73);

    g_cooldown_addr = MCD_FindPattern("Dungeons-Win64-Shipping.exe", "\xF3\x0F\x11\x4B\x38", "xxxxx");
    if (g_cooldown_addr) {
        memcpy(g_orig_bytes, (void*)g_cooldown_addr, sizeof(g_orig_bytes));
        if (g_mod_info.is_active) {
            MCD_NopMemory((void*)g_cooldown_addr, sizeof(g_orig_bytes));
            g_patched = true;
        }
    }
    return true;
}

MCD_EXPORT void MCD_ModShutdown(void) {
    if (g_patched && g_cooldown_addr) {
        MCD_PatchMemory((void*)g_cooldown_addr, g_orig_bytes, sizeof(g_orig_bytes));
        g_patched = false;
    }
}

MCD_EXPORT void MCD_ModUpdate(float delta_time) {
    (void)delta_time;
}

MCD_EXPORT bool MCD_ToggleMod(bool enable) {
    g_mod_info.is_active = enable;
    if (g_cooldown_addr) {
        if (enable && !g_patched) {
            MCD_NopMemory((void*)g_cooldown_addr, sizeof(g_orig_bytes));
            g_patched = true;
        } else if (!enable && g_patched) {
            MCD_PatchMemory((void*)g_cooldown_addr, g_orig_bytes, sizeof(g_orig_bytes));
            g_patched = false;
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
