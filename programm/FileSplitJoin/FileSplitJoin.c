#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int split_file(const char* filepath, long chunkSize) {
    FILE* src = fopen(filepath, "rb");
    if (!src) { printf("Failed to open %s\n", filepath); return 1; }
    char buffer[8192];
    int part = 1;
    while (!feof(src)) {
        char partName[512];
        snprintf(partName, sizeof(partName), "%s.part%03d", filepath, part);
        FILE* dst = fopen(partName, "wb");
        if (!dst) break;
        long written = 0;
        while (written < chunkSize && !feof(src)) {
            size_t toRead = (chunkSize - written > (long)sizeof(buffer)) ? sizeof(buffer) : (size_t)(chunkSize - written);
            size_t n = fread(buffer, 1, toRead, src);
            if (n == 0) break;
            fwrite(buffer, 1, n, dst);
            written += n;
        }
        fclose(dst);
        if (written == 0) { remove(partName); break; }
        printf("Created %s (%ld bytes)\n", partName, written);
        part++;
    }
    fclose(src);
    printf("Split completed: %d part(s) created.\n", part - 1);
    return 0;
}

int join_file(const char* firstPart, const char* outputFile) {
    char baseName[512];
    strncpy(baseName, firstPart, sizeof(baseName) - 1);
    baseName[sizeof(baseName) - 1] = '\0';

    char* ext = strstr(baseName, ".part");
    if (ext) *ext = '\0';

    FILE* dst = fopen(outputFile, "wb");
    if (!dst) {
        printf("Failed to create destination file: %s\n", outputFile);
        return 1;
    }

    char buffer[8192];
    int part = 1;
    long totalBytes = 0;

    while (1) {
        char currentPart[512];
        snprintf(currentPart, sizeof(currentPart), "%s.part%03d", baseName, part);
        FILE* src = fopen(currentPart, "rb");
        if (!src) break;

        printf("Joining %s...\n", currentPart);
        size_t n;
        while ((n = fread(buffer, 1, sizeof(buffer), src)) > 0) {
            fwrite(buffer, 1, n, dst);
            totalBytes += (long)n;
        }
        fclose(src);
        part++;
    }
    fclose(dst);

    if (part == 1) {
        printf("Error: No parts found starting at %s\n", firstPart);
        remove(outputFile);
        return 1;
    }

    printf("Joined %d part(s) into %s (%ld bytes total).\n", part - 1, outputFile, totalBytes);
    return 0;
}

int main(int argc, char* argv[]) {
    printf("====================================================\n");
    printf("          WINDOWS FILE SPLIT & JOIN v1.0            \n");
    printf("====================================================\n\n");
    if (argc < 3) {
        printf("Usage:\n");
        printf("  FileSplitJoin.exe split <filePath> [chunkBytes]\n");
        printf("  FileSplitJoin.exe join <firstPart> <outputFile>\n");
        return 1;
    }
    if (strcmp(argv[1], "split") == 0) {
        long sz = (argc > 3) ? atol(argv[3]) : (1024 * 1024);
        return split_file(argv[2], sz);
    } else if (strcmp(argv[1], "join") == 0) {
        if (argc < 4) {
            printf("Error: join requires <firstPart> <outputFile>\n");
            return 1;
        }
        return join_file(argv[2], argv[3]);
    }
    printf("Unknown command: %s\n", argv[1]);
    return 1;
}
