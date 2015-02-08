all: build

build:
	cd linkedlist && make
	cd hashtable && make

test:
	./linkedlist/test/test-list
	./hashtable/test/test-hashtable
