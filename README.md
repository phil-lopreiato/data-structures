# GWU CSCI 3411 F15 HW1
## Data Structures in C!

This assignment contains three (3) parts:
 - Linked List (single, double, and circular links)
 - Binary Search Tree
 - Priority Queue

### Compiling
From the root directory, run `make`, which will compile all the code. If you want to compile one part individually, you can run `make` in a subdirectory. To compile with debug symbols, edit `vars.mk` in this directory and append `-g` to the variable `CFLAGS`.

### Unit Testing
From the root directory, run `make test`, which will compile all the code, then go through each data structure and run its unit tests. To run the tests for each data specific part, you can run `make && make test` in a subdirectory. Code for the tests can be found in a `test` subdirectory within the directory for each part.

### Implementing On Your Own
Each directory contains the relevant API spec for its data structure. In general, you will have to include the structure's header and link in the compiled object file.
