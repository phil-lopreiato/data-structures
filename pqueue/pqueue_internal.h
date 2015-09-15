#ifndef PQUEUE_INTERNAL_H
#define PQUEUE_INTERNAL_H

#include "pqueue.h"

/* Internal function declarations for priority queue */

static void
__move_node_up(struct pqueue* q, struct pqueue_node* node, int pos);

static void
__move_node_down(struct pqueue* q, struct pqueue_node* node, int pos);

static inline
int __get_parent_index(int index);

static inline
int __get_left_child_index(int index);

static inline
int __get_right_child_index(int index);

static inline
void __swap_nodes(struct pqueue* queue, int first, int second);

#endif
