#include <stdio.h>
#include "frequency.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filepath>\n", argv[0]);
        return 1;
    }

    FrequencyMap map;
    if (calculate_frequencies(argv[1], &map) != 0) {
        return 1;
    }

    printf("--- Frequency Analysis: %s ---\n", argv[1]);
    for (int i = 0; i < 256; i++) {
        if (map.counts[i] > 0) {
            printf("0x%02X (%c): %llu\n", i, (i >= 32 && i <= 126) ? i : '.', map.counts[i]);
        }
    }

    return 0;
}
