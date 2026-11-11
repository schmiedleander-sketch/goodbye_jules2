#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <wincrypt.h>

int main(int argc, char* argv[]) {
    printf("====================================================\n");
    printf("           WINDOWS FILE SHREDDER v1.0               \n");
    printf("====================================================\n\n");
    if (argc < 2) {
        printf("Usage: FileShredder.exe <filePath> [passes]\n");
        printf("Example: FileShredder.exe sensitive.txt 3\n");
        return 1;
    }
    int passes = (argc > 2) ? atoi(argv[2]) : 3;
    if (passes < 1) passes = 3;
    HANDLE hFile = CreateFileA(argv[1], GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        printf("Failed to open file: %s\n", argv[1]);
        return 1;
    }
    LARGE_INTEGER size;
    GetFileSizeEx(hFile, &size);
    printf("Shredding %s (%lld bytes) across %d passes...\n", argv[1], (long long)size.QuadPart, passes);
    BYTE buffer[65536];
    for (int p = 1; p <= passes; p++) {
        SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
        LONGLONG remaining = size.QuadPart;
        printf("Pass %d/%d...", p, passes);
        while (remaining > 0) {
            DWORD toWrite = (remaining > (LONGLONG)sizeof(buffer)) ? (DWORD)sizeof(buffer) : (DWORD)remaining;
            memset(buffer, (p % 2 == 1) ? 0x00 : 0xFF, toWrite);
            DWORD written = 0;
            WriteFile(hFile, buffer, toWrite, &written, NULL);
            remaining -= written;
        }
        FlushFileBuffers(hFile);
        printf(" OK\n");
    }
    CloseHandle(hFile);
    DeleteFileA(argv[1]);
    printf("File securely shredded and deleted.\n");
    return 0;
}
