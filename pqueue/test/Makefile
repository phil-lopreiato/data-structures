include ../../vars.mk

all: pqueue_test

bst_test: test-pqueue.c
	$(CC) $(CFLAGS) test-pqueue.c -o test-pqueue.out ../pqueue.o

run: bst_test
	./test-pqueue.out

clean:
	rm -f test-pqueue.out
