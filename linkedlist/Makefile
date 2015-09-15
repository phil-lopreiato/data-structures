include ../vars.mk

.PHONY: test

all: double single circular

core:
	$(CC) $(CFLAGS) -c linkedlist_core.c

double: core
	$(CC) $(CFLAGS) -c double_linkedlist.c

single: core
	$(CC) $(CFLAGS) -c single_linkedlist.c

circular: core
	$(CC) $(CFLAGS) -c circular_linkedlist.c

test:
	cd test && make run

clean:
	rm -f linkedlist_core.o
	rm -f double_linkedlist.o
	rm -f single_linkedlist.o
	rm -f circular_linkedlist.o
	cd test && make clean
