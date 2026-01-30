#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tree.h"

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
