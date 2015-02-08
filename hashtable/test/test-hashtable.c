#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../hashtable.h"

#define BUCKET_COUNT 3

void hash_node(struct ht_node* node);
int node_compare(struct ht_node* node1, struct ht_node* node2);
void assertSimpleCreate(struct ht* table);

int
main()
{
        struct ht* table;
        int val1 = 2, val2 = 4, val3 = 7;

        printf("Testing hashtable...\n");

        table = ht_init_simple(BUCKET_COUNT, &hash_node, &node_compare);
        /* Assert that we've gotten memory for our table */
        printf("Checking table has been allocated... ");
        assert(table);
        printf("OK\n");
}

void hash_node(struct ht_node* node){
        int sum = 0;
        char *str = node->key;
        while(*str) { sum += *str++; }
        node->hash = sum;
}

int node_compare(struct ht_node* node1, struct ht_node* node2){
    return  node1->hash == node2->hash;
}
