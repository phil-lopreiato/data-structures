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

#include "linkedlist.h"

#ifndef FILE_HASHTABLE
#define FILE_HASHTABLE

#define ENABLE_REBALANCE 1
#define DISABLE_REBALANCE 0

// will not be a 1-1 function
// there may be more than one value for a given key
typedef struct ht_node{
    char *key;
    void *value;
    int hash;
    int file_index;
    unsigned short rebal;       // number of times this node has been rebalanced
} ht_node;

typedef struct ht{
    unsigned short size;        // number of buckets in the list
    unsigned short used;        // number of buckets in use
    unsigned short current_max; // current largest bucket size
    unsigned short max_length;  // max size of a bucket list
    void(*hash_func)(ht_node*); // hash function we use
    int(*node_equal)(ht_node*, ht_node*);// compare two nodes
    float fill_pct;             // max percent of bucket fillage
    ll **buckets;
    unsigned short rebal_count; // number of times the table has been rebalanced
    unsigned short in_rebalance;// flag for when we're rebalancing
    unsigned short allow_rebal; // let the table rebalance?
    unsigned short node_count;  // number of nodes in the table
} ht;

// initialize a hash table with the given number of buckets
ht *ht_init(unsigned short, unsigned short, float, unsigned short, void(*hash_node)(ht_node*), int(*node_equal)(ht_node*, ht_node*));

// create a node (key, value, hash code)
ht_node *ht_create_node(char*, void*, int);

// put something into the hashtable
void ht_insert(ht*, ht_node*);

// check if we need to rebalance the table, accoring to our params
unsigned short ht_check_rebalance(ht*);

// actually rebalance the table
void ht_rebalance(ht**);

// lookup a key/value pair
ht_node *ht_lookup(ht*,ht_node*);

// lookup a key
ll *ht_lookup_key(ht*, int);

//  get the bucket associated node data
ll *ht_get_bucket(ht*, int);

void ht_print(ht*);
void ht_print_node(ll_node*);
void ht_print_stats(ht*);

// free all memory associated with the hash table
void ht_free(ht*);

void ht_free_node(ll_node*);

#endif
