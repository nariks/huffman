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
    
    // TODO (Week 3): Initialize map->total_size here. 
    // This will be the first 8 bytes of your .huff file.
    
    for (int i = 0; i < 256; i++) {
        map->counts[i] = 0;
    }

    unsigned char buffer[BUFFER_SIZE];
    size_t bytes_read;
    size_t total_read = 0;

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        total_read += bytes_read;
        
        // TODO (Week 3): Update map->total_size here using bytes_read.
        
        for (size_t i = 0; i < bytes_read; i++) {
            unsigned char ch = buffer[i];

            // If this is the first time we see this byte, it's a unique character
            if (map->counts[ch] == 0) {
                map->unique_chars++;
            }

            map->counts[ch]++;
        }
    }

    // TODO (Week 3): Replace 'total_read' with 'map->total_size' to 
    // keep your FrequencyMap as the single source of truth.
    if (total_read == 0) {
        fprintf(stderr, "Warning: %s is empty. No frequencies to analyze.\n", filepath);
    }

    fclose(file);
    return 0;
}