# FileHasher

**Category**: File Tools
**Description**: Calculates cryptographic file hashes (MD5, SHA-256) and verifies checksums.
**Target Platform**: Windows 11 x64 (Compatible with Windows 10/11 64-bit)
**Dependencies**: 100% Self-contained static binary (zero external DLL or runtime dependencies required).

## Files in Package
- `FileHasher.exe`: Standalone 64-bit Windows executable.
- `FileHasherInstaller.msi`: Standard Windows Installer MSI package.
- `FileHasher.c`: C source code.
- `FileHasher.wxs`: WiX source configuration for the MSI.

## How to Run the .exe
Open Command Prompt or PowerShell in this directory:
```cmd
FileHasher.exe
```

## How to Install via .msi
Run the installer directly or via msiexec:
```cmd
msiexec /i FileHasherInstaller.msi /quiet /qn
```
