#ifndef PQUEUE_H
#define PQUEUE_H 1

typedef struct p_queue_node{
	int* queue;
	int size;
	int max_size;
} pqueue_t;

/**
 *  Initializes the queue to hold a maximum amount of elements
 *      
 *      @param the max size of the queue
 *      @return a reference to the queue
 */
pqueue_t* init_queue(int size);
/**
 *  Adds the data and priority to the priority queue
 *      
 *      @param pqueue the root of the priority queue
 *		@param data the data to be added
 *		@param priority the priority of the data to be added
 */
void add(pqueue_t* pqueue, int data);

/**
 *  Returns the front of the priority queue but does not remove it
 *      
 *      @param pqueue the root of the priority queue
 *      @return the top of the queue
 */
int peek(pqueue_t* pqueue);

/**
 *  Returns the top of the priority queue and refreshes the queue to have the new highest priority at the top
 *      
 *      @param pqueue the root of the priority queue
 *      @return the top of the queue
 */
int remove(pqueue_t* pqueue);

#endif
