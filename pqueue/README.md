# Priority Queue

A priority queue backed by an array in memory. This means the queue will be a fixed size (supplied at creation time) and can not yet exapand past that.

## Compiling
You can compile a binary by running `make`. The output will be an object file (which means there will be no main method) called `pqueue.o`

## Linking
When you build your own executable using a priority queue, you will need to link in the object file you build above. For an example of how to compile a driver file, look at `test/Makefile`.

## API
The complete API can be found in `pqueue.h`. An example driver can be found in `test/test-pqueue.c`. Below are some basic functions:

 - Create a new priority queue: `pqueue_init()`. Returns a pointer to the main queue struct.
 - Insert a node into the queue with a given priority: `pqueue_insert`. You can pass any pointer to be inserted into the tree as well an an `int` of this value's priority. This will return a pointer to a struct representing the node inserted.
 - Get the size of the queue: `pqueue_size`
 - Extract the data associated with the max priority in the queue: `pqueue_extract_max`
 - Increase the priority of a given node by a given amound: `pqueue_increase`. Pass the node as well an the amount to increase the priority by.
 - Change the priority of a given node: `pqueue_change`. Pass the node as well as the new priority (can be higher or lower than the current value)
 - Print the contents of the queue: `pqueue_print`. You must pass a pointer to a function with the signature defiend in the macro `NODE_PRINT_FUNC` in `pqueue.h`. The function needs to know how to print the data within a node.
  For example, if your data is an int, the print function could look something like:
```c
void print_node(void* daat) {
    printf("$d", *(int*)(data));
} 
```
