#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

HuffmanNode* create_leaf_node(unsigned char value, uint64_t freq) {
    /* * TODO 2.0: Leaf Constructor
     * 1. Allocate memory for a HuffmanNode.
     * 2. Set the character value and its frequency.
     * 3. Ensure the left and right child pointers are NULL.
     */

    HuffmanNode *node = malloc(sizeof(HuffmanNode));
    if (node == NULL) {
        perror("Error: Could not allocate memory for node");
        exit(EXIT_FAILURE);
    }

    node->value = value;
    node->freq = freq;
    node->left = NULL;
    node->right = NULL;

    return node; 
}

HuffmanNode* create_internal_node(HuffmanNode *left, HuffmanNode *right) {
    /* * TODO 2.1: Internal Node Constructor
     * 1. Allocate memory for a HuffmanNode.
     * 2. Set frequency to the sum of the left and right children.
     * 3. Assign the left and right pointers.
     * 4. Note: Character value is usually ignored for internal nodes.
     */

    HuffmanNode *node = malloc(sizeof(HuffmanNode));
    if (node == NULL) {
        perror("Error: Could not allocate memory for node");
        exit(EXIT_FAILURE);
    }

    node->freq = left->freq + right->freq;
    node->value = 0;
    node->left = left;
    node->right = right;

    return node;
}

void free_tree(HuffmanNode *root) {
    /* * TODO 2.2: Recursive Destructor
     * Use Post-Order Traversal to free the entire tree structure.
     * Make sure you don't free a NULL pointer.
     */

    if (root) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }


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
