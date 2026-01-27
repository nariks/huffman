#include "frequency.h"
#include <stdio.h>

#define BUFFER_SIZE 4096

int calculate_frequencies(const char *filepath, FrequencyMap *map) {
    FILE *file = fopen(filepath, "rb");
    if (!file) {
        perror("Error opening file");
        return -1;
    }

    for (int i = 0; i < 256; i++) {
        map->counts[i] = 0;
    }

    unsigned char buffer[BUFFER_SIZE];
    map->unique_chars = 0;
    size_t bytes_read;
    size_t total_read = 0;

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        total_read += bytes_read;
        for (size_t i = 0; i < bytes_read; i++) {
            //calculate frequency of characters
            map->counts[buffer[i]]++;
        }
    }

    //calculate number of unique chars
    for (int i = 0; i < 256; i++) {
        if (map->counts[i] > 0) {
                map->unique_chars++;
        }
    }

    if (total_read == 0) {
        fprintf(stderr, "Warning: %s is empty. No frequencies to analyze.\n", filepath);
    }

    fclose(file);
    return 0;
}
