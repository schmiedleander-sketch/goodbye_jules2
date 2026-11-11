# PortScanner

**Category**: Useful Apps
**Description**: Fast TCP port scanner testing network connectivity and service ports.
**Target Platform**: Windows 11 x64 (Compatible with Windows 10/11 64-bit)
**Dependencies**: 100% Self-contained static binary (zero external DLL or runtime dependencies required).

## Files in Package
- `PortScanner.exe`: Standalone 64-bit Windows executable.
- `PortScannerInstaller.msi`: Standard Windows Installer MSI package.
- `PortScanner.c`: C source code.
- `PortScanner.wxs`: WiX source configuration for the MSI.

## How to Run the .exe
Open Command Prompt or PowerShell in this directory:
```cmd
PortScanner.exe
```

## How to Install via .msi
Run the installer directly or via msiexec:
```cmd
msiexec /i PortScannerInstaller.msi /quiet /qn
```
