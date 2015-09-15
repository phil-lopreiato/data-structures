#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"

int
ll_exists(struct ll *list, void* data, NODE_CMP_FUNC)
{
        if (!list) return 0;
        struct ll_node* node = list->head;
        while(node) {
                if ((*compare)(data, node->data)) {
                        return 1;
                }
                node = node->next;
        }
        return 0;
}

void
ll_append(struct ll *list, struct ll_node *node)
{
        node->last = list->tail;
        if(node->last){
                node->last->next = node;
        }
        node->next = NULL;
        list->tail = node;
        if(!list->head){
                list->head = node;
        }
        list->size++;
}

void
ll_prepend(struct ll *list, struct ll_node *node)
{
        list->head->last = node;
        node->next = list->head;
        list->head = node;
        list->size++;
}

struct ll_node*
ll_first(struct ll *list)
{
        struct ll_node *node = list->head;
        if(node){
                list->head = node->next;
                list->head->last = NULL;
                list->size--;
        }
        return node;
}

struct ll_node*
ll_first_peek(struct ll *list)
{
        return list->head;
}

struct ll_node*
ll_last(struct ll *list)
{
        struct ll_node *node = list->tail;
        if(node){
                list->tail = node->last;
                list->tail->next = NULL;
                list->size--;
        }
        return node;
}

struct ll_node*
ll_last_peek(struct ll *list)
{
        return list->tail;
}

void
ll_remove(struct ll *list, struct ll_node *node)
{
        if(node->last){
                node->last->next = node->next;
        }else{
                // this node is the head of the list
                list->head = node->next;
        }
        if(node->next){
                node->next->last = node->last;
        }else{
                // this node is the tail
                list->tail = node->last;
        }
        list->size--;

        node->next = NULL;
        node->last = NULL;
}
