#ifndef PQUEUE_H
#define PQUEUE_H

#define NODE_PRINT_FUNC void(*print)(void* data)

struct pqueue_node {
        int priority;
        int index;
        void* data;
};

struct pqueue {
        int size;
        int length;
        struct pqueue_node** data;
};

// init a priority queue with the given size
struct pqueue* pqueue_init(int size);

// get the current size of a queue
int pqueue_size(struct pqueue* queue);

// insert a node with priority into the queue
struct pqueue_node* pqueue_insert(struct pqueue* queue, void* data, int priority);

// get the vale of the node with max priority
void* pqueue_extract_max(struct pqueue* queue);

// increases the priority of a given node
void pqueue_increase(struct pqueue* queue, struct pqueue_node* node, int priority);

// set the priority of a given node
void pqueue_change(struct pqueue* queue, struct pqueue_node* node, int delta);

// print the queue in array-order
void pqueue_print(struct pqueue* queue, NODE_PRINT_FUNC);

#endif
