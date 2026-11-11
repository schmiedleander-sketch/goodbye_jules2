# Minecraft Dungeons Mods (20 Native DLL Mods)

A comprehensive suite of 20 high-performance, native mods for **Minecraft Dungeons** (`Dungeons-Win64-Shipping.exe`).

- **Precompiled DLLs included**: Located in `bin/` ready for immediate deployment.
- **No Unreal Engine Required**: Operates completely without UE editor, UModel, UnrealPak, or engine compiling.
- **Full Configuration & Hotkeys**: Each mod includes an editable `.ini` config in `configs/`.

---

## Mod Catalog (20 Mods)

| # | Mod Name | Binary DLL | Default Key | Category |
|---|---|---|---|---|
| 01 | God Mode & Invulnerability | `bin/mcd_godmode.dll` | `F1` | Gameplay / Cheat |
| 02 | Emerald & Gold Multiplier | `bin/mcd_emerald_gold_multiplier.dll` | `F2` | Economy / Currency |
| 03 | Unlimited Arrows | `bin/mcd_unlimited_arrows.dll` | `F3` | Combat / Ammo |
| 04 | Artifact Cooldown Eliminator | `bin/mcd_artifact_cooldown.dll` | `F4` | Combat / Artifacts |
| 05 | Speed Hack & Roll Multiplier | `bin/mcd_speed_hack.dll` | `F5` | Movement / Utility |
| 06 | One Hit Kill & Super Damage | `bin/mcd_one_hit_kill.dll` | `F6` | Combat / Cheat |
| 07 | Drop Rate Booster | `bin/mcd_drop_rate_booster.dll` | `F7` | Loot / Drops |
| 08 | Free Enchantment & Rerolls | `bin/mcd_free_enchantment.dll` | `F8` | Economy / Crafting |
| 09 | Free Vendor Restock | `bin/mcd_free_vendor_restock.dll` | `F9` | Camp / Vendors |
| 10 | FOV & Camera Unlocker | `bin/mcd_fov_camera_unlocker.dll` | `F10` | Camera / Visual |
| 11 | Mob Freeze Aura | `bin/mcd_mob_freeze_aura.dll` | `F11` | Combat / Defense |
| 12 | Auto Loot Collector | `bin/mcd_auto_loot_collector.dll` | `F12` | Loot / Quality of Life |
| 13 | Dev Console Unlocker | `bin/mcd_dev_console_unlocker.dll` | `~` (Tilde) | Developer / Debug |
| 14 | Skip Mission Timer | `bin/mcd_skip_mission_timer.dll` | `T` | Missions / Progression |
| 15 | Custom Item Spawner | `bin/mcd_custom_item_spawner.dll` | `I` | Items / Inventory |
| 16 | XP Multiplier | `bin/mcd_xp_multiplier.dll` | `X` | Progression / XP |
| 17 | Nightmare Difficulty Modifier | `bin/mcd_nightmare_difficulty.dll` | `N` | Difficulty / Hardcore |
| 18 | Secret & Chest ESP Notifier | `bin/mcd_sound_visual_notifier.dll` | `V` | Exploration / ESP |
| 19 | No Roll Cooldown | `bin/mcd_no_roll_cooldown.dll` | `R` | Movement / Combat |
| 20 | UE Tweak & Master Mod Loader | `bin/mcd_ue_tweak_loader.dll` | `F6 / Auto` | System / Engine Loader |

---

## Quick Start & Installation

1. Copy the `.dll` files from `bin/` into:
   ```
   <Minecraft Dungeons Folder>/Dungeons/Binaries/Win64/
   ```
   or inject them into `Dungeons-Win64-Shipping.exe` using any standard DLL injector (or dxgi proxy loader).
2. Copy the `configs/` folder into the same folder as `Dungeons-Win64-Shipping.exe` to customize hotkeys and values.
3. Launch Minecraft Dungeons and use the assigned hotkeys to toggle mods in real-time.

For comprehensive details on each mod, see `docs/MODS_GUIDE.md`.

---

## Building from Source

Requirements: `make` and `mingw-w64` (`x86_64-w64-mingw32-gcc`).
```bash
make all
```

Run test suite:
```bash
python3 tests/verify_mods.py
```
