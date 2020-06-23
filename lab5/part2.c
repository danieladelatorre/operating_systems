/* Daniela De La Torre
 * April 27, 2020
 * Lab 5- synchronization using semaphores, lock, and condition variables
 * Description: this part of the lab uses mutex locks to implement synchronization. The main function creates 10 threads that are supposed to execute the go function. In the go function, the mutex object m is locked allowing only that thread to execute the critical section. The other threads must wait until m is unlocked. After executing the critical section, the thread unlocks the mutex object m so that other threads may now enter the thread. 
 */
  // Thread Sychronization

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h> 

#define NTHREADS 10
pthread_t threads[NTHREADS];
pthread_mutex_t m;

void* go(void* arg) {
  pthread_mutex_lock(&m);					//acquire the lock 
  printf("Thread %d Entered Critical Section..\n", (int)arg);	//critical section 
  sleep(1);							//waits 1 second
  pthread_mutex_unlock(&m); 					//releases the lock
  return (NULL);
} 

int main() {
pthread_mutex_init(&m, NULL); 					//initializes mutex m
static int i;
for (i = 0; i < NTHREADS; i++)  
   pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
for (i = 0; i < NTHREADS; i++) {
   pthread_join(threads[i],NULL);
   printf("\t\t\tThread %d returned \n", i);
   }
printf("Main thread done.\n");
pthread_mutex_destroy(&m);					//destroys the mutex object referenced by m 
return 0; 
} 
