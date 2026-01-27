#ifndef ENCODER_H
#define ENCODER_H

#include <stdio.h>
#include <stdint.h>

typedef struct {
    uint8_t buffer;
    int count;
    FILE *file;
} BitWriter;

// High-level "Phase 3" function
int encode_data(const char *in_path, FILE *out_file, char **code_table);

// Low-level bit-shifting helpers
BitWriter bw_open(FILE *out);
void bw_write_bit(BitWriter *bw, int bit);
void bw_flush(BitWriter *bw);

#endif
