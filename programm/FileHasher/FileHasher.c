#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <wincrypt.h>

void hash_file(const char* filepath, ALG_ID algId, const char* algName) {
    HANDLE hFile = CreateFileA(filepath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        printf("Error opening file: %s\n", filepath);
        return;
    }
    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;
    if (CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {
        if (CryptCreateHash(hProv, algId, 0, 0, &hHash)) {
            BYTE buffer[8192];
            DWORD bytesRead = 0;
            while (ReadFile(hFile, buffer, sizeof(buffer), &bytesRead, NULL) && bytesRead > 0) {
                CryptHashData(hHash, buffer, bytesRead, 0);
            }
            BYTE hash[64];
            DWORD hashLen = sizeof(hash);
            if (CryptGetHashParam(hHash, HP_HASHVAL, hash, &hashLen, 0)) {
                printf("%-8s: ", algName);
                for (DWORD i = 0; i < hashLen; i++) printf("%02x", hash[i]);
                printf("\n");
            }
            CryptDestroyHash(hHash);
        }
        CryptReleaseContext(hProv, 0);
    }
    CloseHandle(hFile);
}

int main(int argc, char* argv[]) {
    printf("====================================================\n");
    printf("            WINDOWS FILE HASHER v1.0                \n");
    printf("====================================================\n\n");
    if (argc < 2) {
        printf("Usage: FileHasher.exe <filePath>\n");
        printf("Example: FileHasher.exe C:\\path\\to\\file.dat\n");
        return 1;
    }
    printf("Target File: %s\n", argv[1]);
    hash_file(argv[1], CALG_MD5, "MD5");
    hash_file(argv[1], CALG_SHA1, "SHA1");
    hash_file(argv[1], CALG_SHA_256, "SHA256");
    printf("Completed.\n");
    return 0;
}
