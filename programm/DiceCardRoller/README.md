# DiceCardRoller

**Category**: Fun Apps
**Description**: Tabletop gaming dice simulator (d6, d20) and standard card dealer.
**Target Platform**: Windows 11 x64 (Compatible with Windows 10/11 64-bit)
**Dependencies**: 100% Self-contained static binary (zero external DLL or runtime dependencies required).

## Files in Package
- `DiceCardRoller.exe`: Standalone 64-bit Windows executable.
- `DiceCardRollerInstaller.msi`: Standard Windows Installer MSI package.
- `DiceCardRoller.c`: C source code.
- `DiceCardRoller.wxs`: WiX source configuration for the MSI.

## How to Run the .exe
Open Command Prompt or PowerShell in this directory:
```cmd
DiceCardRoller.exe
```

## How to Install via .msi
Run the installer directly or via msiexec:
```cmd
msiexec /i DiceCardRollerInstaller.msi /quiet /qn
```
