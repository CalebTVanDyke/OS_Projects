#include "pqueue.h"
#include <semaphore.h>
#include <sched.h>
#include <stdlib.h>
#include <linux/sched.h>
#include "uthread.h"
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>


/** PRIVATE FUNCTION AND VARIABLE DECLARATIONS **/

pqueue_t* pqueue;
sem_t lock;
void kernel_thread(void * arg);
__thread uthread_t* cur_uthread;

/** PUBLIC FUNCTION IMPLEMENTATIONS **/

void system_init(int max_number_of_klt){
	pqueue = init_queue(10);
	sem_init(&lock, 0, 1);
}

int uthread_create(void (*func)()){
	ucontext_t * context = malloc(sizeof(ucontext_t));
	getcontext(context);
	context->uc_stack.ss_sp = malloc(16384); 
	context->uc_stack.ss_size = 16384;
	makecontext(context, func, 0);
	sem_wait(&lock);
	enqueue(pqueue, context, 0);
	if(pqueue->size == 1){
		void *child_stack;
		child_stack=(void *)malloc(16384); child_stack+=16383;
		sem_post(&lock);
		clone(kernel_thread, child_stack, CLONE_VM|CLONE_FILES, NULL);
	}else{
		sem_post(&lock);
	}

}

void uthread_yield(){
	sem_wait(&lock);
	if(peek(pqueue) == NULL){
		return;
	}
	uthread_t* thread = dequeue(pqueue);
	struct rusage* usage = malloc(sizeof(struct rusage*));
	getusage(getpid(), usage);
	// printf("%d", )
	swapcontext(cur_uthread->ucp, thread);
}

void uthread_exit(){
	sem_wait(&lock);
	free(cur_uthread->ucp);
	free(cur_uthread);
	if(peek(pqueue) == NULL){
		sem_post(&lock);
		exit(0);
	}
	uthread_t* thread = dequeue(pqueue);
	sem_post(&lock);
	cur_uthread = thread;
	setcontext(thread->ucp);
}

/** PRIVATE FUNCTION IMPLEMENTATIONS **/

void kernel_thread(void * arg){
	while(1){
		sem_wait(&lock);
		if(peek(pqueue) == NULL){
			sem_post(&lock);
			exit(0);
		}
		uthread_t* thread = dequeue(pqueue);
		cur_uthread = thread;
		sem_post(&lock);
		setcontext(thread->ucp);
/**		free(thread->ucp);
		free(thread);
		WHERE DO I FREE STUFF?!?!?!?!
**/
	}
}