
# TODO:  add a rule for compiling qsort.c into qsort
all: io.o llist.o msort qsort

io.o: list.h io.c io.h
	gcc -c io.c

llist.o: list.h llist.c
	gcc -c llist.c


msort: msort.c io.o llist.o
	gcc msort.c llist.o io.o -o msort

qsort: qsort.c io.o llist.o
	gcc qsort.c llist.o io.o -o qsort


clean:  
	rm -f msort qsort *.o

