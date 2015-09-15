.PHONY: all linkedlist bst pqueue test clean

all: linkedlist bst pqueue

linkedlist:
	cd linkedlist && make

bst:
	cd bst && make

pqueue:
	cd pqueue && make

test: linkedlist bst pqueue
	cd linkedlist && make test
	cd bst && make test
	cd pqueue && make test

clean:
	cd linkedlist && make clean
	cd bst && make clean
	cd pqueue && make clean
