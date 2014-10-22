#include <stdio.h>
#include "uthread.h"
#include <stdlib.h>

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
	sleep(1);
	printf("Priority 1\n");
	uthread_exit();
}
void prior2(){
	sleep(1);
	printf("Priority 2\n");
	uthread_exit();
}
void prior3(){
	sleep(1);
	printf("Priority 3\n");
	uthread_exit();
}
void prior4(){
	sleep(1);
	printf("Priority 4\n");
	uthread_exit();
}
