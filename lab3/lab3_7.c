/*	Daniela De La Torre
	April 14, 2020
	Lab 3-pthreads and interprocess communication-pipes
	This part of the lab does the same as part 6, but makes sure each value of i is unique to the thread
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
        pthread_create(&threads[i], NULL, go, (void *)(size_t)i);				//creates the threads which execute the go function and the value of i is passed
    for (i = 0; i < NTHREADS; i++) {
	printf("Thread %d returned\n", i);							//prints that the thread returned
        pthread_join(threads[i],NULL);								//joins the threads
    }
    printf("Main thread done.\n");
    return 0;
}
void *go(void *arg) {
 printf("Hello from thread %d with iteration %d\n",  (int)pthread_self(), (size_t *)arg);
 return 0;
}

//The solution to the previous function was to pass the specific value of i to the function go instead of just the address which is done by the void *

