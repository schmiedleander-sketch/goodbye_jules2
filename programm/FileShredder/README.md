# FileShredder

**Category**: File Tools
**Description**: Securely shreds files by multi-pass cryptographic data overwriting.
**Target Platform**: Windows 11 x64 (Compatible with Windows 10/11 64-bit)
**Dependencies**: 100% Self-contained static binary (zero external DLL or runtime dependencies required).

## Files in Package
- `FileShredder.exe`: Standalone 64-bit Windows executable.
- `FileShredderInstaller.msi`: Standard Windows Installer MSI package.
- `FileShredder.c`: C source code.
- `FileShredder.wxs`: WiX source configuration for the MSI.

## How to Run the .exe
Open Command Prompt or PowerShell in this directory:
```cmd
FileShredder.exe
```

## How to Install via .msi
Run the installer directly or via msiexec:
```cmd
msiexec /i FileShredderInstaller.msi /quiet /qn
```
