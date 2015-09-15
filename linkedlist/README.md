# Linkedlist

Can be built to be a single, double, or circular list. Each can be used as a stack or a queue (append/prepend to the list and read from the head or tail).

## Compiling
You can compile binaries for all types by running `make`. If you want to compile a certain type, you can run `make single`, `make double`, or `make circular`. The output will be an object file (which means there will be no main method) called `single_linkedlist.o`, `double_linkedlist.o`, or `circular_linkedlist.o`, repectively.

## Linking
When you build your own executable using a linkedlist, you will need to link in two object files. One is `linkedlist_core.o` (which can be built separately by running `make core`) and the other is the type-specific object from the previous step. For an example of how to compile a driver file, look at `test/Makefile`.

## API
The complete API can be found in `linkedlist.h`. An example driver can be found in `test/test-list.c`. Below are some basic functions:

 - Create a new linkedlist: `ll_init()`
 - Create a linkedlist node to be inserted: `ll_create_node(void* data)`. You can pass any pointer to be stored as the list's `data` param.
 - You can add a node to the list using `ll_prepend` or `ll_append` to add a node (created with `ll_create_node`) to the beginning or end of the list, respectively.
 - You can return and remove a node from the first or last position in the list using `ll_first` or `ll_last`.
 - Print the contents of the list: `ll_print`. You must pass a pointer to a function with the signature defiend in the macro `NODE_PRINT_FUNC` in `linkedlist.h`. The function needs to know how to print the data within a node.
  For example, if your data is an int, the print function could look something like:
```c
void print_node(struct ll_node* node) {
    printf("$d", *(int*)(node->data));
} 
```
