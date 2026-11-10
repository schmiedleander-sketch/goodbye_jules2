<#
.SYNOPSIS
    Builds the MSI Windows Installer for the entire 20-app suite using WiX Toolset.
#>
param(
    [string]$Configuration = "Release",
    [string]$SourceDir = "$PSScriptRoot/../artifacts/publish",
    [string]$OutputDir = "$PSScriptRoot/../artifacts/installer"
)

$ErrorActionPreference = "Stop"

Write-Host "Building Windows Installer (.msi)..." -ForegroundColor Cyan

if (-not (Test-Path $OutputDir)) {
    New-Item -ItemType Directory -Path $OutputDir -Force | Out-Null
}

# 1. Verify published .exe binaries exist, or run publish-all.ps1
if (-not (Test-Path "$SourceDir/TaskManagerPlus/TaskManagerPlus.exe")) {
    Write-Host "Publishing applications first..." -ForegroundColor Yellow
    & "$PSScriptRoot/../publish-all.ps1" -Configuration $Configuration -OutputDir $SourceDir
}

# 2. Invoke WiX Toolset compiler (candle) and linker (light)
$wixCandle = "candle.exe"
$wixLight = "light.exe"

$wxsFile = "$PSScriptRoot/Product.wxs"
$wixObj = "$OutputDir/Product.wixobj"
$msiOut = "$OutputDir/WindowsAppSDKSuiteSetup.msi"

Write-Host "Compiling WiX definitions..." -ForegroundColor Yellow
& $wixCandle -dSourceDir="$SourceDir" -out "$wixObj" "$wxsFile"

Write-Host "Linking MSI package..." -ForegroundColor Yellow
& $wixLight -out "$msiOut" "$wixObj" -sval

Write-Host "`n MSI Package successfully built: $msiOut" -ForegroundColor Green
