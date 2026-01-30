#ifndef DECODER_H
#define DECODER_H

#include <stdio.h>
#include <stdint.h>
#include "tree.h"

/**
 * The core decompression engine.
 * Reads the .huff file, rebuilds the tree, and writes the original data.
 */
int decompress_file(const char *input_path);

#endif
