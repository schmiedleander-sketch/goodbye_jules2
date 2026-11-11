# Minecraft Dungeons Mods Suite (20 Mods)

This repository contains 20 native, standalone mods for **Minecraft Dungeons** (`Dungeons-Win64-Shipping.exe`).
All mods are built as Windows 64-bit Dynamic Link Libraries (`.dll`) and **do NOT require Unreal Engine editor**, UModel, UnrealPak, or engine recompilation.

---

## Mod Catalog

| # | Mod Name | Binary DLL | Default Hotkey | Description |
|---|---|---|---|---|
| **01** | God Mode & Invulnerability | `mcd_godmode.dll` | **F1** | Prevents damage to player, health freeze at maximum. |
| **02** | Emerald & Gold Multiplier | `mcd_emerald_gold_multiplier.dll` | **F2** | Configurable emerald (10x) and gold (5x) drops multiplier. |
| **03** | Unlimited Arrows | `mcd_unlimited_arrows.dll` | **F3** | Eliminates arrow depletion on all bows, crossbows, and quivers. |
| **04** | Artifact Cooldown Eliminator | `mcd_artifact_cooldown.dll` | **F4** | Instant cooldown reset for all equipped artifacts. |
| **05** | Speed Hack & Roll Multiplier | `mcd_speed_hack.dll` | **F5** | 2.5x hero movement speed and 2x roll dash distance. |
| **06** | One Hit Kill & Super Damage | `mcd_one_hit_kill.dll` | **F6** | Deals lethal damage multiplier (999,999x) to hostile targets. |
| **07** | Drop Rate Booster | `mcd_drop_rate_booster.dll` | **F7** | Guarantees 100% Unique & Gilded drops with 3 enchantment slots. |
| **08** | Free Enchantment & Rerolls | `mcd_free_enchantment.dll` | **F8** | 0 enchantment points cost and free Enchantsmith rerolls. |
| **09** | Free Vendor Restock | `mcd_free_vendor_restock.dll` | **F9** | Free vendor refreshing & instant 0-mission Blacksmith upgrades. |
| **10** | FOV & Camera Unlocker | `mcd_fov_camera_unlocker.dll` | **F10** | Unlocks 95 FOV, 1800 camera distance, and custom tilt angle. |
| **11** | Mob Freeze Aura | `mcd_mob_freeze_aura.dll` | **F11** | Creates a 1500u paralyzing aura freezing all enemy AI actions. |
| **12** | Auto Loot Collector | `mcd_auto_loot_collector.dll` | **F12** | 5000u vacuum automatically collecting loot, arrows, emeralds. |
| **13** | Dev Console Unlocker | `mcd_dev_console_unlocker.dll` | **~ (Tilde)** | Unlocks native Unreal Engine 4 developer console. |
| **14** | Skip Mission Timer | `mcd_skip_mission_timer.dll` | **T** | Instantly clears ambush countdowns, arenas, and defense timers. |
| **15** | Custom Item Spawner | `mcd_custom_item_spawner.dll` | **I** | Injects custom power level items (e.g. 263 Gilded Fighter's Bindings). |
| **16** | XP Multiplier | `mcd_xp_multiplier.dll` | **X** | Multiplies gained experience by 5x for rapid leveling. |
| **17** | Nightmare Difficulty Modifier | `mcd_nightmare_difficulty.dll` | **N** | Hardcore mode with 3x mob HP, 2.5x damage, 60% elite pack spawns. |
| **18** | Secret & Chest ESP Notifier | `mcd_sound_visual_notifier.dll` | **V** | Highlights hidden chests, pig chests, runes, and plays audio chimes. |
| **19** | No Roll Cooldown | `mcd_no_roll_cooldown.dll` | **R** | Eliminates dodge roll cooldown for infinite mobility. |
| **20** | UE Tweak & Master Mod Loader | `mcd_ue_tweak_loader.dll` | **F6 / Auto** | Unlocks 144+ FPS caps, disables motion blur/vignette, manages mod loading. |

---

## Installation & Usage

1. **Locate Minecraft Dungeons directory**:
   - Launcher / MS Store / Steam: `<GamePath>/Dungeons/Binaries/Win64/`
2. **Copy the DLLs**:
   - Copy any or all `.dll` files from `release/` or `bin/` into the game directory or your standard DLL injector (e.g., Xenos, Cheat Engine, or proxy `dxgi.dll`).
3. **Configurations**:
   - Place the `configs/` folder next to the game executable to customize hotkeys, multipliers, and features.
4. **No Unreal Engine Required**:
   - These mods hook directly via memory patching and PE export tables in runtime memory. No UE editor, cooking, or pak repacking is needed.
