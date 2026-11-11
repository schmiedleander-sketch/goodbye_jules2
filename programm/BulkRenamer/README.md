# BulkRenamer

**Category**: File Tools
**Description**: Batch rename files with prefixes, suffixes, and numbering patterns.
**Target Platform**: Windows 11 x64 (Compatible with Windows 10/11 64-bit)
**Dependencies**: 100% Self-contained static binary (zero external DLL or runtime dependencies required).

## Files in Package
- `BulkRenamer.exe`: Standalone 64-bit Windows executable.
- `BulkRenamerInstaller.msi`: Standard Windows Installer MSI package.
- `BulkRenamer.c`: C source code.
- `BulkRenamer.wxs`: WiX source configuration for the MSI.

## How to Run the .exe
Open Command Prompt or PowerShell in this directory:
```cmd
BulkRenamer.exe
```

## How to Install via .msi
Run the installer directly or via msiexec:
```cmd
msiexec /i BulkRenamerInstaller.msi /quiet /qn
```
