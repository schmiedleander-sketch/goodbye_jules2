# TriviaQuiz

**Category**: Fun Apps
**Description**: Interactive computer and Windows architecture trivia game.
**Target Platform**: Windows 11 x64 (Compatible with Windows 10/11 64-bit)
**Dependencies**: 100% Self-contained static binary (zero external DLL or runtime dependencies required).

## Files in Package
- `TriviaQuiz.exe`: Standalone 64-bit Windows executable.
- `TriviaQuizInstaller.msi`: Standard Windows Installer MSI package.
- `TriviaQuiz.c`: C source code.
- `TriviaQuiz.wxs`: WiX source configuration for the MSI.

## How to Run the .exe
Open Command Prompt or PowerShell in this directory:
```cmd
TriviaQuiz.exe
```

## How to Install via .msi
Run the installer directly or via msiexec:
```cmd
msiexec /i TriviaQuizInstaller.msi /quiet /qn
```
