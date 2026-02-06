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
    
    // Read from LSB to MSB
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
    // Open the .huff file in binary mode
    FILE *in = fopen(input_path, "rb");
    if (!in) { perror("Error opening input file"); return 1; }

    // Parse the File Header
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
    
    //Rebuild the Huffman Tree
    FrequencyMap map = {0};
    map.total_size = total_size;
    memcpy(map.counts, counts, 256 * sizeof(uint64_t));

    for (int i = 0; i < 256; i++) {
        if (counts[i] > 0) map.unique_chars++;
    }

    PriorityQueue *pq = pq_create(256);
    HuffmanNode *root = build_huffman_tree(&map, pq);

    
    char output_path[512];
    // create the restored filename.
    generate_decoded_path(input_path, output_path, sizeof(output_path));

    //Open the output file for writing in binary mode.
    FILE *out = fopen(output_path, "wb");
    if (!out) { perror("Error opening output file"); return 1; }


    // Decode bitstream
    uint64_t bytes_written = 0;
    BitReader br = {in, 0, 0};
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


    // Final Cleanup
    fclose(in);
    fclose(out);
    free_tree(root);
    pq_destroy(pq);

    printf("Result: ✅ Decompression complete. Created: %s\n", output_path);
    return 0;
}
