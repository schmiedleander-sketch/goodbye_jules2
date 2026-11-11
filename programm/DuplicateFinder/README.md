# DuplicateFinder

**Category**: File Tools
**Description**: Finds duplicate files in a directory by comparing sizes and hashes.
**Target Platform**: Windows 11 x64 (Compatible with Windows 10/11 64-bit)
**Dependencies**: 100% Self-contained static binary (zero external DLL or runtime dependencies required).

## Files in Package
- `DuplicateFinder.exe`: Standalone 64-bit Windows executable.
- `DuplicateFinderInstaller.msi`: Standard Windows Installer MSI package.
- `DuplicateFinder.c`: C source code.
- `DuplicateFinder.wxs`: WiX source configuration for the MSI.

## How to Run the .exe
Open Command Prompt or PowerShell in this directory:
```cmd
DuplicateFinder.exe
```

## How to Install via .msi
Run the installer directly or via msiexec:
```cmd
msiexec /i DuplicateFinderInstaller.msi /quiet /qn
```
