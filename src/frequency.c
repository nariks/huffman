#include "frequency.h"
#include <stdio.h>
#include <stdbool.h>

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
    uint8_t buffer[BUFFER_SIZE];
    int readCount;
    bool emptyFile = true;

    while((readCount = fread(buffer, sizeof(char), BUFFER_SIZE, file)) > 0) {
        
        for(int i = 0; i < readCount; i++) {
            map->counts[buffer[i]]++;
        }

        if (emptyFile)
            emptyFile = false;
    }

    if (emptyFile)
        printf("File is empty!\n");
        
    fclose(file);

    return 0;
}