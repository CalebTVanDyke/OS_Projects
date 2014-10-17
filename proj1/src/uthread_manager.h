#ifndef UTHREAD_MANAGER_H
#define UTHREAD_MANAGER_H 1

#include <ucontext.h>

typedef struct {
	ucontext_t context;
	int ms_ran;
} uthread_t;

#endif