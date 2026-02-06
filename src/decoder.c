#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "decoder.h"
#include "frequency.h"
#include "tree.h"
#include "priority_queue.h"
#include "utils.h"

typedef struct {
    FILE *fp;
    uint8_t buffer;
    int bits_left;
} BitReader;

int br_read_bit(BitReader *br) {
    // TODO (Week 4): Implement the "Bit-Unpacking" logic:
    // 1. If bits_left is 0: fread 1 byte from fp into the buffer.
    // 2. If fread fails (returns < 1), return -1 to signal End of Stream.
    // 3. Extract the bit at the current position (MSB-first).
    // 4. Decrement bits_left and return the bit (0 or 1).

    if (br->bits_left == 0) {
        size_t bytes_read = fread(&br->buffer, 1, 1, br->fp);
        if (bytes_read < 1) return -1;
        br->bits_left = 8;
    }
    
    br->bits_left--;
    uint8_t bit = (br->buffer >>  br->bits_left) & 1;     
    
    return bit;
    
}

int decompress_file(const char *input_path) {
    // 1. Open the .huff file in binary mode
    FILE *in = fopen(input_path, "rb");
    if (!in) { perror("Error opening input file"); return 1; }

    // TODO (Week 4): Parse the File Header
    // 1. Read the total_size (uint64_t).
    // 2. Read the frequency counts array (256 uint64_t values).
    // 3. Error check: If fread fails to get the full counts, close and return 1.
    uint64_t total_size = 0;
    uint64_t counts[256];
    if (fread(&total_size, 1, 8, in) < 8) {
        fclose(in);
        return 1;
    }

    if (fread(counts, sizeof(uint64_t), 256, in) < 256) {
        fclose(in);
        return 1; 
    }
    
    // TODO (Week 4): Rebuild the Huffman Tree
    // 1. Initialize a FrequencyMap (HINT: Use C11 { .total_size = total_size }).
    // 2. Copy 'counts' into 'map.counts' (HINT: Use memcpy).
    // 3. Scan the map to update 'unique_chars'.
    // 4. Call build_huffman_tree using a new PriorityQueue.
    FrequencyMap map = {0};
    map.total_size = total_size;
    memcpy(map.counts, counts, 256 * sizeof(uint64_t));

    for (int i = 0; i < 256; i++) {
        if (counts[i] > 0) map.unique_chars++;
    }

    PriorityQueue *pq = pq_create(256);
    HuffmanNode *root = build_huffman_tree(&map, pq);

    // TODO (Week 4): Prepare Output Path
    // 1. Use generate_decoded_path to create the restored filename.
    // 2. Open the output file for writing in binary mode.
    char output_path[512];
    generate_decoded_path(input_path, output_path, sizeof(output_path));
    FILE *out = fopen(output_path, "wb");
    if (!out) { perror("Error opening output file"); return 1; }


    // TODO (Week 4): Decode bitstream
    // 1. Initialize BitReader (buffer=0, bits_left=0).
    // 2. While (bytes_written < total_size):
    //    - Get a bit from br_read_bit.
    //    - Move current pointer: left if bit is 0, right if bit is 1.
    //    - If current is a leaf: fputc its value, increment counter, reset current to root.
    uint64_t bytes_written = 0;
    BitReader br;
    br.fp = in;
    br.buffer = 0;
    br.bits_left = 0;

    HuffmanNode *current = root;

    while (bytes_written < map.total_size) {
        uint8_t read_bit = br_read_bit(&br);
        
        
        current = read_bit ? current->right : current->left;
        if (current->right == NULL && current->left == NULL) {
            fputc(current->value, out);
            bytes_written++;
            current = root;
        }
    }


    // TODO (Week 4): Final Cleanup
    // 1. Close all file pointers.
    // 2. Free the Huffman Tree and Priority Queue to ensure 0 leaks.
    fclose(in);
    fclose(out);
    free_tree(root);
    pq_destroy(pq);

    printf("Result: ✅ Decompression complete. Created: %s\n", output_path);
    return 0;
}
