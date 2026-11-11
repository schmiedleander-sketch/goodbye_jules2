import os
import subprocess
import uuid

programs = [
    ("FileHasher", "-lcrypt32"),
    ("BulkRenamer", ""),
    ("FileShredder", ""),
    ("DuplicateFinder", ""),
    ("TextGrep", ""),
    ("DirTreeViewer", ""),
    ("FileSplitJoin", ""),
    ("SysInfoViewer", "-ladvapi32"),
    ("NetPingScanner", "-liphlpapi -lws2_32"),
    ("PassVaultGen", "-ladvapi32"),
    ("JsonYamlConverter", ""),
    ("Base64Codec", "-lcrypt32"),
    ("PortScanner", "-lws2_32"),
    ("UnitConverter", ""),
    ("AsciiArtBanner", ""),
    ("TextAdventure", ""),
    ("TriviaQuiz", ""),
    ("HangmanGame", ""),
    ("MatrixRain", ""),
    ("DiceCardRoller", "")
]

base_dir = os.path.abspath("programm")

for name, libs in programs:
    app_dir = os.path.join(base_dir, name)
    c_file = os.path.join(app_dir, f"{name}.c")
    exe_file = os.path.join(app_dir, f"{name}.exe")
    wxs_file = os.path.join(app_dir, f"{name}.wxs")
    msi_file = os.path.join(app_dir, f"{name}Installer.msi")

    # Compile .exe if missing
    if not os.path.exists(exe_file):
        cmd = f"x86_64-w64-mingw32-gcc -O2 -s -static {c_file} -o {exe_file} {libs}"
        subprocess.check_call(cmd, shell=True)

    # Build .msi if missing
    if not os.path.exists(msi_file):
        subprocess.check_call(f"wixl -o {msi_file} {wxs_file}", shell=True)

print("All 20 programs compiled and packaged successfully.")
