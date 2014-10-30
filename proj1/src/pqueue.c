#include "pqueue.h"
#include <stdlib.h>
#include <sys/time.h>
#include <sys/time.h>
#include <sys/resource.h>

/** PRIVATE METHOD DEFINITIONS **/

/**
 * Perculates the last element of the queue up as far as it should go
 * @param pqueue
 */
void perculateUp(pqueue_t* pqueue);
/**
 * Perculates the top element down as far as it should go based on the time
 * it has ran and if the time is the same it will go based on FIFO
 * @param pqueue
 */
void perculateDown(pqueue_t* pqueue);
void pqueue_swap(pqueue_t* pqueue, int first, int second);

/** PUBLIC METHOD IMPLEMENTATIONS  **/

pqueue_t* init_queue(int size){
	pqueue_t* pqueue = malloc(sizeof(pqueue_t));
	pqueue->queue = malloc(sizeof(uthread_t*) * size);
	pqueue->size = 0;
	pqueue->max_size = size;
	return pqueue;
}

void enqueue(pqueue_t* pqueue, uthread_t* thread){
	if(pqueue->size == pqueue->max_size){
		//RESIZE THE QUEUE
		return;
	}
	pqueue->queue[pqueue->size] = thread;
	pqueue->size++;
	perculateUp(pqueue);
}

uthread_t* peek(pqueue_t* pqueue){
	if(pqueue->size <= 0){
		return NULL;
	}
	return pqueue->queue[0];
}

uthread_t* dequeue(pqueue_t* pqueue){
	if(pqueue->size <= 0){
		return NULL;
	}
	uthread_t* ret = pqueue->queue[0];
	pqueue->queue[0] = pqueue->queue[pqueue->size - 1];
	pqueue->size--;
	perculateDown(pqueue);
	return ret;
}

void printQueue(pqueue_t* pqueue){
	printf("------------\n");
	int i = 0;
	for(i = 0; i < pqueue->size; i++){
		printf("thread:%d  time_ran:%ld.%06ld\n\n", pqueue->queue[i]->threadID, pqueue->queue[i]->time_ran->tv_sec, pqueue->queue[i]->time_ran->tv_usec);
	}
	printf("------------\n");
}

/** PRIVATE METHOD IMPLEMENTATIONS **/

void perculateUp(pqueue_t * pqueue){
	int child = pqueue->size - 1;
	int parent = (child - 1) / 2;
	while(timercmp(pqueue->queue[parent]->time_ran, pqueue->queue[child]->time_ran, >)){
		pqueue_swap(pqueue, child, parent);
		child = parent;
		parent = (child - 1) / 2;
	}
}

void perculateDown(pqueue_t * pqueue){
	int parent = 0;
	int child = 2 * parent + 1;
	while(child < pqueue->size){
		if(child + 1 < pqueue->size && timercmp(pqueue->queue[child + 1]->time_ran, pqueue->queue[child]->time_ran, <=)){
			if(timercmp(pqueue->queue[child + 1]->time_ran, pqueue->queue[child]->time_ran, ==)){
				if(pqueue->queue[child + 1]->threadID < pqueue->queue[child]->threadID){
					child++;
				}
			}else{
				child++;
			}
		}
		if(timercmp(pqueue->queue[parent]->time_ran, pqueue->queue[child]->time_ran, ==)){
			if(pqueue->queue[parent]->threadID < pqueue->queue[child]->threadID){
				break;
			}
		}
		else if(timercmp(pqueue->queue[parent]->time_ran, pqueue->queue[child]->time_ran, <)){
			break;
		}
		pqueue_swap(pqueue, child, parent);
		parent = child;
		child = 2 * parent + 1;
	}
}

void pqueue_swap(pqueue_t* pqueue, int first, int second){
	uthread_t* temp = pqueue->queue[first];
	pqueue->queue[first] = pqueue->queue[second];
	pqueue->queue[second] = temp;
}