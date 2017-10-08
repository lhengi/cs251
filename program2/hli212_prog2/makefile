all: sq.o fdriver

fdriver: sq.o driver.c
	gcc -std=c99 driver.c sq.o -o fdriver

sq.o: sq.h sq.c
	gcc -std=c99 -c sq.c

clean:
	rm fdriver sq.o
