/**
 * Minecraft Dungeons 2 (MCD2) Standalone Native Mod SDK
 *
 * High-performance C/C++ Modding API for Minecraft Dungeons 2.
 * Operates completely standalone via native Windows x64 DLL injection / hook chaining.
 * No Unreal Engine editor, UBT, or editor dependencies required!
 */

#ifndef MCD2_MOD_SDK_H
#define MCD2_MOD_SDK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <windows.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define MCD2_SDK_VERSION_MAJOR 2
#define MCD2_SDK_VERSION_MINOR 0
#define MCD2_SDK_VERSION_PATCH 4

#define MCD2_API __declspec(dllexport)

/* Mod status return codes */
typedef enum {
    MCD2_SUCCESS = 0,
    MCD2_ERR_INIT_FAILED = 1,
    MCD2_ERR_HOOK_FAILED = 2,
    MCD2_ERR_CONFIG_INVALID = 3,
    MCD2_ERR_UNSUPPORTED_VER = 4,
    MCD2_ERR_ALREADY_LOADED = 5
} MCD2_Result;

/* Mod Metadata descriptor */
typedef struct {
    const char* mod_id;
    const char* mod_name;
    const char* version;
    const char* author;
    const char* description;
    uint32_t target_game_build;
    bool enabled_by_default;
} MCD2_ModInfo;

/* Player State structure for in-memory hook interceptors */
typedef struct {
    float health;
    float max_health;
    float shield;
    float max_shield;
    float movement_speed_mult;
    float attack_speed_mult;
    int32_t emeralds;
    int32_t gold;
    int32_t arrows;
    int32_t lives_remaining;
    float x, y, z;
    float yaw, pitch, roll;
    bool is_invulnerable;
    bool no_clip;
} MCD2_PlayerState;

/* Combat Event payload */
typedef struct {
    uint64_t attacker_id;
    uint64_t target_id;
    float incoming_damage;
    float modified_damage;
    bool is_critical;
    bool is_projectile;
    const char* damage_type;
} MCD2_DamageEvent;

/* Loot Event payload */
typedef struct {
    uint32_t item_id;
    const char* item_name;
    int32_t rarity; // 0=Common, 1=Rare, 2=Unique, 3=Gilded, 4=Ancient
    int32_t power_level;
    int32_t emerald_value;
    float drop_x, drop_y, drop_z;
    bool should_salvage;
} MCD2_LootEvent;

/* Camera State structure */
typedef struct {
    float fov;
    float zoom_distance;
    float pitch_angle;
    float yaw_angle;
    float height_offset;
    bool free_cam_enabled;
} MCD2_CameraState;

/* Mod Export Function Prototypes */
typedef MCD2_Result (*PFN_MCD2_ModInit)(void);
typedef void (*PFN_MCD2_ModShutdown)(void);
typedef const MCD2_ModInfo* (*PFN_MCD2_GetModInfo)(void);
typedef void (*PFN_MCD2_OnGameTick)(float delta_time, MCD2_PlayerState* player);
typedef void (*PFN_MCD2_OnDamageCalculated)(MCD2_DamageEvent* dmg_event);
typedef void (*PFN_MCD2_OnLootDrop)(MCD2_LootEvent* loot_event);

/* Standard Mod Exports declaration macro */
#define DECLARE_MCD2_MOD(mod_id_str, mod_name_str, ver_str, author_str, desc_str) \
    static MCD2_ModInfo g_ModInfo = { \
        .mod_id = mod_id_str, \
        .mod_name = mod_name_str, \
        .version = ver_str, \
        .author = author_str, \
        .description = desc_str, \
        .target_game_build = 202611, \
        .enabled_by_default = true \
    }; \
    MCD2_API const MCD2_ModInfo* MCD2_GetModInfo(void) { \
        return &g_ModInfo; \
    }

#ifdef __cplusplus
}
#endif

#endif /* MCD2_MOD_SDK_H */
