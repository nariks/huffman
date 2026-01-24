#include <stdio.h>
#include "frequency.h"
#include "priority_queue.h"
#include "tree.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filepath>\n", argv[0]);
        return 1;
    }

    // --- Phase 1: Frequency Analysis ---
    FrequencyMap map = {0};
    if (calculate_frequencies(argv[1], &map) != 0) {
        fprintf(stderr, "Error: Could not process file %s\n", argv[1]);
        return 1;
    }

    printf("=== Frequency Analysis: %s ===\n", argv[1]);
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

    // --- Cleanup ---
    free_tree(root);
    pq_destroy(pq);
    
    return 0;
}
