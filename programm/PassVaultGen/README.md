# PassVaultGen

**Category**: Useful Apps
**Description**: Cryptographically secure password generator with customizable rules.
**Target Platform**: Windows 11 x64 (Compatible with Windows 10/11 64-bit)
**Dependencies**: 100% Self-contained static binary (zero external DLL or runtime dependencies required).

## Files in Package
- `PassVaultGen.exe`: Standalone 64-bit Windows executable.
- `PassVaultGenInstaller.msi`: Standard Windows Installer MSI package.
- `PassVaultGen.c`: C source code.
- `PassVaultGen.wxs`: WiX source configuration for the MSI.

## How to Run the .exe
Open Command Prompt or PowerShell in this directory:
```cmd
PassVaultGen.exe
```

## How to Install via .msi
Run the installer directly or via msiexec:
```cmd
msiexec /i PassVaultGenInstaller.msi /quiet /qn
```
