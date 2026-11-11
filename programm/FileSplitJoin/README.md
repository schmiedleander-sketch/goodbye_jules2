# FileSplitJoin

**Category**: File Tools
**Description**: Splits large files into chunks and rejoins them back.
**Target Platform**: Windows 11 x64 (Compatible with Windows 10/11 64-bit)
**Dependencies**: 100% Self-contained static binary (zero external DLL or runtime dependencies required).

## Files in Package
- `FileSplitJoin.exe`: Standalone 64-bit Windows executable.
- `FileSplitJoinInstaller.msi`: Standard Windows Installer MSI package.
- `FileSplitJoin.c`: C source code.
- `FileSplitJoin.wxs`: WiX source configuration for the MSI.

## How to Run the .exe
Open Command Prompt or PowerShell in this directory:
```cmd
FileSplitJoin.exe
```

## How to Install via .msi
Run the installer directly or via msiexec:
```cmd
msiexec /i FileSplitJoinInstaller.msi /quiet /qn
```
