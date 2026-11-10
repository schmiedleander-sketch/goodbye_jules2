<#
.SYNOPSIS
    Compiles and publishes all 20 Windows App SDK applications into standalone / unpackaged Windows executables (.exe).
.DESCRIPTION
    Iterates through all 20 projects, restoring NuGet packages and invoking dotnet publish
    for win-x64, producing ready-to-run .exe files in the release distribution directory.
#>

param(
    [string]$Configuration = "Release",
    [string]$Runtime = "win-x64",
    [string]$OutputDir = "$PSScriptRoot/artifacts/publish"
)

$ErrorActionPreference = "Stop"
Write-Host "==========================================================" -ForegroundColor Cyan
Write-Host " Building & Publishing 20 Windows App SDK Applications     " -ForegroundColor Cyan
Write-Host " Target Runtime: $Runtime | Configuration: $Configuration  " -ForegroundColor Cyan
Write-Host " Output Directory: $OutputDir                              " -ForegroundColor Cyan
Write-Host "==========================================================" -ForegroundColor Cyan

$projects = Get-ChildItem -Path "$PSScriptRoot/apps" -Recurse -Filter "*.csproj"

$counter = 1
foreach ($proj in $projects) {
    $appName = [System.IO.Path]::GetFileNameWithoutExtension($proj.Name)
    $targetDir = Join-Path $OutputDir $appName

    Write-Host "`n[$counter/20] Publishing $appName to .exe..." -ForegroundColor Yellow

    dotnet publish $proj.FullName `
        -c $Configuration `
        -r $Runtime `
        --self-contained true `
        /p:PublishSingleFile=true `
        /p:IncludeNativeLibrariesForSelfExtract=true `
        /p:WindowsPackageType=None `
        -o $targetDir

    if ($LASTEXITCODE -eq 0) {
        Write-Host " -> Successfully generated $appName.exe in $targetDir" -ForegroundColor Green
    } else {
        Write-Error " -> Failed to publish $appName"
    }
    $counter++
}

Write-Host "`n==========================================================" -ForegroundColor Cyan
Write-Host " All 20 application .exe binaries generated successfully!  " -ForegroundColor Green
Write-Host " Executable binaries located in: $OutputDir                " -ForegroundColor Green
Write-Host "==========================================================" -ForegroundColor Cyan
