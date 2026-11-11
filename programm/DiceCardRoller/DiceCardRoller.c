#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(int argc, char* argv[]) {
    printf("====================================================\n");
    printf("         WINDOWS DICE & CARD SIMULATOR v1.0         \n");
    printf("====================================================\n\n");
    srand((unsigned int)time(NULL));

    if (argc < 2 || strcmp(argv[1], "roll") == 0) {
        int count = (argc > 2) ? atoi(argv[2]) : 2;
        int sides = (argc > 3) ? atoi(argv[3]) : 6;
        if (count < 1) count = 1;
        if (sides < 2) sides = 6;
        printf("Rolling %dd%d:\n[ ", count, sides);
        int total = 0;
        for (int i = 0; i < count; i++) {
            int roll = (rand() % sides) + 1;
            printf("%d ", roll);
            total += roll;
        }
        printf("] Total: %d\n", total);
    } else if (strcmp(argv[1], "deal") == 0) {
        const char* suits[] = { "Spades", "Hearts", "Diamonds", "Clubs" };
        const char* ranks[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace" };
        int count = (argc > 2) ? atoi(argv[2]) : 5;
        printf("Dealing %d cards:\n", count);
        for (int i = 0; i < count; i++) {
            printf("  %d. %s of %s\n", i + 1, ranks[rand() % 13], suits[rand() % 4]);
        }
    }
    return 0;
}
