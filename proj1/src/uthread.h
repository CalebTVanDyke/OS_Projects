//UTHREAD HEADER FILE
#ifndef UTHREAD_H
#define UTHREAD_H 1

#include <ucontext.h>
#include <sys/time.h>

/**
*	This struct defines all of the characteristics associated with one user thread
**/
typedef struct {
	int threadID;
	ucontext_t* ucp;
	struct timeval* time_ran;
	struct timeval* start_time;
} uthread_t;
/**
 * This is used to initialized the user thread library
 *
 *      @param max_number_of_klt this denotes the maximum number of kernel threads this user thread library should use.  Must be at least 1
 */
void system_init(int max_number_of_klt);
/**
 *  Creates a new user thread to run func
 *      
 *      @param func the function that should be run on the created thread
 *      @return 0 on success -1 on failure
 */
int uthread_create(void (*func)());
/**
 *  The calling thread should yield to another thread that which has run for the shortest period of time.
 *  If no other thread has shorter running time then the calling thread should proceed to run on a kernal thread.
 */
void uthread_yield();
/**
 *  The calling user thread should end its execution
 *  All user applications should call this before a user thread ends
 */
void uthread_exit();


#endif
