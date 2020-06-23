/* Daniela De La Torre
 * April 27, 2020
 * Lab 5-Synchronization using semaphores, locks, and condition variables
 *Description: This part of the lab allows for synchronization using sempahores. At the beginning of the main function, I have a sem_unlink to remove the semaphores mutex, full, and empty so that in the case where I exit using control C, everything gets cleaned up and there is no starvation that occurs because the previous threads didn't increment the mutex. It creates 5 threads that go to the producer function which waits for there to be an empty slot in the buffer (represented by the semaphore empty) and then tries to lock the mutex. Once it's able to lock the mutex, it executes the critical section and it generates a random number and puts it in the buffer. At the end of the producer function, it updates the semaphore full to indicate theres another value in the buffer and then it increments the mutex to unlock it. There are threads that also go to the consumer function which waits for there to be a value in the buffer and it waits for the mutex to be unlocked. If unlocked it executes the critical section and stores the value in the buffer into a variable called read. It then signals the mutex and the semaphore empty to unlock the mutex and increment the value of empty. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <time.h>

#define SIZE 5						//buffer size is 5
#define NTHREADS 5					//there are 5 threads

sem_t *mutex, *full, *empty;
int in=0;						//initilaizes in and out to position 0
int out=0;
int buffer[SIZE]; 
pthread_t producer_threads[NTHREADS];
pthread_t consumer_threads[NTHREADS];

void *producer(void *arg){
	int item;
	do {
		sem_wait(empty);			//waits until there is an empty slot available and decrements the value of empty if greater than 0
		sem_wait(mutex);			//waits until the critical section is open and decrements the value so it is locked
		item = (rand()%20);
		buffer[in] = item;			//value produced by rand() is put in the buffer at location in
		printf("Producer put %d at location %d\n",item, in);
		sleep(1);
		in = (in+1)%SIZE;			//updates the value of in
		sem_post(mutex);			//increases value of mutex so it is unlocked
		sem_post(full);				//increments the value of full
	} while(1);					//this is an infinite loop
	return NULL;
}

void *consumer(void *arg){
	int read;
	do {
		sem_wait(full);				//waits until there is an item in the buffer
		sem_wait(mutex);			//waits until the mutex is unlocked (has a value of 1) then decrements the value making it locked
		read = buffer[out];			//read has the value of the buffer at location out
		printf("Consumer read item %d at location %d\n", read, out);
		sleep(1);
		out = (out+1)%SIZE;			//updates the value of out
		sem_post(mutex);			//increments value of mutex and unlocks it
		sem_post(empty);			//increments the value of empty	
	} while(1);					//infinite loop
	return NULL;
}

int main() {
	int i;
	sem_unlink("mutex");				//unlinks the mutex just in case I exit out with control C
	sem_unlink("full");
	sem_unlink("empty");
	mutex = sem_open("mutex", O_CREAT, 0644, 1);	//initializes mutex with a value of 1
	full = sem_open("full", O_CREAT, 0644, 0);	//initializes full with a value of 0
	empty = sem_open("empty", O_CREAT, 0644, SIZE);	//initializes empty with size of the buffer
	for(i=0; i<NTHREADS; i++) {
		pthread_create(&producer_threads[i], NULL, producer, (void *)(size_t)i);	//creates threads and passes them to the producer function
	}
	for(i=0; i<NTHREADS; i++) {
		pthread_create(&consumer_threads[i], NULL, consumer, (void *)(size_t)i);	//creates threads and passes them to the consumer function 
	}
	for(i=0; i<NTHREADS; i++) {
		pthread_join(producer_threads[i], NULL);					//joins the producer threads
		printf("Producer thread %d returned\n", i);
	}
	for(i=0; i<NTHREADS; i++) {
		pthread_join(consumer_threads[i], NULL);					//joins the consumer threads
		printf("Consumer thread %d returned\n", i);
	}
	printf("Main thread finished\n");
	sem_unlink("mutex");				//removes mutex sempahore
	sem_unlink("full");				//removes full sempahore
	sem_unlink("empty");				//removes empty semaphore
	pthread_exit(0);
	return 0;
}
