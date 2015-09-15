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
        if(list->tail){
                list->tail->next = node;
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
        struct ll_node *node = list->head;
        struct ll_node *temp;
        while(node) {
                if (node->next && node->next == list->tail) {
                        temp = list->tail;
                        node->next = NULL;
                        list->tail = node;
                        list->size--;
                        return temp;
                }
                node = node->next;
        }
        return NULL;
}

struct ll_node*
ll_last_peek(struct ll *list)
{
        return list->tail;
}

void
ll_remove(struct ll *list, struct ll_node *node)
{
        if (!list) return;
        if (list->head == node){
                // this node is the head of the list
                ll_first(list);
        } else if (list->tail == node) {
                // remove the tail
                ll_last(list);
        } else {
                struct ll_node* iter = list->head;
                while(iter) {
                        if (iter->next && iter->next == node) {
                                iter->next = node->next;
                                node->next = NULL;
                                list->size--;
                                break;
                        }
                        iter = iter->next;
                }
        }

}
