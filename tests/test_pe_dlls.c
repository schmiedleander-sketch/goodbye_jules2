/**
 * PE32+ (x64) Windows DLL Validation Test
 * Verifies that each mod file is a valid 64-bit Windows PE Dynamic Link Library
 * with valid DOS header (MZ) and PE signature (PE\0\0).
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#pragma pack(push, 1)
typedef struct {
    uint16_t e_magic;    // Magic number ("MZ")
    uint16_t e_cblp;
    uint16_t e_cp;
    uint16_t e_crlc;
    uint16_t e_cparhdr;
    uint16_t e_minalloc;
    uint16_t e_maxalloc;
    uint16_t e_ss;
    uint16_t e_sp;
    uint16_t e_csum;
    uint16_t e_ip;
    uint16_t e_cs;
    uint16_t e_lfarlc;
    uint16_t e_ovno;
    uint16_t e_res[4];
    uint16_t e_oemid;
    uint16_t e_oeminfo;
    uint16_t e_res2[10];
    int32_t  e_lfanew;   // File address of new exe header
} IMAGE_DOS_HEADER;

typedef struct {
    uint32_t Signature;       // "PE\0\0"
    uint16_t Machine;         // 0x8664 for AMD64
    uint16_t NumberOfSections;
    uint32_t TimeDateStamp;
    uint32_t PointerToSymbolTable;
    uint32_t NumberOfSymbols;
    uint16_t SizeOfOptionalHeader;
    uint16_t Characteristics; // 0x2000 has IMAGE_FILE_DLL
} IMAGE_FILE_HEADER;
#pragma pack(pop)

static const char* MOD_DLL_PATHS[] = {
    "bin/mcd2_modloader.dll",
    "bin/mods/01_god_mode.dll",
    "bin/mods/02_infinite_arrows.dll",
    "bin/mods/03_speed_demon.dll",
    "bin/mods/04_emerald_multiplier.dll",
    "bin/mods/05_custom_fov_camera.dll",
    "bin/mods/06_one_hit_kill.dll",
    "bin/mods/07_instant_cooldown.dll",
    "bin/mods/08_auto_salvage.dll",
    "bin/mods/09_item_spawner.dll",
    "bin/mods/10_enemy_radar.dll",
    "bin/mods/11_enchantment_reroller.dll",
    "bin/mods/12_xp_booster.dll",
    "bin/mods/13_no_clip_ghost.dll",
    "bin/mods/14_boss_health_bar.dll",
    "bin/mods/15_custom_loot_filter.dll",
    "bin/mods/16_pet_enhancer.dll",
    "bin/mods/17_weather_time_override.dll",
    "bin/mods/18_multiplayer_sync_plus.dll",
    "bin/mods/19_infinite_lives.dll",
    "bin/mods/20_damage_meter_hud.dll"
};

int main(void) {
    int total = sizeof(MOD_DLL_PATHS) / sizeof(MOD_DLL_PATHS[0]);
    int passed = 0;

    printf("====================================================\n");
    printf(" Verifying PE32+ (x64) Windows DLL Binary Integrity \n");
    printf("====================================================\n\n");

    for (int i = 0; i < total; ++i) {
        const char* path = MOD_DLL_PATHS[i];
        FILE* fp = fopen(path, "rb");
        if (!fp) {
            fprintf(stderr, "[FAIL] Cannot open file: %s\n", path);
            continue;
        }

        IMAGE_DOS_HEADER dos;
        if (fread(&dos, sizeof(dos), 1, fp) != 1) {
            fprintf(stderr, "[FAIL] Failed to read DOS header: %s\n", path);
            fclose(fp);
            continue;
        }

        if (dos.e_magic != 0x5A4D) { // 'MZ'
            fprintf(stderr, "[FAIL] Invalid DOS signature: 0x%04X in %s\n", dos.e_magic, path);
            fclose(fp);
            continue;
        }

        if (fseek(fp, dos.e_lfanew, SEEK_SET) != 0) {
            fprintf(stderr, "[FAIL] Failed to seek to PE header: %s\n", path);
            fclose(fp);
            continue;
        }

        IMAGE_FILE_HEADER pe;
        if (fread(&pe, sizeof(pe), 1, fp) != 1) {
            fprintf(stderr, "[FAIL] Failed to read PE file header: %s\n", path);
            fclose(fp);
            continue;
        }

        if (pe.Signature != 0x00004550) { // "PE\0\0"
            fprintf(stderr, "[FAIL] Invalid PE signature: 0x%08X in %s\n", pe.Signature, path);
            fclose(fp);
            continue;
        }

        if (pe.Machine != 0x8664) { // IMAGE_FILE_MACHINE_AMD64
            fprintf(stderr, "[FAIL] Target machine is not AMD64 (0x8664): 0x%04X in %s\n", pe.Machine, path);
            fclose(fp);
            continue;
        }

        if (!(pe.Characteristics & 0x2000)) { // IMAGE_FILE_DLL
            fprintf(stderr, "[FAIL] Binary is not marked as a DLL: 0x%04X in %s\n", pe.Characteristics, path);
            fclose(fp);
            continue;
        }

        fseek(fp, 0, SEEK_END);
        long sz = ftell(fp);
        fclose(fp);

        printf("[PASS] %-36s (PE32+ x86-64 DLL, size: %ld bytes)\n", path, sz);
        passed++;
    }

    printf("\nIntegrity Test Results: %d / %d DLLs verified successfully.\n", passed, total);
    return (passed == total) ? 0 : 1;
}
