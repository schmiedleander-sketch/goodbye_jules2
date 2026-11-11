#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void print_tree(const char* dir, int depth) {
    if (depth > 3) return;
    char searchPath[MAX_PATH];
    snprintf(searchPath, sizeof(searchPath), "%s\\*.*", dir);
    WIN32_FIND_DATAA fd;
    HANDLE hFind = FindFirstFileA(searchPath, &fd);
    if (hFind == INVALID_HANDLE_VALUE) return;
    do {
        if (strcmp(fd.cFileName, ".") == 0 || strcmp(fd.cFileName, "..") == 0) continue;
        for (int i = 0; i < depth; i++) printf("  ");
        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            printf("[DIR]  %s\n", fd.cFileName);
            char subDir[MAX_PATH];
            snprintf(subDir, sizeof(subDir), "%s\\%s", dir, fd.cFileName);
            print_tree(subDir, depth + 1);
        } else {
            LARGE_INTEGER sz;
            sz.LowPart = fd.nFileSizeLow;
            sz.HighPart = fd.nFileSizeHigh;
            printf("[FILE] %s (%lld bytes)\n", fd.cFileName, (long long)sz.QuadPart);
        }
    } while (FindNextFileA(hFind, &fd));
    FindClose(hFind);
}

int main(int argc, char* argv[]) {
    printf("====================================================\n");
    printf("          WINDOWS DIRECTORY TREE VIEWER v1.0        \n");
    printf("====================================================\n\n");
    const char* root = (argc > 1) ? argv[1] : ".";
    printf("Root: %s\n", root);
    print_tree(root, 0);
    return 0;
}
