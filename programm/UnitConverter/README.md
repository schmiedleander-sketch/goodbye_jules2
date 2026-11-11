# UnitConverter

**Category**: Useful Apps
**Description**: Converts digital storage units, length, weight, and temperature.
**Target Platform**: Windows 11 x64 (Compatible with Windows 10/11 64-bit)
**Dependencies**: 100% Self-contained static binary (zero external DLL or runtime dependencies required).

## Files in Package
- `UnitConverter.exe`: Standalone 64-bit Windows executable.
- `UnitConverterInstaller.msi`: Standard Windows Installer MSI package.
- `UnitConverter.c`: C source code.
- `UnitConverter.wxs`: WiX source configuration for the MSI.

## How to Run the .exe
Open Command Prompt or PowerShell in this directory:
```cmd
UnitConverter.exe
```

## How to Install via .msi
Run the installer directly or via msiexec:
```cmd
msiexec /i UnitConverterInstaller.msi /quiet /qn
```
