#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <wincrypt.h>

int main(int argc, char* argv[]) {
    printf("====================================================\n");
    printf("        WINDOWS PASSWORD VAULT GENERATOR v1.0       \n");
    printf("====================================================\n\n");
    int len = (argc > 1) ? atoi(argv[1]) : 16;
    int count = (argc > 2) ? atoi(argv[2]) : 5;
    if (len < 6) len = 16;
    if (count < 1) count = 1;

    const char* chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_=+";
    int charCount = strlen(chars);

    HCRYPTPROV hProv;
    if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
        printf("Error acquiring crypto context.\n");
        return 1;
    }

    printf("Generating %d secure passwords of length %d:\n\n", count, len);
    for (int i = 1; i <= count; i++) {
        printf("[%02d] ", i);
        for (int j = 0; j < len; j++) {
            BYTE b;
            CryptGenRandom(hProv, 1, &b);
            putchar(chars[b % charCount]);
        }
        printf("\n");
    }
    CryptReleaseContext(hProv, 0);
    return 0;
}
