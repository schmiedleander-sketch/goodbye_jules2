# AsciiArtBanner

**Category**: Fun Apps
**Description**: Converts plain text into large ASCII art banners.
**Target Platform**: Windows 11 x64 (Compatible with Windows 10/11 64-bit)
**Dependencies**: 100% Self-contained static binary (zero external DLL or runtime dependencies required).

## Files in Package
- `AsciiArtBanner.exe`: Standalone 64-bit Windows executable.
- `AsciiArtBannerInstaller.msi`: Standard Windows Installer MSI package.
- `AsciiArtBanner.c`: C source code.
- `AsciiArtBanner.wxs`: WiX source configuration for the MSI.

## How to Run the .exe
Open Command Prompt or PowerShell in this directory:
```cmd
AsciiArtBanner.exe
```

## How to Install via .msi
Run the installer directly or via msiexec:
```cmd
msiexec /i AsciiArtBannerInstaller.msi /quiet /qn
```
