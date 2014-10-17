#include <stdio.h>
#include <sched.h>
#include <linux/sched.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define _GNU_SOURCE

int runOnAThread();

int main(int argc, char * argv[]){
    void * child_stack;
    child_stack = (void*)malloc(16384);
    child_stack += 16383; //BECAUSE STACK GOES BACKWARD
    clone(runOnAThread, child_stack, CLONE_VM|CLONE_FILES, NULL);
    sleep(1);
    printf("IN THE MAIN METHOD\n");
}

int runOnAThread(){
    printf("IN THE THREAD\n");
}
