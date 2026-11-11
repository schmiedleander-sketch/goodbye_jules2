#include <stdio.h>
#include <string.h>

int main() {
    printf("====================================================\n");
    printf("             WINDOWS ARCHITECTURE TRIVIA v1.0       \n");
    printf("====================================================\n\n");

    int score = 0;
    printf("Q1: What executable format is standard on 64-bit Windows?\n");
    printf("  [1] ELF\n  [2] PE32+\n  [3] Mach-O\nAnswer (1-3): ");
    int a1 = 0;
    if (scanf("%d", &a1) == 1 && a1 == 2) { printf("Correct!\n\n"); score++; } else printf("Incorrect! (Ans: 2)\n\n");

    printf("Q2: What is the primary installation file format for Windows Installer?\n");
    printf("  [1] RPM\n  [2] DEB\n  [3] MSI\nAnswer (1-3): ");
    int a2 = 0;
    if (scanf("%d", &a2) == 1 && a2 == 3) { printf("Correct!\n\n"); score++; } else printf("Incorrect! (Ans: 3)\n\n");

    printf("Q3: In binary computation, 1 Gigabyte equals how many Megabytes?\n");
    printf("  [1] 1000\n  [2] 1024\n  [3] 2048\nAnswer (1-3): ");
    int a3 = 0;
    if (scanf("%d", &a3) == 1 && a3 == 2) { printf("Correct!\n\n"); score++; } else printf("Incorrect! (Ans: 2)\n\n");

    printf("Final Score: %d / 3\n", score);
    return 0;
}
