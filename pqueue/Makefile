include ../vars.mk

.PHONY: test

all: pqueue

pqueue: pqueue.c
	$(CC) $(CFLAGS) -c pqueue.c

test:
	cd test && make run

clean:
	rm -f pqueue.o
	cd test && make clean
