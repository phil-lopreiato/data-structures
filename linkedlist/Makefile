
all: linkedlist tests

linkedlist:
	gcc -std=c99 -pedantic -Wall -c linkedlist.c

tests:
	cd test && make

clean:
	rm linkedlist.o
	cd test && rm test_list
