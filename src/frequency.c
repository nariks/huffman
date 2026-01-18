#include "frequency.h"
#include <stdio.h>

#define BUFFER_SIZE 4096

int calculate_frequencies(const char *filepath, FrequencyMap *map) {
    FILE *file = fopen(filepath, "rb");
    if (!file) {
        perror("Error opening file");
        return -1;
    }

    // Initialize counts to zero
    /* TODO 1.0: Initialize map->unique_chars here also */
    for (int i = 0; i < 256; i++) {
        map->counts[i] = 0;
    }

    unsigned char buffer[BUFFER_SIZE];
    size_t bytes_read;
    size_t total_read = 0;

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        total_read += bytes_read;
        for (size_t i = 0; i < bytes_read; i++) {
            /* * TODO 1.1: Calculate Unique Characters
             * Iterate through the map->counts array. 
             * For every index where the count is greater than 0, 
             * increment map->unique_chars.
             * * This value is critical for Phase 2 memory allocation.
             */
            map->counts[buffer[i]]++;
        }
    }

    if (total_read == 0) {
        fprintf(stderr, "Warning: %s is empty. No frequencies to analyze.\n", filepath);
    }

    fclose(file);
    return 0;
}
