#define _GNU_SOURCE
#include "pqueue.h"
#include <semaphore.h>
#include <sched.h>
#include <stdlib.h>
#include <linux/sched.h>
#include "uthread.h"
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/syscall.h>


/** PRIVATE FUNCTION AND VARIABLE DECLARATIONS **/

pqueue_t* pqueue;
int thread_count;
int thread_id;
sem_t lock;
//Thread safe variable that keeps track of the current user thread running on this kernel thread
__thread uthread_t* cur_uthread;
int max_kernel_threads;

void kernel_thread(void * arg);

/** PUBLIC FUNCTION IMPLEMENTATIONS **/

void system_init(int max_number_of_klt){
	pqueue = init_queue(10);
	sem_init(&lock, 0, 1);
	thread_count = 0;
	thread_id = 0;
	max_kernel_threads = max_number_of_klt;
	cur_uthread = NULL;
}

int uthread_create(void (*func)()){
	ucontext_t * context = malloc(sizeof(ucontext_t));
	getcontext(context);
	context->uc_stack.ss_sp = malloc(16384); 
	context->uc_stack.ss_size = 16384;
	makecontext(context, func, 0);
	uthread_t* thread = malloc(sizeof(uthread_t));
	thread->ucp = context;
	thread->time_ran = malloc(sizeof(struct timeval));
	thread->time_ran->tv_sec = 0;
	thread->time_ran->tv_usec = 0;
	thread->start_time = malloc(sizeof(struct timeval));
	sem_wait(&lock);
	thread->threadID = thread_id;
	thread_id++;
	thread_count++;
	enqueue(pqueue, thread);
	if(thread_count <= max_kernel_threads){
		void* child_stack= malloc(16384); 
		child_stack+=16383;
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
	struct rusage usage;
	getrusage(RUSAGE_THREAD, &usage);
	timersub(&(usage.ru_utime), cur_uthread->start_time, cur_uthread->time_ran);
	enqueue(pqueue, cur_uthread);
	uthread_t* thread = cur_uthread;
	cur_uthread = dequeue(pqueue);
	cur_uthread->start_time->tv_sec = usage.ru_utime.tv_sec;
	cur_uthread->start_time->tv_usec = usage.ru_utime.tv_usec;
	sem_post(&lock);
	swapcontext(thread->ucp, cur_uthread->ucp);
}

void uthread_exit(){
	if(cur_uthread == NULL){
		exit(0);
	}
	sem_wait(&lock);
	free(cur_uthread);
	if(peek(pqueue) == NULL){
		sem_post(&lock);
		exit(0);
	}
	uthread_t* thread = dequeue(pqueue);
	thread_count--;
	sem_post(&lock);
	struct rusage usage;
	getrusage(RUSAGE_THREAD, &usage);
	thread->start_time->tv_sec = usage.ru_utime.tv_sec;
	thread->start_time->tv_usec = usage.ru_utime.tv_usec;
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
		sem_post(&lock);
		struct rusage usage;
		getrusage(RUSAGE_THREAD, &usage);
		thread->start_time->tv_sec = usage.ru_utime.tv_sec;
		thread->start_time->tv_usec = usage.ru_utime.tv_usec;
		cur_uthread = thread;
		setcontext(thread->ucp);
	}
}