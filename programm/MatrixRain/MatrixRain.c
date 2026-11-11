#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(int argc, char* argv[]) {
    int frames = (argc > 1) ? atoi(argv[1]) : 100;
    const char chars[] = "abcdef0123456789@#$%&*";
    int nChars = sizeof(chars) - 1;
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

    printf("Starting Matrix Code Stream (%d frames)...\n\n", frames);
    for (int f = 0; f < frames; f++) {
        char line[81];
        for (int x = 0; x < 80; x++) {
            line[x] = (rand() % 4 == 0) ? chars[rand() % nChars] : ' ';
        }
        line[80] = '\0';
        printf("%s\n", line);
        Sleep(50);
    }
    SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    return 0;
}
