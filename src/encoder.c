#include "encoder.h"

int encode_data(const char *in_path, FILE *out_file, char **code_table) {
    FILE *in = fopen(in_path, "rb");
    if (!in) return -1;

    BitWriter bw = bw_open(out_file);

    int c;
    while ((c = fgetc(in)) != EOF) {
        // Use (unsigned char) to ensure values 128-255 map to correct table indices
        char *code = code_table[(unsigned char)c];
        if (code) {
            for (int i = 0; code[i] != '\0'; i++) {
                bw_write_bit(&bw, code[i] == '1');
            }
        }
    }

    bw_flush(&bw);
    fclose(in);
    return 0;
}

BitWriter bw_open(FILE *out) {
    BitWriter bw = {0, 0, out};
    return bw;
}

void bw_write_bit(BitWriter *bw, int bit) {
    // Fill from MSB to LSB (7 down to 0)
    if (bit) bw->buffer |= (1 << (7 - bw->count));
    bw->count++;

    if (bw->count == 8) {
        fputc(bw->buffer, bw->file);
        bw->buffer = 0;
        bw->count = 0;
    }
}

void bw_flush(BitWriter *bw) {
    if (bw->count > 0) {
        fputc(bw->buffer, bw->file);
        bw->buffer = 0;
        bw->count = 0;
    }
}

