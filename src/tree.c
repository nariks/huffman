#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tree.h"

// TODO (Week 3): Implement this helper to find the smallest ASCII value in a subtree.
// This is used by the Priority Queue's is_smaller() for tie-breaking.
unsigned char get_min_char(HuffmanNode* node) {
    // TODO: 
    // 1. If node is NULL, return 255 (the highest possible byte value).
    // 2. If it's a leaf node, return node->value.
    // 3. Otherwise, recursively find the min in left and right subtrees and return the smaller one.

    // Suppress -Wunused-parameter until student implementation
    (void)node;
    return 0;
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

// TODO (Week 3): Implement the recursive tree traversal to build the bit-string table.
void build_code_table(HuffmanNode* root, char** table, char* path, int depth) {
    // TODO:
    // 1. Base case: If root is NULL, return.
    // 2. Leaf case: If it's a leaf, null-terminate path[depth] and strdup(path) into table[root->value].
    // 3. Recursive step: 
    //    - If left exists, set path[depth] = '0' and recurse (depth + 1).
    //    - If right exists, set path[depth] = '1' and recurse (depth + 1).

    // Suppress -Wunused-parameter until student implementation
    (void)root;
    (void)table;
    (void)path;
    (void)depth;
}
