# JsonYamlConverter

**Category**: Useful Apps
**Description**: Validates, inspects, and pretty prints JSON key-value data.
**Target Platform**: Windows 11 x64 (Compatible with Windows 10/11 64-bit)
**Dependencies**: 100% Self-contained static binary (zero external DLL or runtime dependencies required).

## Files in Package
- `JsonYamlConverter.exe`: Standalone 64-bit Windows executable.
- `JsonYamlConverterInstaller.msi`: Standard Windows Installer MSI package.
- `JsonYamlConverter.c`: C source code.
- `JsonYamlConverter.wxs`: WiX source configuration for the MSI.

## How to Run the .exe
Open Command Prompt or PowerShell in this directory:
```cmd
JsonYamlConverter.exe
```

## How to Install via .msi
Run the installer directly or via msiexec:
```cmd
msiexec /i JsonYamlConverterInstaller.msi /quiet /qn
```
