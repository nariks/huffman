#include "frequency.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

int calculate_frequencies(const char *filepath, FrequencyMap *map) {
    FILE *file = fopen(filepath, "rb");
    if (!file) {
        perror("Error opening file");
        return -1;
    }

    // Initialize counts to zero
    map->unique_chars = 0;
    map->total_size = 0;        // The first 8 bytes of .huff file.
    
    for (int i = 0; i < 256; i++) {
        map->counts[i] = 0;
    }

    unsigned char buffer[BUFFER_SIZE];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        map->total_size += bytes_read;
        
        for (size_t i = 0; i < bytes_read; i++) {
            unsigned char ch = buffer[i];

            // If this is the first time we see this byte, it's a unique character
            if (map->counts[ch] == 0) {
                map->unique_chars++;
            }

            map->counts[ch]++;
        }
    }

    if (map->total_size == 0) {
        fprintf(stderr, "Warning: %s is empty. No frequencies to analyze.\n", filepath);
    }

    fclose(file);
    return 0;
}