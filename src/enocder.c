
#include "encoder.h"

int encode_data(const char *in_path, FILE *out_file, char **code_table) {
    // TODO (Week 3): Implement the encoding loop
    // 1. Open the input file for reading
    // 2. Initialize the BitWriter
    // 3. For each char: get bit-string from table, write bits via bw_write_bit
    // 4. Flush and close

    // Suppress -Wunused-parameter until student implementation
    (void)in_path;
    (void)out_file;
    (void)code_table;

    return 0;
}

BitWriter bw_open(FILE *out) {
    // TODO (Week 3): Initialize BitWriter (buffer=0, count=0)
    BitWriter bw = {0};

    // Suppress -Wunused-parameter until student implementation
    (void)out; 
    
    return bw;
}

void bw_write_bit(BitWriter *bw, int bit) {
    // TODO (Week 3): Implement the "Bit-Packing" logic:
    // 1. Position the 'bit' (0 or 1) into the buffer using MSB-first order.
    //    Hint: Use (1 << (7 - bw->count)) to shift the bit to the correct slot.
    // 2. Increment the count of bits currently held in the buffer.
    // 3. If the buffer is full (8 bits):
    //    - Write the buffer to the file using fputc.
    //    - Reset both the buffer and the count to 0 for the next byte.

    // Suppress -Wunused-parameter until student implementation
    (void)bw;
    (void)bit;
}

void bw_flush(BitWriter *bw) {
    // TODO (Week 3): Write the final partial byte if count > 0
    
    // Suppress -Wunused-parameter until student implementation
    (void)bw;
}
