#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct {
    char path[MAX_PATH];
    char name[MAX_PATH];
    LARGE_INTEGER size;
} FileEntry;

int compare_file_bytes(const char* f1, const char* f2) {
    FILE* p1 = fopen(f1, "rb");
    FILE* p2 = fopen(f2, "rb");
    if (!p1 || !p2) {
        if (p1) fclose(p1);
        if (p2) fclose(p2);
        return 0;
    }
    char b1[4096], b2[4096];
    int identical = 1;
    while (1) {
        size_t n1 = fread(b1, 1, sizeof(b1), p1);
        size_t n2 = fread(b2, 1, sizeof(b2), p2);
        if (n1 != n2) { identical = 0; break; }
        if (n1 == 0) break;
        if (memcmp(b1, b2, n1) != 0) { identical = 0; break; }
    }
    fclose(p1);
    fclose(p2);
    return identical;
}

int main(int argc, char* argv[]) {
    printf("====================================================\n");
    printf("         WINDOWS DUPLICATE FILE FINDER v1.0         \n");
    printf("====================================================\n\n");
    const char* dir = (argc > 1) ? argv[1] : ".";
    char searchPath[MAX_PATH];
    snprintf(searchPath, sizeof(searchPath), "%s\\*.*", dir);
    WIN32_FIND_DATAA fd;
    HANDLE hFind = FindFirstFileA(searchPath, &fd);
    if (hFind == INVALID_HANDLE_VALUE) {
        printf("Cannot access directory: %s\n", dir);
        return 1;
    }
    FileEntry entries[500];
    int count = 0;
    do {
        if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && count < 500) {
            snprintf(entries[count].path, MAX_PATH, "%s\\%s", dir, fd.cFileName);
            strncpy(entries[count].name, fd.cFileName, MAX_PATH);
            entries[count].size.LowPart = fd.nFileSizeLow;
            entries[count].size.HighPart = fd.nFileSizeHigh;
            count++;
        }
    } while (FindNextFileA(hFind, &fd));
    FindClose(hFind);

    printf("Scanned %d files. Verifying identical byte content...\n\n", count);
    int dupes = 0;
    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            if (entries[i].size.QuadPart == entries[j].size.QuadPart && entries[i].size.QuadPart > 0) {
                if (compare_file_bytes(entries[i].path, entries[j].path)) {
                    printf("[VERIFIED DUPLICATE: %lld bytes matching byte-for-byte]\n", (long long)entries[i].size.QuadPart);
                    printf("  Original : %s\n", entries[i].name);
                    printf("  Duplicate: %s\n\n", entries[j].name);
                    dupes++;
                }
            }
        }
    }
    if (dupes == 0) printf("No duplicate file content detected.\n");
    else printf("Found %d verified duplicate match(es).\n", dupes);
    return 0;
}
