#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

HuffmanNode* create_leaf_node(unsigned char value, uint64_t freq) {
    // Suppress -Wunused-parameter until student implementation
    (void)value;
    (void)freq;

    /* * TODO 2.5: Leaf Constructor
     * 1. Allocate memory for a HuffmanNode.
     * 2. Set the character value and its frequency.
     * 3. Ensure the left and right child pointers are NULL.
     */
    return NULL; 
}

HuffmanNode* create_internal_node(HuffmanNode *left, HuffmanNode *right) {
    // Suppress -Wunused-parameter until student implementation
    (void)left;
    (void)right;

    /* * TODO 2.6: Internal Node Constructor
     * 1. Allocate memory for a HuffmanNode.
     * 2. Set frequency to the sum of the left and right children.
     * 3. Assign the left and right pointers.
     * 4. Note: Character value is usually ignored for internal nodes.
     */
    return NULL;
}

void free_tree(HuffmanNode *root) {
    // Suppress -Wunused-parameter until student implementation
    (void)root;

    /* * TODO 2.7: Recursive Destructor
     * Use Post-Order Traversal to free the entire tree structure.
     * Make sure you don't free a NULL pointer.
     */
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
