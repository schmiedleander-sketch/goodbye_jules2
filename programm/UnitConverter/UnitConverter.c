#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    printf("====================================================\n");
    printf("          WINDOWS UNIVERSAL UNIT CONVERTER v1.0     \n");
    printf("====================================================\n\n");
    if (argc < 4) {
        printf("Usage: UnitConverter.exe <value> <fromUnit> <toUnit>\n");
        printf("Units: c/f (Temp), m/km/mi/ft (Length), kg/lb (Weight), mb/gb (Data)\n");
        printf("Example: UnitConverter.exe 100 c f\n");
        return 1;
    }
    double val = atof(argv[1]);
    const char* from = argv[2];
    const char* to = argv[3];

    if (strcmp(from, "c") == 0 && strcmp(to, "f") == 0) {
        printf("%.2f C = %.2f F\n", val, (val * 9.0/5.0) + 32.0);
    } else if (strcmp(from, "f") == 0 && strcmp(to, "c") == 0) {
        printf("%.2f F = %.2f C\n", val, (val - 32.0) * 5.0/9.0);
    } else if (strcmp(from, "km") == 0 && strcmp(to, "mi") == 0) {
        printf("%.2f km = %.4f miles\n", val, val * 0.621371);
    } else if (strcmp(from, "mi") == 0 && strcmp(to, "km") == 0) {
        printf("%.2f miles = %.4f km\n", val, val * 1.60934);
    } else if (strcmp(from, "mb") == 0 && strcmp(to, "gb") == 0) {
        printf("%.2f MB = %.4f GB\n", val, val / 1024.0);
    } else if (strcmp(from, "gb") == 0 && strcmp(to, "mb") == 0) {
        printf("%.2f GB = %.2f MB\n", val, val * 1024.0);
    } else {
        printf("Conversion from %s to %s not directly supported.\n", from, to);
    }
    return 0;
}
