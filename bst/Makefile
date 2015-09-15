include ../vars.mk

.PHONY: test

all: bst

bst: bst.c bst.h
	$(CC) $(CFLAGS) -c bst.c

test:
	cd test && make run

clean:
	rm -f bst.o
	cd test && make clean
