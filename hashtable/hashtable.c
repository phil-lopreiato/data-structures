/*
 * Copyright (c) 2014 Phil Lopreiato
 * 
 * This program is licensed under the MIT license. 
 * You should have recieved a copy of the full license terms 
 * with this source code. If not, you can find it here: http://opensource.org/licenses/MIT
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashtable.h"
#include "../linkedlist/linkedlist.h"

/* Initialize a hash table.
 * Takes arguments for num buckets, max elements/bucket,
 * Max % of buckets to be filled, function for hashing nodes,
 * and function for equality comparison
 */
ht *ht_init(unsigned short size, unsigned short max_length, float fill_pct, unsigned short allow_rebal, void(*hash_node)(ht_node*), int(*node_equal)(ht_node*, ht_node*)){
    ht *table = malloc(sizeof(ht));
    table->size = size;
    table->used = 0;
    table->max_length = max_length;
    table->fill_pct = fill_pct;
    table->buckets = calloc(size, sizeof(ll));
    table->rebal_count = 0;
    table->in_rebalance = 0;
    table->allow_rebal = allow_rebal;
    table->hash_func = hash_node;
    table->node_equal = node_equal;
    table->current_max = 0;
    table->node_count = 0;
    for(int i=0; i<size; i++){
        table->buckets[i] = ll_init();
    }
    return table;
}

/* Create a node that's ready to be inserted into the hashtable */
ht_node *ht_create_node(char *key, void *value, int file_index){
    if(!key || !value) return NULL;
    ht_node *node = malloc(sizeof(ht_node));
    node->key = key;
    node->value = value;
    node->rebal = 0;
    node->hash = -1;
    node->file_index = file_index;
    return node;
}

/* Insert a node into the hashtable if it doesn't already exist */
void ht_insert(ht *table, ht_node *node){
    ll *list;
    ht_node *lookup;

    if(!node || !table || table->size == 0) return;

    /* First, calculate the hashcode for the node */
    (*table->hash_func)(node);

    /* Keep this node's rebalance count in sync with the table's */
    node->rebal = table->rebal_count; 

    list = ht_get_bucket(table, node->hash);
    lookup = ht_lookup(table, node);

    if(!lookup || table->in_rebalance){
        /* If the node doesn't already exist in the table, insert it into the proper list */
        ll_node *insert = ll_create_node(node);
        ll_append(list, insert);

        if(list->size == 1){
            // if we're adding on a list with no prior elements
            table->used++;
        }

        if(list->size > table->current_max){
            // update the max list size, if this one's the largest
            table->current_max = list->size;
        }

        table->node_count++;
    }
}

unsigned short ht_check_rebalance(ht *table){
    // we want to rebalance our table if:
    // A list is over the maximum allowed length OR
    // most than the specified buckets are occupied
    
    unsigned short allowed_buckets = (unsigned short)(table->fill_pct * table->size);
    return !table->in_rebalance && 
                (table->used > allowed_buckets || 
                 table->current_max > table->max_length); 
}

/* If we need to, enlarge the size of the table so we can reduce the length of the lists */
void ht_rebalance(ht **table){
    while(ht_check_rebalance(*table)){
        ll **buckets = (*table)->buckets;
        int oldsize = (*table)->size;
        ht *oldtable = *table;
        *table = ht_init(oldsize*2, (*table)->max_length, (*table)->fill_pct, (*table)->allow_rebal, (*table)->hash_func, (*table)->node_equal);
        free(oldtable);

        (*table)->in_rebalance = 1;
        for(int i=0; i<oldsize; i++){
            ll *bucket = buckets[i];
            ll_node *node = bucket->head;
            while(node){
                ht_node *data = (ht_node*)node->data;
                ll_node *temp = node->next;
                free(node);
                ht_insert(*table, data);
                node = temp;
            }
        }
        free(buckets);
        (*table)->in_rebalance = 0;
    }
}

/* Check and see if a node exists in the hashtable */
ht_node *ht_lookup(ht *table, ht_node *lookup){ 
    ll *list = ht_get_bucket(table, lookup->hash);
    ll_node *check_node = list->head;
    while(check_node){
        ht_node *data = (ht_node*)check_node->data;
        /* Use the client supplied equality function to see if the nodes are equal */
        if((*table->node_equal)(data, lookup)){
            return data;
        }
        check_node = check_node->next;
    }
    // Node doesn't exist :(
    return NULL;
}

/* Get a list of all the nodes that have a certain key (regardless of value) */
ll *ht_lookup_key(ht* table, int hash){
    ll *output = ll_init();
    ll *list = ht_get_bucket(table, hash);
    ll_node *check_node = list->head;
    while(check_node){
        ht_node *data = (ht_node*)check_node->data;
        /* Since hash is based on key, we can compare those */
        if(data->hash == hash){
            ll_node *node = ll_create_node(data);
            ll_append(output, node);
        }
        check_node = check_node->next;
    }
    return output;
}

/* Take the node's hashcode, mod with bucket size to get the bucket */
ll *ht_get_bucket(ht *table, int hash_code){
    int bucket = hash_code % table->size;
    return table->buckets[bucket];
}

/* Print out the hash table! */
void ht_print(ht *table){
    for(int i=0; i<table->size; i++){
        ll *bucket = table->buckets[i];
        ll_print(bucket, &ht_print_node);
    }
}

/* Function to show some states about the hashtable */
void ht_print_stats(ht *table){
    unsigned short allowed_buckets = (unsigned short)(table->fill_pct * table->size);
    printf("Hashtable size: %u\n", table->size);
    printf("Autobalancing enabled? %s\n", table->allow_rebal?"Yes":"No");
    printf("Buckets used: %u\n", table->used);
    printf("Number of nodes: %u\n", table->node_count);
    printf("Largest bucket: %u\n", table->current_max);
    printf("Max bucket size: %u\n", table->max_length); 
    printf("Max number of used buckets: %u\n",allowed_buckets);
}

/* Function for printing the nodes we've inserted into the linkedlists */
void ht_print_node(ll_node *node){
    ht_node *data = (ht_node*)(node->data);
    char *value = (char*)data->value;
    printf("[(%s, %s - %d): %d]", data->key, value, data->file_index, data->hash);
}

/* Free a hashnode */
void ht_free_node(ll_node *node){
    ht_node *data = node->data;
    free(data);
}

/* Free the hashtable */
void ht_free(ht *table){
    for(int i=0; i<table->size; i++){
       ll_free(table->buckets[i], &ht_free_node); 
    }
    free(table->buckets);
    free(table);
}
