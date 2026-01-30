#include <stdio.h>
#include <stdlib.h>
#include "frequency.h"
#include "priority_queue.h"
#include "tree.h"
#include "encoder.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filepath>\n", argv[0]);
        return 1;
    }

    const char *input_path = argv[1];

    // --- Phase 1: Frequency Analysis ---
    FrequencyMap map = {0};
    if (calculate_frequencies(input_path, &map) != 0) {
        fprintf(stderr, "Error: Could not process file %s\n", input_path);
        return 1;
    }

    printf("=== Frequency Analysis: %s ===\n", input_path);
    for (int i = 0; i < 256; i++) {
        if (map.counts[i] > 0) {
            // Print printable chars, otherwise show a dot
            char display = (i >= 32 && i <= 126) ? (char)i : '.';
            printf("0x%02X (%c): %llu\n", i, display, map.counts[i]);
        }
    }
    printf("\n");

    // --- Phase 2: Building the Tree ---
    printf("=== File Statistics ===\n");
    printf("Unique Bytes:  %u\n\n", map.unique_chars);

    if (map.unique_chars == 0) {
        printf("File is empty. No tree to build.\n");
        return 0;
    }

    PriorityQueue *pq = pq_create(map.unique_chars);

    // 1. Load the Priority Queue
    for (int i = 0; i < 256; i++) {
        if (map.counts[i] > 0) {
            pq_insert(pq, create_leaf_node((unsigned char)i, map.counts[i]));
        }
    }

    // 2. Build the Tree
    // As the Lead, we track internal nodes to verify tree integrity
    int internal_nodes_created = 0;
    while (pq->size > 1) {
        HuffmanNode *left = pq_extract_min(pq);
        HuffmanNode *right = pq_extract_min(pq);
        pq_insert(pq, create_internal_node(left, right));
        internal_nodes_created++;
    }

    HuffmanNode *root = pq_extract_min(pq);

    printf("=== Tree Validation ===\n");
    printf("Expected Internal Nodes: %u\n", map.unique_chars - 1);
    printf("Actual Internal Nodes:   %d\n", internal_nodes_created);

    if (internal_nodes_created == (int)map.unique_chars - 1) {
        printf("Result: ✅ Tree structure is mathematically sound.\n\n");
    } else {
        printf("Result: ❌ Tree structure is corrupted!\n\n");
    }

    printf("=== Huffman Codes ===\n");
    char path_buffer[256];
    print_huffman_codes(root, path_buffer, 0);

    // --- Phase 3: Compression & Bit-Packing ---
    char output_path[512];
    generate_output_path(input_path, output_path, sizeof(output_path));

    printf("\n=== Huffman Compression ===\n");
    printf("Input:  %s\n", input_path);
    printf("Output: %s\n", output_path);

    // 1. Generate the lookup table (the "GPS directions" for the encoder)
    char *code_table[256] = {0};
    build_code_table(root, code_table, path_buffer, 0);
    printf("Result: ✅ Lookup table generated.\n");

    // 2. Open the output .huff file
    FILE *out = fopen(output_path, "wb");
    if (!out) { 
        perror("Error opening output file"); 
        // Cleanup before exiting
        for (int i = 0; i < 256; i++) if (code_table[i]) free(code_table[i]);
        free_tree(root);
        pq_destroy(pq);
        return 1; 
    }

    // 3. Write the Header (Total Size + Frequency Map)
    // This allows the decoder to rebuild the exact same tree later.
    fwrite(&map.total_size, sizeof(uint64_t), 1, out);
    fwrite(map.counts, sizeof(uint64_t), 256, out);
    printf("Result: ✅ File header written (Header Size: %lu bytes).\n", 
            sizeof(uint64_t) + (sizeof(uint64_t) * 256));

    // 4. Run the Encoding Engine
    // This reads the input file again and packs bits into 'out' using the code_table.
    if (encode_data(input_path, out, code_table) != 0) {
        fprintf(stderr, "Error: Encoding process failed.\n");
        fclose(out);
        return 1;
    }
    
    // Explicitly close the file to ensure the final byte is flushed to disk
    fclose(out);

    printf("Result: ✅ Bit-packing complete.\n\n");

    // 5. Show the victory stats
    print_stats(input_path, output_path);

    // --- Cleanup ---
    for (int i = 0; i < 256; i++) if (code_table[i]) free(code_table[i]);
    free_tree(root);
    pq_destroy(pq);
    
    return 0;
}
