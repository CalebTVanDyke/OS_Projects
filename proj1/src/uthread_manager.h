#ifndef UTHREAD_MANAGER_H
#define UTHREAD_MANAGER_H 1

#include <ucontext.h>
#include "pqueue.h"

typedef struct {
	int threadID;
	int (*func)(void*);
	int ms_ran;
} uthread_t;


void kernel_thread();

#endif