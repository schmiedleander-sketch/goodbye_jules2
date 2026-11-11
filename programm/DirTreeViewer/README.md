# DirTreeViewer

**Category**: File Tools
**Description**: Visual directory hierarchy generator with file sizes.
**Target Platform**: Windows 11 x64 (Compatible with Windows 10/11 64-bit)
**Dependencies**: 100% Self-contained static binary (zero external DLL or runtime dependencies required).

## Files in Package
- `DirTreeViewer.exe`: Standalone 64-bit Windows executable.
- `DirTreeViewerInstaller.msi`: Standard Windows Installer MSI package.
- `DirTreeViewer.c`: C source code.
- `DirTreeViewer.wxs`: WiX source configuration for the MSI.

## How to Run the .exe
Open Command Prompt or PowerShell in this directory:
```cmd
DirTreeViewer.exe
```

## How to Install via .msi
Run the installer directly or via msiexec:
```cmd
msiexec /i DirTreeViewerInstaller.msi /quiet /qn
```
