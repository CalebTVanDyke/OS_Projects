#include <stdio.h>
#include "uthread.h"
#include <stdlib.h>
#include <sys/syscall.h>

void prior1();
void prior2();
void prior3();
void prior4();

int main(int argc, char * argv[]){
	system_init(1);
	uthread_create(prior1);
	uthread_create(prior2);
	uthread_create(prior3);
	uthread_create(prior4);
}

void prior1(){
	int i = 0;
	for(i = 1; i > 0; i++);
	uthread_yield();
	printf("Thread 1\n");
	uthread_exit();
}
void prior2(){
	int i = 0;
	for(i = 1; i > 0; i++);
	printf("Thread 2\n");
	uthread_exit();
}
void prior3(){
	int i = 0;
	for(i = 1; i > 0; i++);
	printf("Thread 3\n");
	uthread_exit();
}
void prior4(){
	int i = 0;
	for(i = 1; i > 0; i++);
	uthread_yield();
	printf("Thread 4\n");
	uthread_exit();
}
