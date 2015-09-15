#include <stdlib.h>
#include <stdio.h>

#include "bst_internal.h"


/* Allocate memory for a bst */
struct bst*
bst_init(CMP_FUNC)
{
        struct bst* tree = malloc(sizeof(struct bst));
        tree->size = 0;
        tree->compare = compare;
        tree->root = NULL;
        return tree;
}

/* Return the number of elements in the tree (in constant time) */
int
bst_get_size(struct bst* tree)
{
        return tree->size;
}

/* Place a node with the given data into the tree */
int
bst_insert(struct bst* tree, void* data)
{
        int node_cmp;
        struct bst_node* test_node;
        struct bst_node* last_node;
        struct bst_node* node;

        if (!data) return -1;
        node = malloc(sizeof(struct bst_node));
        if (!node) return -1;
        node->data = data;
        node->parent = NULL;
        node->right = NULL;
        node->left = NULL;

        tree->size++;
        if (tree->size == 1) {
                // nothing in the tree, this is the new head
                // (and only node)
                tree->root = node;
                return 0;
        }

        // otherwise, traverse down the tree finding the right parent
        // to insert under
        test_node = tree->root;
        last_node = NULL;
        while(test_node) {
                node_cmp = tree->compare(data, test_node->data);
                last_node = test_node;
                if (node_cmp < 0) {
                        test_node = test_node->left;
                } else {
                        test_node = test_node->right;
                }
        }

        // insert the node as the proper child of its parent
        node_cmp = tree->compare(data, last_node->data);
        node->parent = last_node;
        if (node_cmp < 0) {
                last_node->left = node;
        } else {
                last_node->right = node;
        }
        return 0;
}

/* Remove a node from the tree with the given value
 * DOES NOT FREE THE NODE OR ITS DATA */
struct bst_node*
bst_delete(struct bst* tree, void* data)
{
        struct bst_node* node = bst_search(tree, data);
        if (!node) return NULL;
        __bst_delete_internal(tree, node);
        tree->size--;
        return node;
}

/* Find a node with a given value in the tree */
struct bst_node*
bst_search(struct bst* tree, void* data)
{
        if (!tree || !data) return NULL;
        return __bst_search_internal(tree->root, data, tree->compare);
}

/* Do an in-order traversal of the tree and print each node */
void
bst_print(struct bst* tree, NODE_PRINT_FUNC)
{
        bst_print_recursive(tree->root, print);
        printf("\n");
}

/* In-order traversal recursive method */
static void
bst_print_recursive(struct bst_node* root, NODE_PRINT_FUNC)
{
        if (!root) return;

        bst_print_recursive(root->left, print);
        (*print)(root->data);
        printf("->");
        bst_print_recursive(root->right, print);
}

/* Perform a different deletion algorithm based on
 * the number of the node's children */
static void
__bst_delete_internal(struct bst* tree, struct bst_node* node)
{
        if (!node) return;

        if (!node->left && !node->right) {
                // node is a leaf, easy to delete
                __bst_delete_leaf(tree, node);
                return;
        }
        if (node->left && node->right) {
                // node has two children
                __bst_delete_two_children(tree, node);
                return;
        }

        // or, node has one child
        __bst_delete_one_child(tree, node);
}

/* Delete a leaf from the tree.
 * Get the node's parent and set the right child to NULL */
static void
__bst_delete_leaf(struct bst* tree, struct bst_node* node)
{
        struct bst_node* parent = node->parent;
        if (!parent) {
                // node is also the root
                tree->root = NULL;
        } else if (parent->left == node){
                parent->left = NULL;
        } else if (parent->right == node) {
                parent->right = NULL;
        }
}

/* Delete a node with one child
 * Replace the to-be-deleted node with its child
 * e.g. make the parent's child this node's child */
static void
__bst_delete_one_child(struct bst* tree, struct bst_node* node)
{
        struct bst_node* child;
        struct bst_node* parent = node->parent;
        if (node->left) child = node->left;
        else child = node->right;

        if (parent == NULL) {
                // node is the head, set child as new root
                child->parent = NULL;
                tree->root = child;
                return;
        }

        // otherwise, set the child of the parent
        // to this node's child
        if (parent->left == node) {
                parent->left = child;
        } else {
                parent->right = child;
        }
}

static void
__bst_delete_two_children(struct bst* tree, struct bst_node* node)
{
        // make this node's value that of its in-order successor and delete that
        // in-order-sucessor will be the min value of the right subtree
        struct bst_node* next = __find_min(node->right);
        node->data = next->data;
        __bst_delete_internal(tree, node->right);
}

/* Find the smallest value in a given subtree
 * Will be the left-most leaf */
static struct bst_node*
__find_min(struct bst_node* root)
{
        struct bst_node* node = root;
        while(node && node->left) {
                node = node->left;
        }
        return node;
}

/* Recursive searching call */
static struct bst_node*
__bst_search_internal(struct bst_node* root, void* data, CMP_FUNC)
{
        int node_cmp;
        if (!root) return NULL;

        node_cmp = compare(data, root->data);
        if (node_cmp == 0) {
                return root;
        } else if (node_cmp < 0) {
                return __bst_search_internal(root->left, data, compare);
        } else {
                return __bst_search_internal(root->right, data, compare);
        }
}
