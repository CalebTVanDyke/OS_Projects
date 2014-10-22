all: testfile

testfile: main.o pqueue.o uthread.o
	gcc -g -o test main.o pqueue.o uthread.o -pthread

main.o: main.c
	gcc -c main.c

pqueue.o: pqueue.c
	gcc -c pqueue.c

uthread.o: uthread.c
	gcc -c uthread.c