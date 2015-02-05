/*
 * Copyright (c) 2014 Phil Lopreiato
 *
 * This program is licensed under the MIT license.
 * You should have recieved a copy of the full license terms
 * with this source code. If not, you can find it here: http://opensource.org/licenses/MIT
 */

#include "../linkedlist/linkedlist.h"

#ifndef FILE_HASHTABLE
#define FILE_HASHTABLE

#define ENABLE_REBALANCE 1
#define DISABLE_REBALANCE 0

// will not be a 1-1 function
// there may be more than one value for a given key
struct ht_node{
    char *key;
    void *value;
    int hash;
    int file_index;
    unsigned short rebal;       // number of times this node has been rebalanced
};

struct ht{
    unsigned short size;        // number of buckets in the list
    unsigned short used;        // number of buckets in use
    unsigned short current_max; // current largest bucket size
    unsigned short max_length;  // max size of a bucket list
    void(*hash_func)(struct ht_node*); // hash function we use
    int(*node_equal)(struct ht_node*, struct ht_node*);// compare two nodes
    float fill_pct;             // max percent of bucket fillage
    struct ll **buckets;
    unsigned short rebal_count; // number of times the table has been rebalanced
    unsigned short in_rebalance;// flag for when we're rebalancing
    unsigned short allow_rebal; // let the table rebalance?
    unsigned short node_count;  // number of nodes in the table
};

// initialize a hash table with the given number of buckets
struct ht*
ht_init(unsigned short size, unsigned short max_length, float fill_pct, unsigned short allow_rebal, void(*hash_node)(struct ht_node*), int(*node_equal)(struct ht_node*, struct ht_node*));

// create a node (key, value, hash code)
struct ht_node*
ht_create_node(char* key, void* value, int file_index);

// put something into the hashtable
void
ht_insert(struct ht* table, struct ht_node* node);

// check if we need to rebalance the table, accoring to our params
unsigned short
ht_check_rebalance(struct ht* table);

// actually rebalance the table
void
ht_rebalance(struct ht** table);

// lookup a key/value pair
struct ht_node*
ht_lookup(struct ht* table, struct ht_node* data);

// lookup a key
struct ll*
ht_lookup_key(struct ht* table, int hash);

//  get the bucket associated node data
struct ll*
ht_get_bucket(struct ht* table, int hash);

void
ht_print(struct ht* table);

void
ht_print_node(struct ll_node* node);

void
ht_print_stats(struct ht* table);

// free all memory associated with the hash table
void
ht_free(struct ht* table);

void
ht_free_node(struct ll_node* node);

#endif
