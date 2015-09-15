#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../linkedlist.h"

void assertEmptyList(struct ll *list);
void assertListNode(struct ll_node *node, int val);
void assertSingleItem(struct ll *list);
void assertMultiItem(struct ll *list);
void assertDequeue(struct ll *list);
void assertClear(struct ll *list);
void assertFree(struct ll *list);
int compare(void* data1, void* data2);

int main(){
        struct ll *list;
        struct ll_node *node, *node2, *node3;
        int val = 4, val2 = 5, val3 = 6, val4 = 10;

        printf("Testing linkedlist...\n");

        list = ll_init();

        /* Assert that we've gotten memory for our list */
        printf("Checking list has been allocated... ");
        assert(list);
        printf("OK\n");

        assertEmptyList(list);

        printf("Inserting nodes... \n");
        node = ll_create_node(&val);
        assertListNode(node, val);

        ll_append(list, node);
        assertSingleItem(list);

        node2 = ll_create_node(&val2);
        node3 = ll_create_node(&val3);
        assert(node2);
        assert(node3);

        ll_append(list, node2);
        ll_prepend(list, node3);
        /* Data should now be 6, 4, 5 */

        printf("Checking list contains new values... ");
        assert(ll_exists(list, &val, &compare));
        assert(ll_exists(list, &val2, &compare));
        assert(ll_exists(list, &val3, &compare));
        assert(!ll_exists(list, &val4, &compare));
        printf("OK\n");

        assertMultiItem(list);
        assertDequeue(list);

        assertClear(list);
        assertFree(list);

        printf("All linkedlist tests passed!\n\n");
}

/* Makes sure that an empty list has all the properties we expect */
void assertEmptyList(struct ll *list){
        printf("Checking list has 0 size...");
        assert(list->size == 0);
        printf("OK\nChecking list head is NULL...");
        assert(list->head == NULL);
        printf("OK\nChecking list tail is NULL...");
        assert(list->tail == NULL);
        printf("OK\n");
}

/* Make sure we allocated a node properly */
void assertListNode(struct ll_node *node, int val){
        printf("Checking node was allocated...");
        assert(node);
        printf("OK\nChecking data in node...");
        assert(compare(node->data, &val));
        printf("OK\n");
}

/* Check the first node got added okay */
void assertSingleItem(struct ll *list){
        assert(list);
        printf("Asserting size is 1...");
        assert(list->size == 1);
        printf("OK\n");
        printf("Checking head and tail are defined... ");
        assert(list->head);
        assert(list->tail);
        assert(list->head == list->tail);
        printf("OK\n");
}

/* Check our three item list is okay */
void assertMultiItem(struct ll *list){
        struct ll_node *head, *tail;
        assert(list);
        printf("Checking list size is 3...");
        assert(list->size == 3);
        printf("OK\nChecking head is 6...");
        head = ll_first_peek(list);
        assert(head);
        assert( *(int*)head->data == 6);
        printf("OK\nChecking tail is 5...");
        tail = ll_last_peek(list);
        assert(tail);
        assert( *(int*)tail->data == 5);
        printf("OK\nChecking size hasn't changed...");
        assert(list->size == 3);
        printf("OK\n");
}

/* Make sure we can dequeue elements in the list, from head and tail */
void assertDequeue(struct ll *list){
        struct ll_node *head, *tail;
        assert(list);
        printf("Checking the head node is correct...");
        head = ll_first(list);
        assert( *(int*)head->data == 6);
        printf("OK\nChecking list state updated properly...");
        assert(list->size == 2);
        assert(list->head != head);
        printf("OK\n");
        printf("Checking the tail node is correct...");
        tail = ll_last(list);
        assert(tail);
        assert( *(int*)tail->data == 5);
        printf("OK\nChecking list state updated properly...");
        assert(list->size == 1);
        assert(list->tail != tail);
        printf("OK\n");
}

void assertClear(struct ll *list){
        assert(list);
        printf("Making sure we can clear the list...");
        assert(ll_get_size(list) == 1);
        ll_clear(list, NULL); // nothing special to free here
        assert(list);
        assert(ll_first_peek(list) == ll_last_peek(list));
        assert(ll_first_peek(list) == NULL);
        assert(ll_get_size(list) == 0);
        printf("OK\n");
}

void assertFree(struct ll *list){
        assert(list);
        printf("Making sure we can free the list...");
        ll_free(list, NULL);
        printf("OK\n");
}

int compare(void* data1, void* data2) {
        return *(int*)data1 == *(int*)data2;
}
