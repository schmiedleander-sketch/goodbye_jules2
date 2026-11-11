#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    printf("====================================================\n");
    printf("             WINDOWS TEXT GREP v1.0                 \n");
    printf("====================================================\n\n");
    if (argc < 3) {
        printf("Usage: TextGrep.exe <searchPattern> <filePath>\n");
        printf("Example: TextGrep.exe ERROR C:\\Logs\\app.log\n");
        return 1;
    }
    const char* pattern = argv[1];
    const char* filepath = argv[2];
    FILE* fp = fopen(filepath, "r");
    if (!fp) {
        printf("Cannot open file: %s\n", filepath);
        return 1;
    }
    char line[4096];
    int lineNum = 1;
    int matches = 0;
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, pattern)) {
            printf("[%d]: %s", lineNum, line);
            matches++;
        }
        lineNum++;
    }
    fclose(fp);
    printf("\nTotal occurrences of '%s': %d\n", pattern, matches);
    return 0;
}
