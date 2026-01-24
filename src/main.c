
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

    // --- Phase 2: Building the Tree ---
    /* * TODO 4.0: Initialize the Priority Queue
     * Use map.unique_chars to determine the initial capacity of your Min-Heap.
     */

    PriorityQueue *pq = pq_create(map.unique_chars);

    /* * TODO 4.1: Load the Leaf Nodes
     * Iterate through your FrequencyMap and insert a leaf node for every 
     * character with a count > 0 into your Priority Queue.
     */

    for (int i = 0; i < 256; i++) {
        if (map.counts[i] > 0) {
            HuffmanNode *leaf_node = create_leaf_node(i, map.counts[i]);
            pq_insert(pq, leaf_node);
        }

    }

    /* * TODO 4.2: Build the Huffman Tree
     * Implement the Huffman algorithm:
     * 1. While the PQ has more than 1 node:
     * a. Extract the two nodes with the lowest frequency.
     * b. Create a new internal node with these two as children.
     * c. Insert the new internal node back into the PQ.
     * 2. The remaining node in the PQ is your Tree Root.
     */

    int internal_nodes_created = 0; // Track this to verify tree integrity

    while((pq->size) > 1) {
        HuffmanNode *left =  pq_extract_min(pq);
        HuffmanNode *right = pq_extract_min(pq);
        HuffmanNode *internal = create_internal_node(left, right);
        pq_insert(pq, internal);
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
    /* * TODO 4.3: Memory Management
     * Ensure you have a recursive function to free your tree and
     * a function to destroy your Priority Queue to prevent memory leaks.
     */

    pq_destroy(pq);
    free_tree(root);
    
    
    return 0;
}
