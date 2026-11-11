# SysInfoViewer

**Category**: Useful Apps
**Description**: Displays CPU, memory, OS version, disk drives, and system parameters.
**Target Platform**: Windows 11 x64 (Compatible with Windows 10/11 64-bit)
**Dependencies**: 100% Self-contained static binary (zero external DLL or runtime dependencies required).

## Files in Package
- `SysInfoViewer.exe`: Standalone 64-bit Windows executable.
- `SysInfoViewerInstaller.msi`: Standard Windows Installer MSI package.
- `SysInfoViewer.c`: C source code.
- `SysInfoViewer.wxs`: WiX source configuration for the MSI.

## How to Run the .exe
Open Command Prompt or PowerShell in this directory:
```cmd
SysInfoViewer.exe
```

## How to Install via .msi
Run the installer directly or via msiexec:
```cmd
msiexec /i SysInfoViewerInstaller.msi /quiet /qn
```
