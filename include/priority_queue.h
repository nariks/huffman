#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "tree.h"
#include <stdbool.h>

struct PriorityQueue {
    uint32_t size;                 // Current number of nodes in the heap
    uint32_t capacity;             // Maximum allowed nodes (usually 256)
    HuffmanNode **nodes;           // Array of HuffmanNode pointers
};

typedef struct PriorityQueue PriorityQueue;

// Lifecycle
PriorityQueue* pq_create(uint32_t capacity);
void pq_destroy(PriorityQueue *pq);

// Logic
void pq_insert(PriorityQueue *pq, HuffmanNode *node);
HuffmanNode* pq_extract_min(PriorityQueue *pq);
bool pq_is_empty(PriorityQueue *pq);

#endif
