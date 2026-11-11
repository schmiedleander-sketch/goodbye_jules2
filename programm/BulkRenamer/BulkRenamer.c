#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int main(int argc, char* argv[]) {
    printf("====================================================\n");
    printf("            WINDOWS BULK RENAMER v1.0               \n");
    printf("====================================================\n\n");
    if (argc < 3) {
        printf("Usage: BulkRenamer.exe <directory> <prefix>\n");
        printf("Example: BulkRenamer.exe C:\\Photos Doc_\n");
        return 1;
    }
    char searchPath[MAX_PATH];
    snprintf(searchPath, sizeof(searchPath), "%s\\*.*", argv[1]);
    WIN32_FIND_DATAA fd;
    HANDLE hFind = FindFirstFileA(searchPath, &fd);
    if (hFind == INVALID_HANDLE_VALUE) {
        printf("No files found or invalid directory: %s\n", argv[1]);
        return 1;
    }
    int count = 0;
    do {
        if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            char oldPath[MAX_PATH], newPath[MAX_PATH];
            snprintf(oldPath, sizeof(oldPath), "%s\\%s", argv[1], fd.cFileName);
            snprintf(newPath, sizeof(newPath), "%s\\%s%s", argv[1], argv[2], fd.cFileName);
            if (MoveFileA(oldPath, newPath)) {
                printf("Renamed: %s -> %s%s\n", fd.cFileName, argv[2], fd.cFileName);
                count++;
            }
        }
    } while (FindNextFileA(hFind, &fd));
    FindClose(hFind);
    printf("\nTotal files renamed: %d\n", count);
    return 0;
}
