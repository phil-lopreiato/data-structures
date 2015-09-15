#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"

/**
 * Core functionality of linkedlist.h that is universal for all types of links
 */

/* Allocates memory for a new linkedlist */
struct ll
*ll_init()
{
        struct ll *list = malloc(sizeof(struct ll));
        if(!list) return NULL;
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
        return list;
}

/* Allocates memory for a node with given data */
struct ll_node*
ll_create_node(void *data)
{
        struct ll_node *node = malloc(sizeof(struct ll_node));
        if(!node) return NULL;
        node->data = data;
        node->next = NULL;
        node->last = NULL;
        return node;
}

int
ll_get_size(struct ll *list)
{
        return list->size;
}

/* Prints the contents of a list
 * Requires a function pointer passed to know how to print the node
 */
void
ll_print(struct ll *list, void(*print_node)(struct ll_node*))
{
        printf("List has %d elements\n", list->size);
        struct ll_node *node = list->head;
        while(node){
                (*print_node)(node);
                printf("->");
                node = node->next;
        }
        printf("\n");
}

void
ll_delete(struct ll *list, void* data, NODE_CMP_FUNC)
{
        if (!list) return;
        struct ll_node* node = list->head;
        struct ll_node* temp;
        while(node) {
                if ((*compare)(data, node->data)) {
                        temp = node->next;
                        ll_remove(list, node);
                        node = temp;
                } else {
                        node = node->next;
                }
        }
}

void
ll_clear(struct ll *list, void(*free_node)(struct ll_node*))
{
        struct ll_node *temp;
        struct ll_node *node = list->head;
        while(node){
                temp = node->next;
                if(free_node){
                        (*free_node)(node->data);
                }
                free(node);
                if(temp == list->head) temp = NULL;
                node = temp;
        }
        list->size = 0;
        list->head = NULL;
        list->tail = NULL;
}

void
ll_free(struct ll *list, void(*free_node)(struct ll_node*))
{
        ll_clear(list, free_node);
        free(list);
}
