# Base64Codec

**Category**: Useful Apps
**Description**: Encodes and decodes text strings and binary buffers to Base64.
**Target Platform**: Windows 11 x64 (Compatible with Windows 10/11 64-bit)
**Dependencies**: 100% Self-contained static binary (zero external DLL or runtime dependencies required).

## Files in Package
- `Base64Codec.exe`: Standalone 64-bit Windows executable.
- `Base64CodecInstaller.msi`: Standard Windows Installer MSI package.
- `Base64Codec.c`: C source code.
- `Base64Codec.wxs`: WiX source configuration for the MSI.

## How to Run the .exe
Open Command Prompt or PowerShell in this directory:
```cmd
Base64Codec.exe
```

## How to Install via .msi
Run the installer directly or via msiexec:
```cmd
msiexec /i Base64CodecInstaller.msi /quiet /qn
```
