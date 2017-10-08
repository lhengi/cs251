all: sq.o driver

driver: sq.o driver.c
	gcc -std=c99 driver.c sq.o -o driver

sq.o: sq.h sq.c
	gcc -std=c99 -c sq.c

clean:
	rm driver sq.o
