#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tree.h"
#include "frequency.h"
#include "priority_queue.h"

// Helper to find the smallest ASCII value in a subtree for tie-breaking
unsigned char get_min_char(HuffmanNode* node) {
    if (!node) return 255;
    if (!node->left && !node->right) return node->value;

    unsigned char left_min = get_min_char(node->left);
    unsigned char right_min = get_min_char(node->right);

    return (left_min < right_min) ? left_min : right_min;
}

HuffmanNode* create_leaf_node(unsigned char value, uint64_t freq) {
    HuffmanNode *node = malloc(sizeof(HuffmanNode));
    if (!node) return NULL;
    node->value = value;
    node->freq = freq;
    node->left = node->right = NULL;
    return node;
}

HuffmanNode* create_internal_node(HuffmanNode *left, HuffmanNode *right) {
    HuffmanNode *node = malloc(sizeof(HuffmanNode));
    if (!node) return NULL;
    node->value = '\0';
    node->freq = left->freq + right->freq;
    node->left = left;
    node->right = right;
    return node;
}

void free_tree(HuffmanNode *root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

void build_code_table(HuffmanNode* root, char** table, char* path, int depth) {
    if (!root) return;

    if (!root->left && !root->right) {
        path[depth] = '\0';
        table[root->value] = strdup(path);
        return;
    }

    if (root->left) {
        path[depth] = '0';
        build_code_table(root->left, table, path, depth + 1);
    }
    if (root->right) {
        path[depth] = '1';
        build_code_table(root->right, table, path, depth + 1);
    }
}

HuffmanNode* build_huffman_tree(FrequencyMap *map, PriorityQueue *pq) {
    // TODO (Week 4): Implement the Shared Tree Building Logic
    // This logic is now DRY (Don't Repeat Yourself) so both
    // the Encoder and Decoder can use it.
    // Remember, you did this already. Just bring it in from main.c

    // 1. Load the Priority Queue
    //    - Loop through the 256 possible characters in map->counts.
    //    - If a count is > 0, create a leaf node and insert it into the PQ.

    // 2. The Core Huffman Algorithm
    //    - While the PQ has more than 1 node:
    //      a. Extract the two nodes with the smallest frequencies.
    //      b. Combine them into a new Internal Node.
    //      c. Insert the Internal Node back into the PQ.

    // 3. Also bring in the Tree validation printf logic here

    // 4. Return the Root
    //    - The last remaining node in the PQ is the root of your tree.

 
    // 1. Load the Priority Queue
    for (int i = 0; i < 256; i++) {
        if (map->counts[i] > 0) {
            pq_insert(pq, create_leaf_node((unsigned char)i, map->counts[i]));
        }
    }

    // 2. Build the Tree
    int internal_nodes_created = 0;
    while (pq->size > 1) {
        HuffmanNode *left = pq_extract_min(pq);
        HuffmanNode *right = pq_extract_min(pq);
        pq_insert(pq, create_internal_node(left, right));
        internal_nodes_created++;
    }

    HuffmanNode *root = pq_extract_min(pq);

    printf("=== Tree Validation ===\n");
    printf("Expected Internal Nodes: %u\n", map->unique_chars - 1);
    printf("Actual Internal Nodes:   %d\n", internal_nodes_created);

    if (internal_nodes_created == (int)map->unique_chars - 1) {
        printf("Result: ✅ Tree structure is mathematically sound.\n\n");
    } else {
        printf("Result: ❌ Tree structure is corrupted!\n\n");
    }

    return root;
}
