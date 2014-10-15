#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int runOnAThread();

int main(int argc, char * argv[]){
    void * child_stack;
    child_stack = (void*)malloc(16384);
    clone(runOnAThread, child_stack, CLONE_VM|CLONE_FILES, NULL);
    sleep(1);
    printf("IN THE MAIN METHOD");
}

int runOnAThread(){
    printf("IN THE THREAD");
}
