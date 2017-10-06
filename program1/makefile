all: llist.o tests_pt2 tests_pt1 tester


tests_pt2: llist.o tests_pt2.c
	gcc -std=c99 tests_pt2.c llist.o -o tests_pt2

tests_pt1: llist.o tests_pt1.c
	gcc -std=c99 tests_pt1.c llist.o -o tests_pt1
tester: llist.o tester.c
	gcc -std=c99 tester.c llist.o -o tester


llist.o: list.h llist.c
	gcc -std=c99 -c llist.c

clean:
	rm tests_pt1 tests_pt2 llist.o tester
