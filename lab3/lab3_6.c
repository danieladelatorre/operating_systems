/*	Daniela De La Torre
	April 14, 2020
	Lab3-pthreads and inter-process communication-pipes
	This part of the lab creates 10 threads which print the statement in the go function.
*/
/**************************
*       COEN177: Threads  *
**************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *go(void *);
#define NTHREADS 10
pthread_t threads[NTHREADS];
int main() {
    int i;
    for (i = 0; i < NTHREADS; i++)  
        pthread_create(&threads[i], NULL, go, &i);
    for (i = 0; i < NTHREADS; i++) {
	printf("Thread %d returned\n", i);
        pthread_join(threads[i],NULL);
    }
    printf("Main thread done.\n");
    return 0;
}
void *go(void *arg) {
 printf("Hello from thread %d with iteration %d\n",  (int)pthread_self(), *(int *)arg);
 return 0;
}
//there are 10 total threads created, however the values of i printed for each thread in the go function are 0,1,3,4,5,6,7,8,9 and 2 is not included 
//the problem with this part of the lab is that since the threads share the memory address, the address of i is passed so when a thread is executing it checks what value of i is in memory at that specific time, this allows multiple threads to have the same value of i. to fix this we need to pass the actual value of i.
