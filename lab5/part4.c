/* Daniela De La Torre
 * April 27, 2020
 * Lab 5- synchronization using semaphores, locks, and condition variables
   Description: this part of the lab uses locks and condition variables to allow synchronization in this producer consumer program. The main function creates four threads that each go to the producer and consumer functions. When a function executes the producer function, it locks the mutex and if the buffer is full, it unlocks the mutex and waits for the condition variable empty to be signaled. Once signaled, it executes the critical section and produces a random number and inserts it in the buffer at position in. It then increments the value of in and the count size. We need a count size because the condition variables do not have a specific value so the count keeps track of the number of elements in the buffer. After executing the critical section, it signals the condition variable full to show that there is something in the buffer and it also unlocks the mutex. Similarly, the consumer function locks the mutex and waits for full to be signales if there is nothing  in the buffer. It then executes the critical section and updates the value of out and count and it stores the value of the buffer at location out in a variable called read. It then signals empty and unlocks the mutex.
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

#define BUFFER_SIZE 10
#define NTHREADS 4
pthread_t producer_threads[NTHREADS];
pthread_t consumer_threads[NTHREADS];
pthread_mutex_t mutex;							//initializes the mutex
pthread_cond_t full, empty;						//initializes the condition variables full and empty
int buffer[BUFFER_SIZE];
int count=0;
int in=0;
int out=0;

void *producer(void *arg) {
	int item;
	do {
		pthread_mutex_lock(&mutex);				//acquires the lock for the critical section
		while(count==BUFFER_SIZE) {				//while the buffer is full
			pthread_cond_wait(&empty, &mutex);		//unlocks mutex and waits on condition variable empty 
		}
		item = (rand()%20);					//generates a random number
		buffer[in] = item;					//sets the buffer at location in to the random number above
		printf("producer put %d at location %d\n", item, in);
		in = (in+1)%BUFFER_SIZE;				//updates the variable in
		count++;						//updates the count
		pthread_cond_signal(&full);				//unblocks any thread waiting on the full condition variable
		pthread_mutex_unlock(&mutex);				//unlocks the mutex
		sleep(1);
	} while(1);
	return NULL;
}

void *consumer(void *arg) {
	int read;
	do {
		pthread_mutex_lock(&mutex);							//locks the mutex
		while(count==0) {								//while the buffer is empty
			pthread_cond_wait(&full, &mutex);					//unlocks the mutex while condition is not met and waits on the condition variable full 
		}
		read = buffer[out];								//read has the value of the buffer at location out
		printf("consumer read %d, at location %d\n", read, out); 
		out = (out+1)%BUFFER_SIZE;							//updats the value of out
		count--;									//updates the count
		pthread_cond_signal(&empty);							//wakes up thread waiting for condition variable empty
		pthread_mutex_unlock(&mutex);							//unlocks the mutex
		sleep(1);
	} while(1);
	return NULL;
}

int main() {
	int i;
	pthread_mutex_init(&mutex, NULL);							//initializes the mutex
	pthread_cond_init(&empty, NULL);
	pthread_cond_init(&full, NULL);
	for(i=0; i<NTHREADS; i++) {						
		pthread_create(&producer_threads[i], NULL, producer, (void *)(size_t)i);	//creates threads and passes them to the producer function
		pthread_create(&consumer_threads[i], NULL, consumer, (void *)(size_t)i);	//creates threads and passes them to the consumer function
	}
	for(i=0; i<NTHREADS; i++) {
		pthread_join(producer_threads[i], NULL);					//joins the producer threads
		pthread_join(consumer_threads[i], NULL);					//joins the consumer threads
	}
	printf("Main thread done\n");
	return 0;
}
