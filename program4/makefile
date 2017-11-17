
test: test.c bst.o
	gcc -o test test.c pq.o

bst.o: pq.c pq.h
	gcc -g -c pq.c

clean:
	rm -f pq.o test
