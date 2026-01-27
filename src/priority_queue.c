#include <stdlib.h>
#include <stdio.h>
#include "priority_queue.h"

PriorityQueue* pq_create(uint32_t capacity) {

    //Allocating memory for the priority queue
    PriorityQueue *pq = malloc(sizeof(PriorityQueue));
    if (!pq) {
        perror("Error: Priority queue allocation failed");
        return NULL;
    }

    //Allocate memory for internal nodes array
    pq->nodes = malloc(capacity * sizeof(HuffmanNode*));
    if (!pq->nodes) {
        perror("Error: Priority queue internal node allocation failed");
        return NULL;
    }

    pq->size = 0;
    pq->capacity = capacity;
    return pq; 
}

void pq_insert(PriorityQueue *pq, HuffmanNode *node) {
    // "Sift-Up" (Insertion)
    if (pq->size < pq->capacity) {
        pq->size++;
    } else {
        fprintf(stderr, "Queue capacity reached!\n");
        return;
    }

    uint32_t child_index = pq->size - 1;
    
    while(child_index) {
        uint64_t parent_index = (child_index - 1) / 2;
        uint64_t child_freq = node->freq;
        uint64_t parent_freq = pq->nodes[parent_index]->freq;

        if (child_freq < parent_freq) {
            pq->nodes[child_index] = pq->nodes[parent_index];
            child_index = parent_index;
        } else {
            break;
        }
    }
    
    pq->nodes[child_index] = node;

    return;
}

HuffmanNode* pq_extract_min(PriorityQueue *pq) {

    
    HuffmanNode *min_node = NULL;

    if (!pq_is_empty(pq)) {
        min_node = pq->nodes[0];
        pq->nodes[0] = pq->nodes[pq->size - 1];
        pq->nodes[pq->size - 1] = NULL;
        pq->size--;
    }

    uint32_t parent_index = 0;

    //sinking the new root
    while(((2 * parent_index) + 1) < pq->size) {
        uint32_t left_child_index = (2 * parent_index) + 1;
        uint32_t right_child_index = (2 * parent_index) + 2;
        uint64_t parent_freq = pq->nodes[parent_index]->freq;

        //if root has both left and right children
        if (right_child_index < pq->size) {
            uint64_t right_freq = pq->nodes[right_child_index]->freq;
            uint64_t left_freq = pq->nodes[left_child_index]->freq;

            uint64_t smallest_freq = parent_freq;
            uint32_t smallest_index = parent_index;
            
            if (smallest_freq > left_freq) {
                smallest_index = left_child_index;
                smallest_freq = left_freq;
            } 

            if (smallest_freq > right_freq) {
                smallest_index = right_child_index;
                smallest_freq = right_freq;
            }

            if (smallest_freq != parent_freq) {
                HuffmanNode *temp = pq->nodes[smallest_index];
                pq->nodes[smallest_index] = pq->nodes[parent_index];
                pq->nodes[parent_index] = temp;
                parent_index = smallest_index;
            } else {
                break;
            }
        
        // if root has left child only    
        } else if (left_child_index < pq->size) {        
            uint64_t left_freq = pq->nodes[left_child_index]->freq;

            if (parent_freq > left_freq) { 
                    HuffmanNode *temp = pq->nodes[left_child_index];
                    pq->nodes[left_child_index] = pq->nodes[parent_index];
                    pq->nodes[parent_index] = temp;
                    parent_index = left_child_index;
            } else {
                break;
            }
        } 
    }

    return min_node;
}

bool pq_is_empty(PriorityQueue *pq) {
    return (pq->size == 0);
}

void pq_destroy(PriorityQueue *pq) {
    free(pq->nodes);
    free(pq);
}
