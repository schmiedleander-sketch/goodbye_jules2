#include <stdio.h>
#include <windows.h>

int main() {
    printf("====================================================\n");
    printf("          WINDOWS SYSTEM INFO VIEWER v1.0           \n");
    printf("====================================================\n\n");

    SYSTEM_INFO si;
    GetNativeSystemInfo(&si);
    printf("[CPU & HARDWARE]\n");
    printf("Processor Architecture: %s\n", (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64) ? "x64 (AMD64)" : "Other");
    printf("Number of Processors  : %u\n", si.dwNumberOfProcessors);
    printf("Page Size             : %u bytes\n\n", si.dwPageSize);

    MEMORYSTATUSEX mem;
    mem.dwLength = sizeof(mem);
    if (GlobalMemoryStatusEx(&mem)) {
        printf("[MEMORY METRICS]\n");
        printf("Memory Load        : %ld%%\n", mem.dwMemoryLoad);
        printf("Total Physical RAM : %lld MB\n", (long long)(mem.ullTotalPhys / (1024 * 1024)));
        printf("Avail Physical RAM : %lld MB\n", (long long)(mem.ullAvailPhys / (1024 * 1024)));
        printf("Total Page File    : %lld MB\n\n", (long long)(mem.ullTotalPageFile / (1024 * 1024)));
    }

    char compName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD compLen = sizeof(compName);
    if (GetComputerNameA(compName, &compLen)) printf("Computer Name : %s\n", compName);

    char userName[256];
    DWORD userLen = sizeof(userName);
    if (GetUserNameA(userName, &userLen)) printf("Current User  : %s\n", userName);

    return 0;
}
