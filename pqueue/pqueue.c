#include <stdlib.h>
#include <stdio.h>

#include "pqueue_internal.h"


/* Allocate memory for an array-backed priority queue */
struct pqueue*
pqueue_init(int size)
{
        struct pqueue* queue = malloc(sizeof(struct pqueue));
        if (!queue) return NULL;
        queue->size = size;
        queue->length = 0;
        queue->data = calloc(size, sizeof(struct pqueue_node));
        if (!queue->data) {
                free(queue);
                return NULL;
        }
        return queue;
}

/* Return the number of elements in the queue (constant time) */
int
pqueue_size(struct pqueue* queue)
{
        return queue->length;
}

/* Insert a node with a value & priority into the queue */
struct pqueue_node*
pqueue_insert(struct pqueue* queue, void* data, int priority)
{
        if (queue->length >= queue->size) {
                // queue is full
                return NULL;
        }
        struct pqueue_node* node = malloc(sizeof(struct pqueue_node));
        if (!node) return NULL;

        node->data = data;
        node->priority = priority;
        node->index = queue->length;

        // insert the node at the last position in the array
        // move it to the proper position by swapping with parent
        // if it has a larger prioirity
        queue->data[queue->length] = node;
        __move_node_up(queue, node, queue->length);
        queue->length++;
        return node;
}

/* Get the node with max priority from the queue
 * SWAP first and last elements, swap new root down based on priority */
void*
pqueue_extract_max(struct pqueue* queue)
{
        void* maxData;

        if (queue->length == 0) return NULL;

        // swap the root and last nodes, shrinking the queue
        queue->length--;
        __swap_nodes(queue, 0, queue->length);
        __move_node_down(queue, queue->data[0], 0);

        // note the element to be returned
        maxData = queue->data[queue->length]->data;
        free(queue->data[queue->length]);

        return maxData;
}

/* Increase the priority of a node by a given amount
 * New priority = old priority + delta (delta > 0) */
void
pqueue_increase(struct pqueue* queue, struct pqueue_node* node, int delta)
{
        if (delta <= 0) return;

        node->priority += delta;
        __move_node_up(queue, node, node->index);
}

/* Change the priority of a node */
void
pqueue_change(struct pqueue* queue, struct pqueue_node* node, int priority)
{
        if (priority == node->priority) {
                return;
        } else if (priority > node->priority) {
                pqueue_increase(queue, node, priority);
        } else {
                node->priority = priority;
                __move_node_down(queue, node, node->index);
        }
}

/* Print the contents of the queue */
void
pqueue_print(struct pqueue* queue, NODE_PRINT_FUNC)
{
        struct pqueue_node* node;
        printf("| ");
        for (int i = 0; i < queue->length; i++) {
                printf("{");
                node = queue->data[i];
                (*print)(node->data);
                printf(",%d} ", node->priority);
        }
        printf("|\n");
}

/* For a node inserted at the bottom of the queue, move it up (via parent)
 * until the priority is in the proper place
 */
static void
__move_node_up(struct pqueue* q, struct pqueue_node* node, int pos)
{
        int parentIndex = __get_parent_index(pos);
        struct pqueue_node* parent = q->data[parentIndex];
        while(parentIndex != pos && node->priority > parent->priority) {
                __swap_nodes(q, parentIndex, pos);
                pos = parentIndex;
                parentIndex = __get_parent_index(pos);
                parent = q->data[parentIndex];
        }
}

static void
__move_node_down(struct pqueue* q, struct pqueue_node* node, int pos)
{
        int lChild = __get_left_child_index(pos);
        int rChild = __get_right_child_index(pos);
        int lPri;
        int rPri;
        int max;

        if (lChild < q->length && rChild < q->length) {
                // both children are in bounds, swap with max value
                lPri = q->data[lChild]->priority;
                rPri = q->data[rChild]->priority;
                max = lPri > rPri ? lChild : rChild;

                // no need to swap, heap order is statisfied
                if (node->priority > q->data[max]->priority) return;
                __swap_nodes(q, pos, max);
                __move_node_down(q, node, max);
        } else if (lChild < q->length) {
                // only the left child is in bounds, swap with that
                // but only if its priority is higher
                if (node->priority > q->data[lChild]->priority) return;
                __swap_nodes(q, pos, lChild);
                __move_node_down(q, node, lChild);
        } else if (rChild < q->length) {
                // only the right child is in bounds, swap with that
                // but only if its priority is higher
                if (node->priority > q->data[rChild]->priority) return;
                __swap_nodes(q, pos, rChild);
                __move_node_down(q, node, rChild);
        }
        // else no children are in bounds, so we're at the bottom of the tree
}

static inline int
__get_parent_index(int index)
{
        if (index == 0) return 0;
        return (index - 1) / 2;
}

static inline int
__get_left_child_index(int index)
{
        return index * 2 + 1;
}

static inline int
__get_right_child_index(int index)
{
        return index * 2 + 2;
}

static inline void
__swap_nodes(struct pqueue* queue, int first, int second)
{
        struct pqueue_node* temp;
        temp = queue->data[first];
        queue->data[first] = queue->data[second];
        queue->data[second] = temp;

        queue->data[first]->index = first;
        queue->data[second]->index = second;
}
