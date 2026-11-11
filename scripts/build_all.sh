#!/bin/bash
set -euo pipefail

echo "=========================================================="
echo " Building 20 Minecraft Dungeons 2 Mods & Loader (MinGW x64)"
echo "=========================================================="

CC=x86_64-w64-mingw32-gcc
CFLAGS="-O3 -Wall -Wextra -shared -I./include"

mkdir -p bin/mods dist

echo "Compiling mcd2_modloader.dll..."
$CC $CFLAGS src/mcd2_modloader.c -o bin/mcd2_modloader.dll

echo "Compiling 20 standalone mod DLLs..."
for mod_src in src/mods/*.c; do
    mod_name=$(basename "$mod_src" .c)
    echo "  -> Compiling bin/mods/${mod_name}.dll"
    $CC $CFLAGS "$mod_src" -o "bin/mods/${mod_name}.dll"
done

echo "Compiling mcd2_launcher.exe..."
$CC -O3 -Wall -Wextra -I./include src/mcd2_launcher.c -o bin/mcd2_launcher.exe -L./bin -lmcd2_modloader

echo "Compiling native test suite runner (Linux host binary for automated test verification)..."
gcc -O3 -Wall -Wextra tests/test_pe_dlls.c -o tests/test_pe_dlls

echo "Build complete! All 20 DLLs and binaries generated in bin/"
