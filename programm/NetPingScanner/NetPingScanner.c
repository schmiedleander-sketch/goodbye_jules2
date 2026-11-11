#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <iphlpapi.h>
#include <icmpapi.h>

int main(int argc, char* argv[]) {
    printf("====================================================\n");
    printf("          WINDOWS NET PING SCANNER v1.0             \n");
    printf("====================================================\n\n");
    const char* ipStr = (argc > 1) ? argv[1] : "127.0.0.1";
    int count = (argc > 2) ? atoi(argv[2]) : 4;
    printf("Pinging %s with 32 bytes of test payload:\n\n", ipStr);

    HANDLE hIcmp = IcmpCreateFile();
    if (hIcmp == INVALID_HANDLE_VALUE) {
        printf("Unable to open ICMP handle.\n");
        return 1;
    }
    unsigned long ipAddr = inet_addr(ipStr);
    char sendData[] = "Win11PingEchoPayload123456789012";
    DWORD replySize = sizeof(ICMP_ECHO_REPLY) + sizeof(sendData) + 8;
    void* replyBuffer = malloc(replySize);

    int received = 0;
    for (int i = 1; i <= count; i++) {
        DWORD replies = IcmpSendEcho(hIcmp, ipAddr, sendData, sizeof(sendData), NULL, replyBuffer, replySize, 1000);
        if (replies != 0) {
            PICMP_ECHO_REPLY pEcho = (PICMP_ECHO_REPLY)replyBuffer;
            printf("Reply from %s: bytes=%d time=%ldms TTL=%d\n", ipStr, (int)sizeof(sendData), pEcho->RoundTripTime, pEcho->Options.Ttl);
            received++;
        } else {
            printf("Request timed out.\n");
        }
        Sleep(400);
    }
    free(replyBuffer);
    IcmpCloseHandle(hIcmp);
    printf("\nPing stats: %d sent, %d received.\n", count, received);
    return 0;
}
