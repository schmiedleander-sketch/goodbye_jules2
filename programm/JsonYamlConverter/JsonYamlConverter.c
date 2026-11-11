#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void convert_json_to_yaml(const char* filepath) {
    FILE* fp = fopen(filepath, "r");
    if (!fp) {
        printf("Error opening %s\n", filepath);
        return;
    }
    printf("--- # YAML representation\n");
    int c;
    int indent = 0;
    int inString = 0;
    int isEscaped = 0;
    int afterColon = 0;
    int needIndent = 1;

    while ((c = fgetc(fp)) != EOF) {
        if (inString) {
            if (isEscaped) {
                putchar(c);
                isEscaped = 0;
            } else if (c == '\\') {
                isEscaped = 1;
                putchar(c);
            } else if (c == '"') {
                inString = 0;
                putchar(c);
            } else {
                putchar(c);
            }
            continue;
        }

        if (c == '"') {
            if (needIndent) {
                for (int i = 0; i < indent; i++) printf("  ");
                needIndent = 0;
            }
            inString = 1;
            putchar(c);
        } else if (c == '{' || c == '[') {
            if (!afterColon && !needIndent) printf("\n");
            indent++;
            afterColon = 0;
            needIndent = 1;
        } else if (c == '}' || c == ']') {
            if (indent > 0) indent--;
            afterColon = 0;
            needIndent = 1;
        } else if (c == ':') {
            printf(": ");
            afterColon = 1;
            needIndent = 0;
        } else if (c == ',') {
            printf("\n");
            afterColon = 0;
            needIndent = 1;
        } else if (!isspace(c)) {
            if (needIndent) {
                for (int i = 0; i < indent; i++) printf("  ");
                needIndent = 0;
            }
            putchar(c);
        }
    }
    printf("\n");
    fclose(fp);
}

int validate_json(const char* filepath) {
    FILE* fp = fopen(filepath, "r");
    if (!fp) {
        printf("Error: Could not open file %s\n", filepath);
        return 1;
    }
    int braces = 0, brackets = 0, inString = 0, isEscaped = 0;
    int c;
    while ((c = fgetc(fp)) != EOF) {
        if (inString) {
            if (isEscaped) {
                isEscaped = 0;
            } else if (c == '\\') {
                isEscaped = 1;
            } else if (c == '"') {
                inString = 0;
            }
            continue;
        }

        if (c == '"') {
            inString = 1;
        } else if (c == '{') braces++;
        else if (c == '}') braces--;
        else if (c == '[') brackets++;
        else if (c == ']') brackets--;
    }
    fclose(fp);
    if (braces == 0 && brackets == 0 && !inString) {
        printf("VALIDATION PASSED: '%s' has perfectly balanced JSON syntax.\n", filepath);
        return 0;
    } else {
        printf("VALIDATION FAILED: Unbalanced syntax in '%s' (Brace balance: %d, Bracket balance: %d)\n", filepath, braces, brackets);
        return 2;
    }
}

int main(int argc, char* argv[]) {
    printf("====================================================\n");
    printf("        WINDOWS JSON-YAML CONVERTER & INSPECTOR      \n");
    printf("====================================================\n\n");
    if (argc < 2) {
        printf("Usage:\n");
        printf("  JsonYamlConverter.exe validate <filePath>\n");
        printf("  JsonYamlConverter.exe to-yaml <filePath>\n");
        return 1;
    }
    if (strcmp(argv[1], "to-yaml") == 0) {
        if (argc < 3) { printf("Missing file argument.\n"); return 1; }
        convert_json_to_yaml(argv[2]);
        return 0;
    } else if (strcmp(argv[1], "validate") == 0) {
        if (argc < 3) { printf("Missing file argument.\n"); return 1; }
        return validate_json(argv[2]);
    } else {
        return validate_json(argv[1]);
    }
}
