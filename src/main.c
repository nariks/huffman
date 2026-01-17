#include <stdio.h>
#include "frequency.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filepath>\n", argv[0]);
        return 1;
    }

    // --- Phase 1: Frequency Analysis ---
    FrequencyMap map = {0};
    if (calculate_frequencies(argv[1], &map) != 0) {
        fprintf(stderr, "Error: Could not process file %s\n", argv[1]);
        return 1;
    }

    printf("=== Frequency Analysis: %s ===\n", argv[1]);
    for (int i = 0; i < 256; i++) {
        if (map.counts[i] > 0) {
            // Print printable chars, otherwise show a dot
            char display = (i >= 32 && i <= 126) ? (char)i : '.';
            printf("0x%02X (%c): %llu\n", i, display, map.counts[i]);
        }
    }
    printf("\n");

    return 0;
}
