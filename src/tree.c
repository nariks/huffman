#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tree.h"

// TODO (Week 3): Implement this helper to find the smallest ASCII value in a subtree.
// This is used by the Priority Queue's is_smaller() for tie-breaking.
unsigned char get_min_char(HuffmanNode* node) {
    
    if (node == NULL) {
        return 255;
    } else if (node->right == NULL && node->left == NULL) {
        return node->value;
    } else {
        uint64_t left_min = get_min_char(node->left);
        uint64_t right_min = get_min_char(node->right);
        return left_min < right_min ? left_min : right_min;
    }
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

    if (root == NULL)
        return;

    if (root->left == NULL && root->right == NULL) {
        path[depth] = '\0';
        table[root->value] = strdup(path);
    } else {
        if (root->left) {
            path[depth] = '0';
            build_code_table(root->left, table, path, depth + 1);
        }

        if (root->right) {
            path[depth] = '1';
            build_code_table(root->right, table, path, depth + 1);

        }
    }
}