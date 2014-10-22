#include "pqueue.h"
#include <stdlib.h>
#include <sys/time.h>

/** PRIVATE METHOD DEFINITIONS **/

void perculateUp(pqueue_t* pqueue);
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

void enqueue(pqueue_t* pqueue, ucontext_t* context, int ran){
	if(pqueue->size == pqueue->max_size){
		//RESIZE THE QUEUE
		return;
	}
	uthread_t* thread = malloc(sizeof(uthread_t));
	thread->ucp = context;
	thread->time_ran.tv_sec = 0;
	thread->time_ran.tv_usec = 0;
	thread->threadID = pqueue->size;
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
		if(child + 1 < pqueue->size &&  timercmp(pqueue->queue[parent]->time_ran, pqueue->queue[child]->time_ran, ==)){
			if(pqueue->queue[child]->threadID > pqueue->queue[child + 1]->threadID){
				child++;
			}
		}
		else if(child + 1 < pqueue->size && timercmp(pqueue->queue[parent]->time_ran, pqueue->queue[child]->time_ran, >)){
			child++;
		}
		if(timeCmp >= 0
			 && pqueue->queue[child]->threadID >= pqueue->queue[parent]->threadID){
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