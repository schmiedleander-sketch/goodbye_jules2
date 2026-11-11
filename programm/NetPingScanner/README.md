# NetPingScanner

**Category**: Useful Apps
**Description**: TCP/ICMP network latency tester and availability scanner.
**Target Platform**: Windows 11 x64 (Compatible with Windows 10/11 64-bit)
**Dependencies**: 100% Self-contained static binary (zero external DLL or runtime dependencies required).

## Files in Package
- `NetPingScanner.exe`: Standalone 64-bit Windows executable.
- `NetPingScannerInstaller.msi`: Standard Windows Installer MSI package.
- `NetPingScanner.c`: C source code.
- `NetPingScanner.wxs`: WiX source configuration for the MSI.

## How to Run the .exe
Open Command Prompt or PowerShell in this directory:
```cmd
NetPingScanner.exe
```

## How to Install via .msi
Run the installer directly or via msiexec:
```cmd
msiexec /i NetPingScannerInstaller.msi /quiet /qn
```
