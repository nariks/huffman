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
    for (int i = 0; i < 256; i++) {
        map->counts[i] = 0;
    }

    // TODO: Implement Buffered I/O here using fread()
    // Loop through the file, update map->counts[byte]
    unsigned char buffer[BUFFER_SIZE];
    size_t readCount = 0;
    size_t totalBytes = 0;

    while((readCount = fread(buffer, 1 , BUFFER_SIZE, file)) > 0) {
        
        for(size_t i = 0; i < readCount; i++) {
            map->counts[buffer[i]]++;
        }

        totalBytes += readCount;
    }

    // Empty file handling
    if (totalBytes == 0)
        fprintf(stderr, "File is empty. Nothing to report!\n");
        
    fclose(file);
    return 0;
}
