
#include "encoder.h"
#include <string.h>

#define BUFFER_SIZE 4096

int encode_data(const char *in_path, FILE *out_file, char **code_table) {

    FILE *file = fopen(in_path, "rb");
    if (!file) {
        perror("Error opening file");
        return -1;
    }

    BitWriter bw = bw_open(out_file);

    unsigned char buffer[BUFFER_SIZE];
    size_t bytes_read;
   
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        
        for (size_t i = 0; i < bytes_read; i++) {
            unsigned char ch = buffer[i];
            
            for (int j = 0; code_table[ch][j] != '\0'; j++) {
                bw_write_bit(&bw, code_table[ch][j] - '0');     
            }
        }     
    }

    bw_flush(&bw);
    fclose(file);
    return 0;

}

BitWriter bw_open(FILE *out) {
    BitWriter bw = {0, 0, out};
    return bw;
}

void bw_write_bit(BitWriter *bw, int bit) {

    bw->buffer |= bit << (7 - bw->count);
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
