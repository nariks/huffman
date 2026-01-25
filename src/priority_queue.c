#include <stdlib.h>
#include "priority_queue.h"
#include "tree.h"

// TODO (Week 3): Implement this helper to ensure a deterministic tree.
// Deterministic comparison: Frequency first, then lowest ASCII character 
// (use the get_min_char function from tree.h).
static bool is_smaller(HuffmanNode *a, HuffmanNode *b) {
    // TODO: 1. If frequencies are different, return a->freq < b->freq
    // TODO: 2. If frequencies are equal, return get_min_char(a) < get_min_char(b)
    
    // Suppress -Wunused-parameter until student implementation
    (void)a;
    (void)b;
    return false;
}

PriorityQueue* pq_create(uint32_t capacity) {
    PriorityQueue *pq = malloc(sizeof(PriorityQueue));
    pq->nodes = malloc(sizeof(HuffmanNode*) * capacity);
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}

void pq_insert(PriorityQueue *pq, HuffmanNode *node) {
    uint32_t i = pq->size++;
    while (i > 0) {
        uint32_t p = (i - 1) / 2; // Find the Boss
        // TODO (Week 3): Replace the simple <= check with your new is_smaller function.
        // This ensures the tree is built exactly the same way every time.
        // Suppress -Wunused-function until student implementation
        (void)is_smaller;
        if (pq->nodes[p]->freq <= node->freq) break; 

        pq->nodes[i] = pq->nodes[p]; // Boss moves down
        i = p;
    }
    pq->nodes[i] = node; // Node climbs to its spot
}

HuffmanNode* pq_extract_min(PriorityQueue *pq) {
    // 1. Check if the queue is empty
    if (pq->size == 0) return NULL;

    // 2. The "CEO" (smallest freq) is always at Index 0
    HuffmanNode *min_node = pq->nodes[0];

    // 3. Remove the last node in the array to fill the hole
    HuffmanNode *last_node = pq->nodes[--pq->size];

    // 4. If the queue is now empty, just return the node
    if (pq->size == 0) {
        pq->nodes[0] = NULL; // Optional safety
        return min_node;
    }

    // 5. Percolate Down (Sift-Down)
    uint32_t i = 0;
    uint32_t child = 1; // Start by looking at the Left Child (0 * 2 + 1)

    while (child < pq->size) {
        // TODO (Week 3): Update this check to use is_smaller.
        // If the Right child exists and is "smaller" (via tie-breaker), pick the Right.
        if (child + 1 < pq->size && pq->nodes[child + 1]->freq < pq->nodes[child]->freq) {
            child++;
        }

        // TODO (Week 3): Update this tie-breaker to use is_smaller.
        // If our last_node is smaller than the smallest child, we've found its home.
        if (last_node->freq <= pq->nodes[child]->freq) {
            break;
        }

        // Move the smaller child up into the current hole
        pq->nodes[i] = pq->nodes[child];

        // Update our index to the child's old spot and calculate the next level
        i = child;
        child = i * 2 + 1;
    }

    // 6. Place the last_node into its final resting spot
    pq->nodes[i] = last_node;

    return min_node;
}

bool pq_is_empty(PriorityQueue *pq) {
    return pq->size == 0;
}

void pq_destroy(PriorityQueue *pq) {
    free(pq->nodes);
    free(pq);
}
