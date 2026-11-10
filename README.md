# Windows App SDK Suite & GACL Game Showcase

A collection of **20 Windows applications** built using Microsoft's modern desktop platform:
- **[Windows App SDK](https://github.com/microsoft/WindowsAppSDK)** (WinUI 3, XAML, Fluent Design, Windows App Runtime 1.6+)
- **[Game Asset Conditioning Library (GACL)](https://github.com/microsoft/Game-Asset-Conditioning-Library)** (specifically for the game applications: texture rate distortion optimization (BLER), DirectStorage 1.4 BCn shuffle transforms, and 16KB space curves)

---

## Architecture & Overview

All 20 applications are structured in the `apps/` directory and connected through the root solution `WindowsAppsSuite.sln`.

Each application targets `.NET 8.0` with Windows App SDK `1.6.250108002` and Windows SDK BuildTools `10.0.26100.1742`.

### Application Catalog

| # | Project Directory | Application Name | Category | Technologies & Features |
|---|-------------------|------------------|----------|-------------------------|
| 1 | `apps/01-TaskManagerPlus` | **Task Manager Plus** | System Utility | WinUI 3 process monitor, memory usage, thread counts, filtering, task termination |
| 2 | `apps/02-MarkdownNotePad` | **Markdown NotePad** | Productivity | Split-view Markdown editor with real-time live preview rendering and word/line metrics |
| 3 | `apps/03-DevPalette` | **DevPalette Color Tool** | Designer / Dev | RGB/HSL sliders, HEX conversions, WCAG 2.1 contrast ratio analysis, harmony swatches |
| 4 | `apps/04-FileChecksumValidator` | **File Checksum Validator** | Security | Cryptographic hashing (MD5, SHA-1, SHA-256, SHA-512) and hash match verification |
| 5 | `apps/05-NetworkSpeedPulse` | **Network Speed Pulse** | Network | ICMP latency monitor, round-trip ping time, and network adapter diagnostics |
| 6 | `apps/06-AudioWaveLab` | **Audio Wave Lab** | Audio / Media | Tone synthesizer (Sine, Square, Sawtooth), frequency tuner, and RIFF WAV exporter |
| 7 | `apps/07-JsonXmlForge` | **JSON & XML Forge** | Developer Tool | Syntax tree formatting, JSON prettifier/minifier, and XML validation |
| 8 | `apps/08-SystemHealthSentinel` | **System Health Sentinel** | Diagnostics | Host device diagnostics, logical CPU cores, OS kernel version, and volume disk space |
| 9 | `apps/09-ClipboardVault` | **Clipboard Vault** | Productivity | History manager for code snippets, clipboard buffers, and fast snippet tagging |
| 10 | `apps/10-BatchRenamePro` | **Batch Rename Pro** | Utility | Mass file renamer with custom prefix, suffix, index sequence, and previewer |
| 11 | `apps/11-ImageResizerFluid` | **Image Resizer Fluid** | Media / Graphics | Aspect ratio scaler and image format converter (PNG, JPEG, WebP, BMP) |
| 12 | `apps/12-RestApiClient` | **REST API Client** | Developer Tool | HTTP method client (GET/POST/PUT/DELETE) with JSON response viewer and status codes |
| 13 | `apps/13-PomodoroFocusHub` | **Pomodoro Focus Hub** | Productivity | 25-minute Pomodoro timer, session counter, pause/reset, and focus workflow |
| 14 | `apps/14-QuickLauncherTray` | **Quick Launcher Tray** | Desktop Utility | One-click developer launchpad and system tool trigger grid |
| 15 | `apps/15-GitRepositoryExplorer` | **Git Repository Explorer** | Developer Tool | Visual Git commit log browser, revision history inspector, and branch tracker |
| 16 | `apps/16-CyberRacer2D` | **Cyber Racer 2D** *(Game)* | Game & GACL | Retro arcade racing game integrating **GACL DirectStorage 1.4 BC7 Split shuffle** |
| 17 | `apps/17-DungeonCrawlerGACL` | **Dungeon Crawler GACL** *(Game)* | Game & GACL | Procedural roguelike featuring **GACL Block-Level Entropy Reduction (BLER)** for BC1 sprite atlases |
| 18 | `apps/18-SpaceAsteroidsBattle` | **Space Asteroids Battle** *(Game)* | Game & GACL | Vector arcade shooter using **GACL BC7 texture compression pipeline & 256KB clamp** |
| 19 | `apps/19-VoxelWorldBuilder` | **Voxel World Builder** *(Game)* | Game & GACL | Voxel sandbox world engine conditioning **BC4 height & BC5 normal map streams via GACL** |
| 20 | `apps/20-RetroPlatformerJump` | **Retro Platformer Jump** *(Game)* | Game & GACL | 2D platformer leveraging **GACL 16KB micro-tile space curves and runtime unshuffle** |

---

## Game Asset Conditioning Library (GACL) Integration

For the 5 game titles (`apps/16` through `apps/20`), texture assets are conditioned using Microsoft's **Game Asset Conditioning Library**:
- **BLER (Block-Level Entropy Reduction)**: Unifies visually similar 4x4 BCn blocks within a 256KB window, achieving up to 50% stream reduction with >40 dB PSNR.
- **DirectStorage Shuffle Transforms**:
  - `ZSTD_BC1`: Format 0x01
  - `ZSTD_BC3`: Format 0x02
  - `ZSTD_BC4`: Format 0x03
  - `ZSTD_BC5`: Format 0x04
  - `ZSTD_BC7_SPLIT`: Format 0x05 (DirectStorage 1.4 GA unshuffle)
- **Space Curves**: Converts linear textures into 16KB micro-tile Z-order layouts to maximize spatial adjacency compression.

Each game includes a dedicated `GaclPipeline.cs` native binding interface to communicate with GACL routines.

---

## Building and Running

### Prerequisites
1. Windows 10 version 1809 (Build 17763) or Windows 11.
2. [.NET 8.0 SDK](https://dotnet.microsoft.com/download/dotnet/8.0).
3. Visual Studio 2022 (v143) with the **.NET Desktop Development** and **Desktop development with C++** workloads, including the **Windows App SDK C# Templates**.

### Command Line Build
To build all 20 applications from the repository root:
```powershell
dotnet build WindowsAppsSuite.sln
```

To run an individual application (e.g. `TaskManagerPlus` or `CyberRacer2D`):
```powershell
cd apps/01-TaskManagerPlus
dotnet run

# Or a game:
cd apps/16-CyberRacer2D
dotnet run
```
