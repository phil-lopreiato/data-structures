include ../../vars.mk

all: bst_test

bst_test: test-bst.c
	$(CC) $(CFLAGS) test-bst.c -o test-bst.out ../bst.o

run: bst_test
	./test-bst.out

clean:
	rm -f test-bst.out
