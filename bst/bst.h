#ifndef BST_H
#define BST_H

// A function to compare the two datas
// return 0 if equal, <0 if arg1 < arg2, else >0
#define CMP_FUNC int(*compare)(void*, void*)

// A function to print the contents of a node
#define NODE_PRINT_FUNC void(*print)(void* data)

struct bst_node {
        void* data;
        struct bst_node* parent;
        struct bst_node* left;
        struct bst_node* right;
};

struct bst {
        struct bst_node* root;
        int size;
        CMP_FUNC;
};

// Initialize an empty array-based BST
struct bst* bst_init(CMP_FUNC);

// get the size of a bst
int bst_get_size(struct bst* tree);

// insert a node with the given data
// return 0 if successful
int bst_insert(struct bst* tree, void* data);

// remove a node from the tree
// NODE IS NOT FREED
struct bst_node* bst_delete(struct bst* tree, void* data);

// search for a node with the given data in the tree
struct bst_node* bst_search(struct bst* tree, void* data);

// print the tree in order
void bst_print(struct bst* tree, NODE_PRINT_FUNC);

#endif
