#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    printf("====================================================\n");
    printf("             WINDOWS HANGMAN GAME v1.0              \n");
    printf("====================================================\n\n");
    const char secret[] = "MICROSOFT";
    int len = strlen(secret);
    char guessed[32];
    memset(guessed, '_', len);
    guessed[len] = '\0';

    int lives = 6;
    while (lives > 0) {
        printf("Word: ");
        for (int i = 0; i < len; i++) printf("%c ", guessed[i]);
        printf(" (Lives: %d)\nGuess a letter: ", lives);

        char guess;
        if (scanf(" %c", &guess) != 1) break;
        guess = toupper(guess);

        int found = 0;
        for (int i = 0; i < len; i++) {
            if (secret[i] == guess) { guessed[i] = guess; found = 1; }
        }

        if (found) {
            printf("Good guess!\n\n");
            if (strcmp(guessed, secret) == 0) {
                printf("YOU WIN! The secret word was: %s\n", secret);
                return 0;
            }
        } else {
            lives--;
            printf("Wrong guess! Lives remaining: %d\n\n", lives);
        }
    }
    printf("GAME OVER! Secret word was: %s\n", secret);
    return 0;
}
