#include <stdlib.h>
#include "priority_queue.h"

PriorityQueue* pq_create(uint32_t capacity) {
    // Suppress -Wunused-parameter until student implementation
    (void)capacity; 
    /* * TODO 3.0: Constructor
     * 1. Allocate memory for the PriorityQueue struct.
     * 2. Allocate the internal 'nodes' array for (capacity) HuffmanNode pointers.
     * 3. Initialize size to 0 and store the capacity.
     */
    return NULL; 
}

void pq_insert(PriorityQueue *pq, HuffmanNode *node) {
    // Suppress -Wunused-parameter until student implementation
    (void)pq;   
    (void)node; 
    /* * TODO 3.1: "Sift-Up" (Insertion)
     * Implement the O(log n) heap insertion. 
     * The node must bubble up until its parent has a lower or equal frequency.
     */
}

HuffmanNode* pq_extract_min(PriorityQueue *pq) {
    // Suppress -Wunused-parameter until student implementation
    (void)pq; 
    /* TODO 3.2: "Sift-Down" (Extraction)
     * 1. Extract the root and move the last leaf to the top.
     * 2. Restore the Min-Heap property by "sinking" the new root.
     * 3. At each step, compare the node with its SMALLEST child.
     * 4. Stop when the node is smaller than both children or hits the bottom.
     * * Note: Be careful with your array bounds when checking for children!
     */
    return NULL;
}

bool pq_is_empty(PriorityQueue *pq) {
    // Suppress -Wunused-parameter until student implementation
    (void)pq;
    /* * TODO 3.3: Return true if the PQ size is 0. */
    return true; 
}

void pq_destroy(PriorityQueue *pq) {
    // Suppress -Wunused-parameter until student implementation
    (void)pq; 
    /* * TODO 3.4: Destructor
     * Clean up all memory allocated in pq_create.
     * NOTE: Do NOT free the HuffmanNodes themselves here.
     */
}
