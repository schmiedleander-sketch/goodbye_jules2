#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>

int main(int argc, char* argv[]) {
    printf("====================================================\n");
    printf("             WINDOWS TCP PORT SCANNER v1.0          \n");
    printf("====================================================\n\n");
    const char* host = (argc > 1) ? argv[1] : "127.0.0.1";
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    int ports[] = { 21, 22, 23, 25, 53, 80, 110, 135, 139, 443, 445, 1433, 3306, 3389, 8080 };
    int nPorts = sizeof(ports) / sizeof(ports[0]);
    printf("Scanning %s across %d common ports...\n\n", host, nPorts);

    int openPorts = 0;
    for (int i = 0; i < nPorts; i++) {
        SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(ports[i]);
        addr.sin_addr.s_addr = inet_addr(host);

        DWORD timeout = 250;
        setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
        setsockopt(s, SOL_SOCKET, SO_SNDTIMEO, (const char*)&timeout, sizeof(timeout));

        if (connect(s, (struct sockaddr*)&addr, sizeof(addr)) == 0) {
            printf("[OPEN]  Port %5d\n", ports[i]);
            openPorts++;
        }
        closesocket(s);
    }
    WSACleanup();
    printf("\nScan complete. Open ports detected: %d\n", openPorts);
    return 0;
}
