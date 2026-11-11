#include <stdio.h>
#include <string.h>

int main() {
    printf("====================================================\n");
    printf("         DUNGEONS OF WIN11: TEXT ADVENTURE          \n");
    printf("====================================================\n\n");
    printf("You stand before the ancient Crystal Caverns.\n");
    printf("Paths branch: [1] North into Armory, [2] East into Shrine, [3] Exit\n\n");

    int room = 1;
    int hasKey = 0;
    while (1) {
        if (room == 1) {
            printf("[Cavern Gate] Options: [north] [east] [quit] > ");
        } else if (room == 2) {
            printf("[Armory] You see a Golden Key! Options: [take key] [south] > ");
        } else if (room == 3) {
            printf("[Sanctum] A locked diamond door stands here. Options: [unlock] [west] > ");
        }
        char cmd[64];
        if (!fgets(cmd, sizeof(cmd), stdin)) break;
        cmd[strcspn(cmd, "\r\n")] = 0;

        if (strcmp(cmd, "quit") == 0) break;
        if (room == 1 && strcmp(cmd, "north") == 0) room = 2;
        else if (room == 1 && strcmp(cmd, "east") == 0) room = 3;
        else if (room == 2 && strcmp(cmd, "take key") == 0) { printf("Key acquired!\n"); hasKey = 1; }
        else if (room == 2 && strcmp(cmd, "south") == 0) room = 1;
        else if (room == 3 && strcmp(cmd, "west") == 0) room = 1;
        else if (room == 3 && strcmp(cmd, "unlock") == 0) {
            if (hasKey) {
                printf("\n*** CONGRATULATIONS! The portal opens and you escape victorious! ***\n");
                break;
            } else {
                printf("The door is locked tight. Find the key!\n");
            }
        } else {
            printf("Invalid command.\n");
        }
    }
    return 0;
}
