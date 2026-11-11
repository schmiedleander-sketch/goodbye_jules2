# TextGrep

**Category**: File Tools
**Description**: High-speed text search across files with line numbering.
**Target Platform**: Windows 11 x64 (Compatible with Windows 10/11 64-bit)
**Dependencies**: 100% Self-contained static binary (zero external DLL or runtime dependencies required).

## Files in Package
- `TextGrep.exe`: Standalone 64-bit Windows executable.
- `TextGrepInstaller.msi`: Standard Windows Installer MSI package.
- `TextGrep.c`: C source code.
- `TextGrep.wxs`: WiX source configuration for the MSI.

## How to Run the .exe
Open Command Prompt or PowerShell in this directory:
```cmd
TextGrep.exe
```

## How to Install via .msi
Run the installer directly or via msiexec:
```cmd
msiexec /i TextGrepInstaller.msi /quiet /qn
```
