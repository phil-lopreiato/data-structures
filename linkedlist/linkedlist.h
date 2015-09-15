#ifndef FILE_LINKEDLIST
#define FILE_LINKEDLIST

#define NODE_FREE_FUNC void(*free_node)(struct ll_node*)
#define NODE_PRINT_FUNC void(*print_node)(struct ll_node*)
#define NODE_CMP_FUNC int(*compare)(void*, void*)

struct ll_node {
        void *data;
        struct ll_node *next;
        struct ll_node *last;
};

struct ll {
        struct ll_node *head;
        struct ll_node *tail;
        int size;
};

// initialize empty list
struct ll * ll_init();

// create a node with the given value
struct ll_node* ll_create_node(void *value);

int ll_get_size(struct ll *list);

// check if a node exists
int ll_exists(struct ll *list, void* data, NODE_CMP_FUNC);

// append node to the tail of the list
void ll_append(struct ll *list, struct ll_node *node);

// prepend node to the head of the list
void ll_prepend(struct ll *list, struct ll_node *node);

// return node from the front of the list
struct ll_node* ll_first(struct ll *list);

// return the node from the front of the list without removing it
struct ll_node* ll_first_peek(struct ll *list);

// return the node at the tail of the list
struct ll_node* ll_last(struct ll *list);

// peek at the tail node without removing it
struct ll_node* ll_last_peek(struct ll *list);

void ll_print(struct ll*, NODE_PRINT_FUNC);

// remove a node from the list
// DOES NOT FREE THE NODE
void ll_remove(struct ll *list, struct ll_node *node);

// removes all nodes with given data from the list
// DOES NOT FREE THE NODE
void ll_delete(struct ll *list, void* data, NODE_CMP_FUNC);

// clear everything in the list
void ll_clear(struct ll *list, NODE_FREE_FUNC);

// clear the list and free the given pointer
void ll_free(struct ll *list, NODE_FREE_FUNC);

#endif
