#ifndef FREQUENCY_H
#define FREQUENCY_H

#include <stdint.h>
#include <stddef.h>

// Define a structure to hold our 256-byte frequency map
typedef struct {
    uint64_t counts[256];   // Individual character frequencies
    uint32_t unique_chars;  // Number of entries > 0 (Useful for PQ capacity)
} FrequencyMap;

// Function prototype for the analysis logic
// Returns 0 on success, -1 on error
int calculate_frequencies(const char *filepath, FrequencyMap *map);

#endif
