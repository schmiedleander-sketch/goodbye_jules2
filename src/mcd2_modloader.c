/**
 * Minecraft Dungeons 2 Mod Loader & Host Controller
 *
 * Scans the mods directory, dynamically loads all .dll mod files, validates
 * their MCD2_GetModInfo exports, initializes each mod, and dispatches game lifecycle hooks.
 * Does not require Unreal Engine.
 */

#include "../include/mcd2_mod_sdk.h"

#define MAX_MODS 64

typedef struct {
    HMODULE handle;
    const MCD2_ModInfo* info;
    PFN_MCD2_ModInit init_fn;
    PFN_MCD2_ModShutdown shutdown_fn;
    PFN_MCD2_OnGameTick tick_fn;
    PFN_MCD2_OnDamageCalculated dmg_fn;
    PFN_MCD2_OnLootDrop loot_fn;
} LoadedMod;

static LoadedMod g_LoadedMods[MAX_MODS];
static int g_LoadedCount = 0;

MCD2_API int MCD2_LoadMod(const char* dll_path) {
    if (g_LoadedCount >= MAX_MODS) return -1;

    HMODULE mod = LoadLibraryA(dll_path);
    if (!mod) {
        printf("[ModLoader] Failed to load DLL: %s\n", dll_path);
        return -2;
    }

    PFN_MCD2_GetModInfo get_info_fn = (PFN_MCD2_GetModInfo)GetProcAddress(mod, "MCD2_GetModInfo");
    if (!get_info_fn) {
        printf("[ModLoader] DLL does not export MCD2_GetModInfo: %s\n", dll_path);
        FreeLibrary(mod);
        return -3;
    }

    const MCD2_ModInfo* info = get_info_fn();
    LoadedMod* slot = &g_LoadedMods[g_LoadedCount++];
    slot->handle = mod;
    slot->info = info;
    slot->init_fn = (PFN_MCD2_ModInit)GetProcAddress(mod, "MCD2_ModInit");
    slot->shutdown_fn = (PFN_MCD2_ModShutdown)GetProcAddress(mod, "MCD2_ModShutdown");
    slot->tick_fn = (PFN_MCD2_OnGameTick)GetProcAddress(mod, "MCD2_OnGameTick");
    slot->dmg_fn = (PFN_MCD2_OnDamageCalculated)GetProcAddress(mod, "MCD2_OnDamageCalculated");
    slot->loot_fn = (PFN_MCD2_OnLootDrop)GetProcAddress(mod, "MCD2_OnLootDrop");

    if (slot->init_fn) {
        slot->init_fn();
    }

    printf("[ModLoader] Successfully loaded [%s] v%s by %s\n", info->mod_name, info->version, info->author);
    return 0;
}

MCD2_API int MCD2_GetLoadedModCount(void) {
    return g_LoadedCount;
}

MCD2_API const MCD2_ModInfo* MCD2_GetLoadedModInfo(int index) {
    if (index < 0 || index >= g_LoadedCount) return NULL;
    return g_LoadedMods[index].info;
}

MCD2_API void MCD2_DispatchGameTick(float delta_time, MCD2_PlayerState* player) {
    for (int i = 0; i < g_LoadedCount; ++i) {
        if (g_LoadedMods[i].tick_fn) {
            g_LoadedMods[i].tick_fn(delta_time, player);
        }
    }
}

MCD2_API void MCD2_DispatchDamage(MCD2_DamageEvent* dmg) {
    for (int i = 0; i < g_LoadedCount; ++i) {
        if (g_LoadedMods[i].dmg_fn) {
            g_LoadedMods[i].dmg_fn(dmg);
        }
    }
}

MCD2_API void MCD2_DispatchLoot(MCD2_LootEvent* loot) {
    for (int i = 0; i < g_LoadedCount; ++i) {
        if (g_LoadedMods[i].loot_fn) {
            g_LoadedMods[i].loot_fn(loot);
        }
    }
}

MCD2_API void MCD2_UnloadAllMods(void) {
    for (int i = 0; i < g_LoadedCount; ++i) {
        if (g_LoadedMods[i].shutdown_fn) {
            g_LoadedMods[i].shutdown_fn();
        }
        if (g_LoadedMods[i].handle) {
            FreeLibrary(g_LoadedMods[i].handle);
        }
    }
    g_LoadedCount = 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    (void)hinstDLL; (void)lpvReserved;
    if (fdwReason == DLL_PROCESS_DETACH) {
        MCD2_UnloadAllMods();
    }
    return TRUE;
}
