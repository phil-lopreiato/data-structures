# Binary Search Tree

A tree data structure where every node is greater than its left child and less that its right child.

## Compiling
You can compile a binary by running `make`. The output will be an object file (which means there will be no main method) called `bst.o`

## Linking
When you build your own executable using a bst, you will need to link in the object file you build above. For an example of how to compile a driver file, look at `test/Makefile`.

## API
The complete API can be found in `bst.h`. An example driver can be found in `test/test-bst.c`. Below are some basic functions:

 - Create a new bst: `bst_init()`. Returns a pointer to the main bst struct.
 - Insert a node into the tree: `bst_insert`. You can pass any pointer to be inserted into the tree.
 - Get the size of the tree: `bst_get_size`
 - Delete a node from the tree: `bst_delete`. Pass a `void*` of the data to search for and delete. 
 - Search for a node in the tree: `bst_search`. Pass a `void*` of the data to search for. Returns the node structure if found, `NULL`otherwise.
 - Print the contents of the tree: `bst_print`. This does an in-order traversal of the tree and prints all the nodes out in sorted order. You must pass a pointer to a function with the signature defiend in the macro `NODE_PRINT_FUNC` in `bst.h`. The function needs to know how to print the data within a node. 
  For example, if your data is an int, the print function could look something like:
```c
void print_node(void* daat) {
    printf("$d", *(int*)(data));
} 
```
