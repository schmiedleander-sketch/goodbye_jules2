# HangmanGame

**Category**: Fun Apps
**Description**: Word-guessing terminal game with ASCII gallows.
**Target Platform**: Windows 11 x64 (Compatible with Windows 10/11 64-bit)
**Dependencies**: 100% Self-contained static binary (zero external DLL or runtime dependencies required).

## Files in Package
- `HangmanGame.exe`: Standalone 64-bit Windows executable.
- `HangmanGameInstaller.msi`: Standard Windows Installer MSI package.
- `HangmanGame.c`: C source code.
- `HangmanGame.wxs`: WiX source configuration for the MSI.

## How to Run the .exe
Open Command Prompt or PowerShell in this directory:
```cmd
HangmanGame.exe
```

## How to Install via .msi
Run the installer directly or via msiexec:
```cmd
msiexec /i HangmanGameInstaller.msi /quiet /qn
```
