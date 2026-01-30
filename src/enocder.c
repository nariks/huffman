
#include "encoder.h"
#include <string.h>

#define BUFFER_SIZE 4096

int encode_data(const char *in_path, FILE *out_file, char **code_table) {
    // TODO (Week 3): Implement the encoding loop
    // 1. Open the input file for reading
    // 2. Initialize the BitWriter
    // 3. For each char: get bit-string from table, write bits via bw_write_bit
    // 4. Flush and close

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
            int j = 0;
            //printf("insider encoder after bw_write_bit. OK\n");
            //printf("code_table[%c] - %s\n", ch, code_table[ch]);
            while (code_table[ch][j] != '\0') {

                bw_write_bit(&bw, code_table[ch][j] - '0');  
                j++; 
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
