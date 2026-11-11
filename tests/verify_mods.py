#!/usr/bin/env python3
import os
import subprocess
import sys

EXPECTED_MODS = [
    "mcd_godmode.dll",
    "mcd_emerald_gold_multiplier.dll",
    "mcd_unlimited_arrows.dll",
    "mcd_artifact_cooldown.dll",
    "mcd_speed_hack.dll",
    "mcd_one_hit_kill.dll",
    "mcd_drop_rate_booster.dll",
    "mcd_free_enchantment.dll",
    "mcd_free_vendor_restock.dll",
    "mcd_fov_camera_unlocker.dll",
    "mcd_mob_freeze_aura.dll",
    "mcd_auto_loot_collector.dll",
    "mcd_dev_console_unlocker.dll",
    "mcd_skip_mission_timer.dll",
    "mcd_custom_item_spawner.dll",
    "mcd_xp_multiplier.dll",
    "mcd_nightmare_difficulty.dll",
    "mcd_sound_visual_notifier.dll",
    "mcd_no_roll_cooldown.dll",
    "mcd_ue_tweak_loader.dll",
]

MANDATORY_EXPORTS = [
    "MCD_GetModInfo",
    "MCD_ModInit",
    "MCD_ModShutdown",
    "MCD_ModUpdate",
    "MCD_ToggleMod",
    "MCD_IsModEnabled",
    "MCD_OnKeyEvent",
]

def verify_dll(dll_path):
    print(f"[*] Verifying {os.path.basename(dll_path)}...")
    if not os.path.isfile(dll_path):
        print(f"[-] ERROR: File {dll_path} does not exist!")
        return False

    size = os.path.getsize(dll_path)
    if size < 10000:
        print(f"[-] ERROR: File size too small ({size} bytes)!")
        return False

    # Check PE header magic bytes
    with open(dll_path, "rb") as f:
        dos_hdr = f.read(2)
        if dos_hdr != b'MZ':
            print(f"[-] ERROR: Invalid DOS header magic in {dll_path}!")
            return False
        f.seek(0x3C)
        pe_offset = int.from_bytes(f.read(4), byteorder='little')
        f.seek(pe_offset)
        pe_sig = f.read(4)
        if pe_sig != b'PE\x00\x00':
            print(f"[-] ERROR: Invalid PE signature in {dll_path}!")
            return False
        machine = int.from_bytes(f.read(2), byteorder='little')
        # 0x8664 is IMAGE_FILE_MACHINE_AMD64
        if machine != 0x8664:
            print(f"[-] ERROR: Machine is not x86-64 (got 0x{machine:04x})!")
            return False

    # Check exports via objdump
    try:
        proc = subprocess.run(
            ["x86_64-w64-mingw32-objdump", "-p", dll_path],
            capture_output=True,
            text=True,
            check=True
        )
        output = proc.stdout
        for exp in MANDATORY_EXPORTS:
            if exp not in output:
                print(f"[-] ERROR: Missing export '{exp}' in {dll_path}!")
                return False
    except Exception as e:
        print(f"[-] ERROR checking exports: {e}")
        return False

    print(f"[+] {os.path.basename(dll_path)} is valid x86-64 PE32+ DLL with all exports!")
    return True

def main():
    print("==================================================")
    print("Minecraft Dungeons Mod Verification Suite (20 Mods)")
    print("==================================================")
    if len(EXPECTED_MODS) != 20:
        print(f"[-] ERROR: Expected 20 mods, found {len(EXPECTED_MODS)} in list!")
        sys.exit(1)

    all_passed = True
    for mod in EXPECTED_MODS:
        dll_path = os.path.join("bin", mod)
        if not verify_dll(dll_path):
            all_passed = False

    if not all_passed:
        print("[-] Verification failed!")
        sys.exit(1)

    print("\n[SUCCESS] All 20 Minecraft Dungeons mods successfully verified!")
    sys.exit(0)

if __name__ == "__main__":
    main()
