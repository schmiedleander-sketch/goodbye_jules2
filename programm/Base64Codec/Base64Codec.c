#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <wincrypt.h>

int main(int argc, char* argv[]) {
    printf("====================================================\n");
    printf("             WINDOWS BASE64 CODEC v1.0              \n");
    printf("====================================================\n\n");
    if (argc < 3) {
        printf("Usage:\n");
        printf("  Base64Codec.exe enc <text>\n");
        printf("  Base64Codec.exe dec <base64>\n");
        return 1;
    }
    if (strcmp(argv[1], "enc") == 0) {
        DWORD outLen = 0;
        CryptBinaryToStringA((const BYTE*)argv[2], strlen(argv[2]), CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF, NULL, &outLen);
        char* out = malloc(outLen + 1);
        CryptBinaryToStringA((const BYTE*)argv[2], strlen(argv[2]), CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF, out, &outLen);
        printf("Encoded: %s\n", out);
        free(out);
    } else if (strcmp(argv[1], "dec") == 0) {
        DWORD outLen = 0;
        CryptStringToBinaryA(argv[2], 0, CRYPT_STRING_BASE64, NULL, &outLen, NULL, NULL);
        BYTE* out = malloc(outLen + 1);
        CryptStringToBinaryA(argv[2], 0, CRYPT_STRING_BASE64, out, &outLen, NULL, NULL);
        out[outLen] = '\0';
        printf("Decoded: %s\n", (char*)out);
        free(out);
    }
    return 0;
}
