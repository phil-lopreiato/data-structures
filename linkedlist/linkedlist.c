/*
 * Copyright (c) 2014 Phil Lopreiato
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"

ll *ll_init(){
    ll *list = malloc(sizeof(ll));
    if(!list) return NULL;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

ll_node *ll_create_node(void *data){
    ll_node *node = malloc(sizeof(ll_node));
    if(!node) return NULL;
    node->data = data;
    node->next = NULL;
    node->last = NULL;
    return node;
}

int ll_get_size(ll *list){
    return list->size;
}

void ll_append(ll *list, ll_node *node){
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

void ll_prepend(ll *list, ll_node *node){
    list->head->last = node;
    node->next = list->head;
    list->head = node;
    list->size++;
} 

ll_node *ll_first(ll *list){
    ll_node *node = list->head;
    if(node){
        list->head = node->next;
        list->head->last = NULL;
        list->size--;
    }
    return node;
}

ll_node *ll_first_peek(ll *list){
    return list->head;
}

ll_node *ll_last(ll *list){
    ll_node *node = list->tail;
    if(node){
        list->tail = node->last;
        list->tail->next = NULL;
        list->size--;
    }
    return node;
}

ll_node *ll_last_peek(ll *list){
    return list->tail;
}

void ll_print(ll *list, void(*print_node)(ll_node*)){
    printf("List has %d elements\n", list->size);
    ll_node *node = list->head;
    while(node){
        (*print_node)(node);
        printf("->");
        node = node->next;
    } 
    printf("\n");
} 

void ll_remove(ll *list, ll_node *node){
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

void ll_clear(ll *list, void(*free_node)(ll_node*)){
    ll_node *node = list->head;
    while(node){
        ll_node *temp = node->next;
        if(free_node){
            (*free_node)(node->data);
        }
        free(node);
        node = temp;
    }
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
}

void ll_free(ll *list, void(*free_node)(ll_node*)){
    ll_clear(list, free_node);
    free(list);
}
