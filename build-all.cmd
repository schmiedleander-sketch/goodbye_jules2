@echo off
setlocal enabledelayedexpansion

echo ==========================================================
echo  Building and Publishing 20 Windows App SDK Applications (.exe)
echo ==========================================================

set CONFIG=Release
set RUNTIME=win-x64
set OUTDIR=%~dp0artifacts\publish

powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0publish-all.ps1" -Configuration %CONFIG% -Runtime %RUNTIME% -OutputDir "%OUTDIR%"

echo.
echo All .exe files generated in %OUTDIR%
