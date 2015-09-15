include ../../vars.mk

all: double_test single_test circular_test

double_test:
	$(CC) $(CFLAGS) test-list.c -o test-double-list.out ../linkedlist_core.o ../double_linkedlist.o

single_test:
	$(CC) $(CFLAGS) test-list.c -o test-single-list.out ../linkedlist_core.o ../single_linkedlist.o

circular_test:
	$(CC) $(CFLAGS) test-list.c -o test-circular-list.out ../linkedlist_core.o ../circular_linkedlist.o

run: double_test single_test circular_test
	./test-double-list.out
	./test-single-list.out
	./test-circular-list.out

clean:
	rm -f ./test-double-list.out
	rm -f ./test-single-list.out
	rm -f ./test-circular-list.out
