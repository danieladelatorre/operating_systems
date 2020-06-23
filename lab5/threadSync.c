/* Daniela De La Torre
 * April 27, 2020
 * Lab5 - synchronization using semaphores, lock, and condition variables
   Description: this part of the lab creates a semaphore called mutex and it creates 10 threads that are supposed to execute the statements in the go function. When a thread enters the go function, it is supposed to wait until the mutex is unlocked or has a value of 1 and then it is able to execute the print statement in the critical section. After executing the critical section, the thread increments the value fo mutex makiing it unlocked so the next thread could access it.
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
sem_t *mutex; 

void* go(void* arg) { 
  sem_wait(mutex); 						//entry section (waits for mutex to be positive then decrements the value)
  printf("Thread %d Entered Critical Section..\n", (int)arg); 	//critical section 
   sleep(1); 
  sem_post(mutex); 						//exit section (increments the value of mutex)
  return (NULL);
} 

int main() { 
mutex = sem_open("mutex", O_CREAT, 0644, 1);
static int i;
for (i = 0; i < NTHREADS; i++)  
   pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
for (i = 0; i < NTHREADS; i++) {
   pthread_join(threads[i],NULL);
   printf("\t\t\tThread %d returned \n", i);
   }
printf("Main thread done.\n");
sem_unlink("mutex"); 
return 0; 
} 
