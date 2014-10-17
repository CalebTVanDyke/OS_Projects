#include "pqueue.h"
#include <stdlib.h>

/** PRIVATE METHOD DEFINITIONS **/

void perculateUp(int* pqueue);
void perculateDown(int* pqueue);

/** PUBLIC METHOD IMPLEMENTATIONS  **/

void init_queue(int size){
	pqueue_t* pqueue = malloc(sizeof(pqueue_t));
	pqueue->queue = malloc(sizeof(int) * size);
	pqueue->size = 0;
	pqueue->max_size = size;
}

void add(int* pqueue, int data){
	if(pqueue->size == pqueue->max_size){
		//RESIZE THE QUEUE
		return;
	}
	pqueue->queue[pqueue->size] = data;
	perculateUp(pqueue);
	size++;
}

int peek(int* pqueue){
	if(size <= 0){
		return 0;
	}
	return pqueue->queue[0];
}

int remove(int* pqueue){
	int ret = pqueue->queue[0];
	pqueue->queue[0] = pqueue->queue[size - 1];
	size--;
	perculateDown(pqueue);
}

/** PRIVATE METHOD IMPLEMENTATIONS **/

void perculateUp(int * pqueue){
	int child = pqueue->size - 1;
	int parent = (child - 1) / 2;
	while(pqueue->queue[parent] > pqueue->queue[child]){
		int temp = pqueue->queue[child];
		pqueue->queue[child] = pqueue->queue[parent];
		pqueue->queue[parent] = temp;
		child = parent;
		parent = (child - 1) / 2;
	}
}

void perculateDown(int * pqueue){
	int parent = 0;
	int child = 2 * parent + 1;
	while(child < pqueue->size){
		if(child + 1 < pqueue->size && pqueue->[child] > pqueue[child + 1]){
			child++;
		}
		if(pqueue->queue[child] >= pqueue->queue[parent]){
			break;
		}
		int temp = pqueue->queue[child];
		pqueue->queue[child] = pqueue->queue[parent];
		pqueue->queue[parent] = temp;
		parent = child;
		child = 2 * parent + 1;
	}
}