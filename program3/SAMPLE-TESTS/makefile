
test:  test.c bst.o
	gcc -o test test.c bst.o

bst.o: bst.c bst.h
	gcc -c bst.c

clean:
	rm -f bst.o test test.exe
