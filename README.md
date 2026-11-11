# Windows 11 x64 Suite - 20 Unique Working Programs

A collection of 20 fully functional, non-malware Windows programs compiled for **Windows 11 x64** (compatible with Windows 10/11 64-bit).

All programs are **100% self-contained**: all dependencies are statically included directly within each application folder, requiring no external runtimes or framework installations.

Each program is provided with:
1. Native 64-bit Windows Executable (`.exe`)
2. Genuine Windows Installer Package (`.msi`)
3. Full C source code (`.c`)
4. WiX Installer configuration (`.wxs`)
5. Detailed documentation (`README.md`)

---

## Catalog of Programs

### Category 1: File Tools
1. **FileHasher** (`/programm/FileHasher/`)
   - Computes cryptographic file checksums (MD5, SHA-1, SHA-256) using Windows CryptoAPI.
   - Files: `FileHasher.exe`, `FileHasherInstaller.msi`

2. **BulkRenamer** (`/programm/BulkRenamer/`)
   - High-throughput batch file rename utility with customizable prefixes and directory traversal.
   - Files: `BulkRenamer.exe`, `BulkRenamerInstaller.msi`

3. **FileShredder** (`/programm/FileShredder/`)
   - Secure data destruction utility that performs multi-pass overwrites (zeroes, ones, patterns) before deletion.
   - Files: `FileShredder.exe`, `FileShredderInstaller.msi`

4. **DuplicateFinder** (`/programm/DuplicateFinder/`)
   - Scans directories and detects identical files based on size matching and verification.
   - Files: `DuplicateFinder.exe`, `DuplicateFinderInstaller.msi`

5. **TextGrep** (`/programm/TextGrep/`)
   - Fast pattern search across text files with match count and line-number reporting.
   - Files: `TextGrep.exe`, `TextGrepInstaller.msi`

6. **DirTreeViewer** (`/programm/DirTreeViewer/`)
   - Visual directory tree generator displaying hierarchical directory layouts and file sizes.
   - Files: `DirTreeViewer.exe`, `DirTreeViewerInstaller.msi`

7. **FileSplitJoin** (`/programm/FileSplitJoin/`)
   - Splits large files into smaller numbered chunks and rejoins them seamlessly.
   - Files: `FileSplitJoin.exe`, `FileSplitJoinInstaller.msi`

---

### Category 2: Useful Productivity & System Apps
8. **SysInfoViewer** (`/programm/SysInfoViewer/`)
   - Comprehensive Windows system metrics: CPU architecture, processor count, RAM status, computer name, and active user.
   - Files: `SysInfoViewer.exe`, `SysInfoViewerInstaller.msi`

9. **NetPingScanner** (`/programm/NetPingScanner/`)
   - Windows ICMP ping scanner measuring packet round-trip time (RTT), latency, and TTL.
   - Files: `NetPingScanner.exe`, `NetPingScannerInstaller.msi`

10. **PassVaultGen** (`/programm/PassVaultGen/`)
    - Cryptographically secure random password generator utilizing `CryptGenRandom`.
    - Files: `PassVaultGen.exe`, `PassVaultGenInstaller.msi`

11. **JsonYamlConverter** (`/programm/JsonYamlConverter/`)
    - Structural syntax validator for JSON data, verifying balanced delimiters and structures.
    - Files: `JsonYamlConverter.exe`, `JsonYamlConverterInstaller.msi`

12. **Base64Codec** (`/programm/Base64Codec/`)
    - High-speed encoder and decoder for Base64 data strings using Windows Crypto API.
    - Files: `Base64Codec.exe`, `Base64CodecInstaller.msi`

13. **PortScanner** (`/programm/PortScanner/`)
    - TCP socket scanner checking common service ports (SSH, HTTP, HTTPS, SMB, RDP, MySQL, etc.).
    - Files: `PortScanner.exe`, `PortScannerInstaller.msi`

14. **UnitConverter** (`/programm/UnitConverter/`)
    - Conversion calculator supporting digital units (MB/GB), temperature (Celsius/Fahrenheit), length (km/miles), and weight.
    - Files: `UnitConverter.exe`, `UnitConverterInstaller.msi`

---

### Category 3: Fun Apps & Games
15. **AsciiArtBanner** (`/programm/AsciiArtBanner/`)
    - Renders text input into stylized ASCII art banners for consoles and headers.
    - Files: `AsciiArtBanner.exe`, `AsciiArtBannerInstaller.msi`

16. **TextAdventure** (`/programm/TextAdventure/`)
    - Interactive retro dungeon crawler RPG with room exploration, item collection, and puzzle solving.
    - Files: `TextAdventure.exe`, `TextAdventureInstaller.msi`

17. **TriviaQuiz** (`/programm/TriviaQuiz/`)
    - Interactive trivia challenge testing knowledge of Windows architectures, file formats, and computing history.
    - Files: `TriviaQuiz.exe`, `TriviaQuizInstaller.msi`

18. **HangmanGame** (`/programm/HangmanGame/`)
    - Classic word-guessing game featuring procedural ASCII gallows graphics and score tracking.
    - Files: `HangmanGame.exe`, `HangmanGameInstaller.msi`

19. **MatrixRain** (`/programm/MatrixRain/`)
    - Animated green digital stream screensaver in the terminal inspired by The Matrix.
    - Files: `MatrixRain.exe`, `MatrixRainInstaller.msi`

20. **DiceCardRoller** (`/programm/DiceCardRoller/`)
    - Tabletop multi-sided dice roller (d6, d20, etc.) and 52-card standard deck dealer/shuffler.
    - Files: `DiceCardRoller.exe`, `DiceCardRollerInstaller.msi`

---

## Installation & Execution

### Running the `.exe`
Navigate to any program directory and run the standalone executable:
```cmd
cd programm\FileHasher
FileHasher.exe C:\Windows\notepad.exe
```

### Installing via `.msi`
Install with standard Windows GUI or via command line:
```cmd
msiexec /i FileHasherInstaller.msi /quiet /qn
```
