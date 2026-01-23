#include <stdlib.h>
#include <stdio.h>
#include "priority_queue.h"

PriorityQueue* pq_create(uint32_t capacity) {
    /* * TODO 3.0: Constructor
     * 1. Allocate memory for the PriorityQueue struct.
     * 2. Allocate the internal 'nodes' array for (capacity) HuffmanNode pointers.
     * 3. Initialize size to 0 and store the capacity.
     */

    PriorityQueue *pq = malloc(sizeof(PriorityQueue));
    if (!pq) {
        perror("Error: Could not allocate memory for priority queue");
        exit(EXIT_FAILURE);
    }

    pq->nodes = malloc(capacity * sizeof(HuffmanNode*));
    if (!pq->nodes) {
        perror("Error: Could not allocate memory for priority queue node");
        exit(EXIT_FAILURE);
    }

    pq->size = 0;
    pq->capacity = capacity;
    return pq; 
}

void pq_insert(PriorityQueue *pq, HuffmanNode *node) {
    /* * TODO 3.1: "Sift-Up" (Insertion)
     * Implement the O(log n) heap insertion. 
     * The node must bubble up until its parent has a lower or equal frequency.
     */

    if (pq->size < pq->capacity) {
        pq->nodes[pq->size] = node;
        pq->size++;
    } else {
        fprintf(stderr, "Queue capacity reached!\n");
        return;
    }

    uint32_t child_index = pq->size - 1;

    while(child_index) {
        uint32_t parent_index = (child_index - 1) / 2;
        uint64_t child_freq = pq->nodes[child_index]->freq;
        uint64_t parent_freq = pq->nodes[parent_index]->freq;

        if (child_freq < parent_freq) {
            pq->nodes[child_index] = pq->nodes[parent_index];
            pq->nodes[parent_index] = node;
            child_index = parent_index;
        } else {
            break;
        }
    }
    return;
}

HuffmanNode* pq_extract_min(PriorityQueue *pq) {
    /* TODO 3.2: "Sift-Down" (Extraction)
     * 1. Extract the root and move the last leaf to the top.
     * 2. Restore the Min-Heap property by "sinking" the new root.
     * 3. At each step, compare the node with its SMALLEST child.
     * 4. Stop when the node is smaller than both children or hits the bottom.
     * * Note: Be careful with your array bounds when checking for children!
     */

    if (pq_is_empty(pq)) {
        return NULL;
    } else if (pq->size == 1) {
        pq->size--;
        return pq->nodes[0];
    }

    uint32_t last_index = pq->size - 1;

    HuffmanNode *min_node = pq->nodes[0];
    pq->nodes[0] = pq->nodes[last_index];
    pq->nodes[last_index] = NULL;
    pq->size--;
    last_index--;

    if (last_index == 0) {
        return min_node;
    }

    uint32_t parent_index = 0;

    while(1) {
        uint32_t left_child_index = (2 * parent_index) + 1;
        uint32_t right_child_index = (2 * parent_index) + 2;
        uint64_t parent_freq = pq->nodes[parent_index]->freq;

        if (right_child_index <= last_index) {
            uint64_t right_freq = pq->nodes[right_child_index]->freq;
            uint64_t left_freq = pq->nodes[left_child_index]->freq;

            if (parent_freq < left_freq && parent_freq < right_freq) {
            break;
            } 

            if (right_freq >= left_freq) {
                if (parent_freq > left_freq) { 
                    HuffmanNode *temp = pq->nodes[left_child_index];
                    pq->nodes[left_child_index] = pq->nodes[parent_index];
                    pq->nodes[parent_index] = temp;
                    parent_index = left_child_index;
                } else {
                    break;
                }
            } else if (right_freq < left_freq) {
                if (parent_freq > right_freq) {
                    HuffmanNode *temp = pq->nodes[right_child_index];
                    pq->nodes[right_child_index] = pq->nodes[parent_index];
                    pq->nodes[parent_index] = temp;
                    parent_index = right_child_index;
                } else {
                    break;
                }
            }

        } else if (left_child_index <= last_index) {
            uint64_t left_freq = pq->nodes[left_child_index]->freq;

            if (parent_freq > left_freq) { 
                    HuffmanNode *temp = pq->nodes[left_child_index];
                    pq->nodes[left_child_index] = pq->nodes[parent_index];
                    pq->nodes[parent_index] = temp;
                    parent_index = left_child_index;
            } else {
                break;
            }
        } else {
            break;
        }
    }
    return min_node;
}

bool pq_is_empty(PriorityQueue *pq) {
    /* * TODO 3.3: Return true if the PQ size is 0. */
    if (!pq->size) {
        return true;
    } else {
        return false;
    } 
}

void pq_destroy(PriorityQueue *pq) {
    /* * TODO 3.4: Destructor
     * Clean up all memory allocated in pq_create.
     * NOTE: Do NOT free the HuffmanNodes themselves here.
     */
    free(pq->nodes);
    free(pq);
}