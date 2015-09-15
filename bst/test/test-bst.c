#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../bst.h"

int compare(void* arg1, void* arg2);
void print(void* data);
void assertEmptyTree(struct bst* tree);
void assertSingleItemTree(struct bst* tree, int* root);
void assertTwoItemTree(struct bst* tree, int* root);
void assertThreeItemTree(struct bst* tree, int* root);

int
main()
{
        struct bst* tree;
        struct bst_node* node;
        int val1 = 4, val2 = 7, val3 = 2;

        printf("Testing bst...\n");

        tree = bst_init(&compare);

        printf("Checking memory has been allocated...");
        assert(tree);
        printf("OK\n");

        assertEmptyTree(tree);

        printf("Inserting one value...\n");
        bst_insert(tree, &val1);
        assertSingleItemTree(tree, &val1);

        printf("Ensuring we can search for one value...");
        node = bst_search(tree, &val1);
        assert(node != NULL);
        assert(compare(node->data, &val1) == 0);
        printf("OK\n");

        printf("Ensuring we can delete one value...\n");
        bst_delete(tree, &val1);
        assertEmptyTree(tree);

        printf("Adding two nodes...\n");
        bst_insert(tree, &val1);
        bst_insert(tree, &val2);
        assertTwoItemTree(tree, &val1);

        printf("Deleting two nodes...\n");
        bst_delete(tree, &val1);
        assertSingleItemTree(tree, &val2);
        bst_delete(tree, &val2);
        assertEmptyTree(tree);

        printf("Adding three nodes...\n");
        bst_insert(tree, &val1);
        bst_insert(tree, &val2);
        bst_insert(tree, &val3);
        assertThreeItemTree(tree, &val1);

        printf("Deleting three nodes...\n");
        bst_delete(tree, &val1);
        assertTwoItemTree(tree, &val2);
        bst_delete(tree, &val2);
        assertSingleItemTree(tree, &val3);
        bst_delete(tree, &val3);
        assertEmptyTree(tree);

        printf("Printing a tree with three nodes (%d, %d, %d):...\n", val1, val2, val3);
        bst_insert(tree, &val1);
        bst_insert(tree, &val2);
        bst_insert(tree, &val3);
        bst_print(tree, &print);

        printf("All bst tests passed!\n\n");
}

void
assertEmptyTree(struct bst* tree)
{
        printf("Checking tree has 0 size...");
        int size = bst_get_size(tree);
        assert(size == 0);
        printf("OK\nChecking root is null...");
        assert(tree->root == NULL);
        printf("OK\n");
}

void
assertSingleItemTree(struct bst* tree, int* root)
{
        printf("Checking tree has 1 size...");
        int size = bst_get_size(tree);
        assert(size == 1);
        assert(tree->root != NULL);
        printf("OK\nChecking root node is correct...");
        assert(compare(tree->root->data, root) == 0);
        printf("OK\n");
}

void
assertTwoItemTree(struct bst* tree, int* root)
{
        printf("Checking tree has 2 size...");
        int size = bst_get_size(tree);
        assert(size == 2);
        assert(tree->root != NULL);
        printf("OK\nChecking root node is correct...");
        assert(compare(tree->root->data, root) == 0);
        printf("OK\nChecking root has a child...");
        assert(tree->root->left || tree->root->right);
        printf("OK\n");
}

void
assertThreeItemTree(struct bst* tree, int* root)
{
        printf("Checking tree has 3 size...");
        int size = bst_get_size(tree);
        assert(size == 3);
        assert(tree->root != NULL);
        printf("OK\nChecking root node is correct...");
        assert(compare(tree->root->data, root) == 0);
        printf("OK\nChecking root has two children...");
        assert(tree->root->left && tree->root->right);
        printf("OK\nChecking left < right...");
        assert(compare(tree->root->left->data, root) < 0);
        assert(compare(tree->root->right->data, root) > 0);
        printf("OK\n");
}

int
compare(void* arg1, void* arg2)
{
        int val1 = *(int*)arg1;
        int val2 = *(int*)arg2;

        if (val1 == val2) return 0;
        if (val1 < val2) return -1;
        else return 1;
}

void
print(void* data)
{
        printf("%d", *(int*)data);
}
