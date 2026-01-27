#ifndef TREE_H
#define TREE_H

#include <stdint.h>

typedef struct HuffmanNode {
    unsigned char value;
    uint64_t freq;
    struct HuffmanNode *left;
    struct HuffmanNode *right;
} HuffmanNode;

HuffmanNode* create_leaf_node(unsigned char value, uint64_t freq);
HuffmanNode* create_internal_node(HuffmanNode *left, HuffmanNode *right);
void free_tree(HuffmanNode *root);

void build_code_table(HuffmanNode* root, char** table, char* path, int depth);
unsigned char get_min_char(HuffmanNode* node);

#endif
