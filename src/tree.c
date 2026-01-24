#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

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

void print_huffman_codes(HuffmanNode *root, char *path, int depth) {
    if (!root) return;

    // Leaf node: We've reached a character
    if (!root->left && !root->right) {
        path[depth] = '\0';
        
        // Output formatting: Hex, Char, Frequency, and the Bit String
        // Determine if character is printable, otherwise show a dot
        char display_char = (root->value >= 32 && root->value <= 126) ? (char)root->value : '.';

        // Print in a structured, column-aligned format
        printf("0x%02X | '%c' | Freq: %-10llu | Code: %s\n", 
            root->value, 
            display_char, 
            (unsigned long long)root->freq, 
            path);
        return;
    }

    // Standard recursive walk: Left is 0, Right is 1
    if (root->left) {
        path[depth] = '0';
        print_huffman_codes(root->left, path, depth + 1);
    }
    
    if (root->right) {
        path[depth] = '1';
        print_huffman_codes(root->right, path, depth + 1);
    }
}
