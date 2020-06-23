//Daniela De La Torre
//April 7, 2020
//Lab 2-Programming in C and use of System Calls
//This part of the lab does the same as the first part except instead of forking, it uses two threads to print the statements for the parent and child process

#include <stdio.h>      /* printf, stderr */
#include <pthread.h>
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */ 
#include <stdint.h>

/* main function with command-line arguments to pass */
void *firstloopThread(void *arg);
void *secondloopThread(void *arg);

int main(int argc, char *argv[]) {
    pthread_t thread_id[3];
    int i, rc, sc, n = atoi(argv[1]); // n microseconds to input from keyboard for delay
    printf("Before thread\n");
    rc = pthread_create(&thread_id[0], NULL, firstloopThread, (void *) &n);
    sc = pthread_create(&thread_id[1], NULL, secondloopThread, (void *) &n);
    if(rc) {
	printf("Error creating thread %d\n", rc);
	exit(-1);
    }
    if(sc) {
	printf("Error creating second thread %d\n", sc);
	exit(-1);
    }
    for(i=0;i<2;i++) {
    	pthread_join(thread_id[i], NULL);
    }
    printf("After thread\n");
    pthread_exit(NULL);
    return 0;
}    

void *firstloopThread(void *arg) {
    int i;
    int *delay = arg;
    for (i=0;i<100;i++) {
    printf("\t \t \t Parent Process %d\n", i);
    usleep(*delay);
    }
    return NULL;
}

void *secondloopThread(void *arg) {
    int i;
    int *delay = arg;
    for (i=0;i<100;i++) {
    printf("Child process %d\n", i);
    usleep(*delay);
    }
    return NULL;
}
