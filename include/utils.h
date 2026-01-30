#ifndef UTILS_H
#define UTILS_H

#include "tree.h"
#include <stddef.h>

// UI/UX Helpers
void generate_output_path(const char* input, char* output, size_t max_len);
void generate_decoded_path(const char* input, char* output, size_t max_len);
void print_stats(const char* input, const char* output);

// Visualizing the Algorithm
void print_huffman_codes(HuffmanNode *root, char *path, int depth);

#endif
