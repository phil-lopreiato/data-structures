#ifndef BST_INTERNAL_H
#define BST_INTERNAL_H

#include "bst.h"

/* Intenal bst function declarations */

static struct bst_node*
__bst_search_internal(struct bst_node* root, void* data, CMP_FUNC);

static void
__bst_delete_internal(struct bst* tree, struct bst_node* node);

static void
__bst_delete_leaf(struct bst* tree, struct bst_node* node);

static void
__bst_delete_one_child(struct bst* tree, struct bst_node* node);

static void
__bst_delete_two_children(struct bst* tree, struct bst_node* node);

static struct
bst_node* __find_min(struct bst_node* root);

static void
bst_print_recursive(struct bst_node* root, NODE_PRINT_FUNC);

#endif
