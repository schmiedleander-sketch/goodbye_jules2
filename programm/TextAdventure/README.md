# TextAdventure

**Category**: Fun Apps
**Description**: Interactive dungeon quest text role-playing game.
**Target Platform**: Windows 11 x64 (Compatible with Windows 10/11 64-bit)
**Dependencies**: 100% Self-contained static binary (zero external DLL or runtime dependencies required).

## Files in Package
- `TextAdventure.exe`: Standalone 64-bit Windows executable.
- `TextAdventureInstaller.msi`: Standard Windows Installer MSI package.
- `TextAdventure.c`: C source code.
- `TextAdventure.wxs`: WiX source configuration for the MSI.

## How to Run the .exe
Open Command Prompt or PowerShell in this directory:
```cmd
TextAdventure.exe
```

## How to Install via .msi
Run the installer directly or via msiexec:
```cmd
msiexec /i TextAdventureInstaller.msi /quiet /qn
```
