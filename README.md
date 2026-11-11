# Minecraft Dungeons 2 (MCD2) Standalone Native Mod Suite

A collection of **20 standalone native mods** for Minecraft Dungeons 2, compiled as native 64-bit Windows dynamic link libraries (`.dll`).

**Engine-Independent:** No Unreal Engine editor, UnrealBuildTool, or source engine installations are required. The mods operate standalone via native Windows x64 DLL injection and the lightweight Minecraft Dungeons 2 C/C++ Mod SDK.

---

## 📦 Included Mods (20 DLLs)

| # | Mod Name | DLL Filename | Description |
|---|---|---|---|
| **01** | **God Mode & Emergency Aegis** | `01_god_mode.dll` | Grants complete invulnerability, permanent emergency shields, and nullifies lethal damage. |
| **02** | **Infinite Arrows & Quiver Refill** | `02_infinite_arrows.dll` | Keeps quiver capped at 999 arrows; never runs out of specialized ammunition. |
| **03** | **Speed Demon Overdrive** | `03_speed_demon.dll` | 2.25x movement speed multiplier and 2.50x attack speed velocity booster. |
| **04** | **Emerald & Gold Multiplier** | `04_emerald_multiplier.dll` | 10x multiplier on emerald drops and chest gold rewards. |
| **05** | **Enhanced Camera & Custom FOV** | `05_custom_fov_camera.dll` | Unlocked field of view (95°+), custom zoom distance, and pitch/yaw rotation. |
| **06** | **One-Hit Kill & Armor Pierce** | `06_one_hit_kill.dll` | 9,999,999 outgoing damage per hit, guarantees criticals, and pierces armor. |
| **07** | **Instant Artifact & Potion Cooldown** | `07_instant_cooldown.dll` | Zero cooldown for artifacts, healing potion flasks, and class skills. |
| **08** | **Smart Auto-Salvage Utility** | `08_auto_salvage.dll` | Automatically salvages common and uncommon junk loot directly into emeralds. |
| **09** | **In-Game Item & Gear Spawner** | `09_item_spawner.dll` | Programmatic item spawning with power level overrides and gilding support. |
| **10** | **Tactical Enemy Radar & ESP** | `10_enemy_radar.dll` | Tracks active hostiles within 1,500 units, alerts on enchanted mobs and bosses. |
| **11** | **Free Enchantment Reroller** | `11_enchantment_reroller.dll` | 0 gold cost at Enchantsmith and guarantees Tier 3 enchantments. |
| **12** | **XP & Leveling Progression Booster** | `12_xp_booster.dll` | 5x experience multiplier for rapid character and seasonal pass leveling. |
| **13** | **Ghost Walk & No Clip** | `13_no_clip_ghost.dll` | Toggles collision geometry, enabling phase traversal through obstacles and gates. |
| **14** | **Boss Health Bar & Phase Overlay** | `14_boss_health_bar.dll` | Live numeric HP display, phase transitions, and shield breakdown tracking. |
| **15** | **Custom Loot Filter & Beam Highlighter** | `15_custom_loot_filter.dll` | Colored ground loot beams and automatic item vacuuming. |
| **16** | **Companion & Pet Master Overhaul** | `16_pet_enhancer.dll` | 3x companion damage, 4x health, and increases active summon slot cap to 10. |
| **17** | **Weather & Atmosphere Controller** | `17_weather_time_override.dll` | Custom time-of-day lock (e.g. noon), weather freezing, and distance fog remover. |
| **18** | **Multiplayer Co-Op Sync Plus** | `18_multiplayer_sync_plus.dll` | 3x teammate revive range, network latency smoother, and instanced loot drops. |
| **19** | **Infinite Lives & Defeat Immunity** | `19_infinite_lives.dll` | Locks remaining camp lives to 4, preventing mission wipes and failed night events. |
| **20** | **Real-time DPS & Combat Meter HUD** | `20_damage_meter_hud.dll` | Real-time DPS calculation, total damage output, and crit rate tracking. |

---

## 🛠️ Mod Architecture & SDK

- **SDK Header**: `include/mcd2_mod_sdk.h`
- **Mod Loader**: `bin/mcd2_modloader.dll` (`src/mcd2_modloader.c`)
- **Launcher / Host**: `bin/mcd2_launcher.exe` (`src/mcd2_launcher.c`)
- **Configuration**: `config/mods_config.json`

Every mod implements standard Windows DLL entry points:
- `DllMain(HINSTANCE, DWORD, LPVOID)`
- `const MCD2_ModInfo* MCD2_GetModInfo(void)`
- `MCD2_Result MCD2_ModInit(void)`
- `void MCD2_ModShutdown(void)`
- Hook callbacks (`MCD2_OnGameTick`, `MCD2_OnDamageCalculated`, `MCD2_OnLootDrop`)

---

## 🚀 Building & Testing

### Requirements
- `x86_64-w64-mingw32-gcc` (for building Windows x64 DLLs)
- Optional: `wine64` (for executing the simulation harness on Linux)

### Build All Mods & Binaries
```bash
chmod +x scripts/build_all.sh
./scripts/build_all.sh
```

### Run Binary Integrity Tests
Verifies that all 20 mod DLLs and `mcd2_modloader.dll` have valid PE32+ (x86-64) headers, export tables, and characteristics:
```bash
./tests/test_pe_dlls
```

### Run Simulation Test via Wine
```bash
cd bin
wine64 mcd2_launcher.exe
```
