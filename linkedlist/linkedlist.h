/*
 * Copyright (c) 2014 Phil Lopreiato
 * 
 * This program is licensed under the MIT license. 
 * You should have recieved a copy of the full license terms 
 * with this source code. If not, you can find it here: http://opensource.org/licenses/MIT
 */

#ifndef FILE_LINKEDLIST
#define FILE_LINKEDLIST
typedef struct ll_node{
    void *data; 
    struct ll_node *next;
    struct ll_node *last;
} ll_node;

typedef struct ll{
    ll_node *head;
    ll_node *tail;
    int size;
} ll;

//initialize empty list
ll *ll_init();

//create a node with the given value
ll_node *ll_create_node(void *value);

int ll_get_size();

//append node to the tail of the list
void ll_append(ll *list, ll_node *node);

//prepend node to the head of the list
void ll_prepend(ll *list, ll_node *node);

//return node from the front of the list
ll_node *ll_first(ll *list);

//return the node from the front of the list without removing it
ll_node *ll_first_peek(ll *list);

//return the node at the tail of the list
ll_node *ll_last(ll *list);

//peek at the tail node without removing it
ll_node *ll_last_peek(ll *list);

void ll_print(ll*, void(*print_node)(ll_node*));

// remove a node from the list
// DOES NOT FREE THE NODE
void ll_remove(ll *list, ll_node *node);

//clear everything in the list
void ll_clear(ll *list, void(*free_node)(ll_node*));

//clear the list and free the given pointer
void ll_free(ll *list, void(*free_node)(ll_node*));
#endif
