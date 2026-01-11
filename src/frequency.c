#include "frequency.h"
#include <stdio.h>

int calculate_frequencies(const char *filepath, FrequencyMap *map) {
    FILE *file = fopen(filepath, "rb");
    if (!file) {
        perror("Error opening file");
        return -1;
    }

    // Initialize counts to zero
    for (int i = 0; i < 256; i++) {
        map->counts[i] = 0;
    }

    // TODO: Implement Buffered I/O here using fread()
    // Loop through the file, update map->counts[byte]
    
    fclose(file);
    return 0;
}