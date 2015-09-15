#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../pqueue.h"

#define SIZE 10

void assertEmptyQueue(struct pqueue* queue);
void assertQueue(struct pqueue* queue, int size, int* max, int maxPri);
void print(void* data);

int
main()
{
        struct pqueue* queue;
        struct pqueue_node* node;
        void* max;
        int val1 = 2, val2 = 4, val3 = 8;
        int pri1 = 5, pri2 = 1, pri3 = 12;
        int pri4 = 15;

        printf("Testing Priority Queue...\n");

        queue = pqueue_init(SIZE);

        printf("Checking memory has been allocated...");
        assert(queue);
        printf("OK\n");

        assertEmptyQueue(queue);

        printf("Inserting one item...\n");
        pqueue_insert(queue, &val1, pri1);
        assertQueue(queue, 1, &val1, pri1);

        printf("Dequeueing one item...\n");
        max = pqueue_extract_max(queue);
        assert(max == &val1);
        assertEmptyQueue(queue);

        printf("Inserting two items...\n");
        pqueue_insert(queue, &val1, pri1);
        pqueue_insert(queue, &val2, pri2);
        assertQueue(queue, 2, &val1, pri1);

        printf("Dequeueing first item...\n");
        max = pqueue_extract_max(queue);
        assert(max == &val1);
        assertQueue(queue, 1, &val2, pri2);

        printf("Dequeueing second item...\n");
        max = pqueue_extract_max(queue);
        assert(max == &val2);
        assertEmptyQueue(queue);

        printf("Inserting three items...\n");
        pqueue_insert(queue, &val1, pri1);
        pqueue_insert(queue, &val2, pri2);
        pqueue_insert(queue, &val3, pri3);
        assertQueue(queue, 3, &val3, pri3);

        printf("Dequeueing three items...\n");
        max = pqueue_extract_max(queue);
        assert(max == &val3);
        assertQueue(queue, 2, &val1, pri1);
        max = pqueue_extract_max(queue);
        assert(max == &val1);
        assertQueue(queue, 1, &val2, pri2);
        max = pqueue_extract_max(queue);
        assert(max == &val2);
        assertEmptyQueue(queue);

        printf("Creating queue to check priority changes...\n");
        node = pqueue_insert(queue, &val1, pri1);
        pqueue_insert(queue, &val2, pri2);
        pqueue_insert(queue, &val3, pri3);
        assertQueue(queue, 3, &val3, pri3);

        printf("Increasing element priority...\n");
        pqueue_increase(queue, node, pri4);
        assertQueue(queue, 3, &val1, pri1 + pri4);

        printf("Decreasing element priority...\n");
        pqueue_change(queue, node, pri1);
        assertQueue(queue, 3, &val3, pri3);

        printf("Printing a queue with three nodes {%d, %d}, {%d, %d}, {%d, %d}...\n", val1, pri1, val2, pri2, val3, pri3);
        pqueue_print(queue, &print);

        printf("All Priority Queue tests passed!\n");
}

void
assertEmptyQueue(struct pqueue* queue)
{
        printf("Checking size is 0...");
        assert(pqueue_size(queue) == 0);
        printf("OK\n");
}

void
assertQueue(struct pqueue* queue, int size, int* val, int pri)
{
        printf("Checking size is %d...", size);
        assert(pqueue_size(queue) == size);
        printf("OK\nChecking root is correct...");
        struct pqueue_node* node = queue->data[0];
        assert(node->data == val);
        assert(node->priority == pri);
        printf("OK\n");
}

void
print(void* data)
{
        printf("%d", *(int*)data);
}
