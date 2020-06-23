#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define N 1024
#define M 1024
#define L 1024

double matrixA[N][M] = {{0}};					//initializes the matrix with 0's
double matrixB[M][L] = {{0}};
double matrixC[N][L] = {{0}};

pthread_t threads[N];

void *matrix(void *arg) {
	int j, k;
	int p = (int)(size_t *)arg;				//p equals the row number
	double temp;
	for(j=0; j<L; j++) {					//computes the value for each column in the row
		temp=0;
		for(k=0; k<M; k++) {
			temp+=(matrixA[p][k]*matrixB[k][j]);	//temp holds the result of the dot product of row A and column B
		}
		matrixC[p][j]=temp;				//sets row p and column j equal to the dot product of the row of A and column of B
	}	
	return;
}

int main(){
	int i, j;
	srand(time(NULL));
	for(i=0; i<N; i++) {
		for(j=0; j<M; j++) {
			matrixA[i][j]=rand()%10;		//generates random numbers between 0 and 10 for matrix A
			printf("%f ", matrixA[i][j]);		//prints matrix A
		}
		printf("\n");
	}
	for(i=0; i<M; i++) {
		for(j=0; j<L; j++) {
			matrixB[i][j]=rand()%10;		//generates random numbers between 0 and 10 for matrix B
			printf("\t\t\t\t%f ", matrixB[i][j]);	//prints matrix B
		}
		printf("\n");
	}
	for(i=0; i<N; i++){
		pthread_create(&threads[i], NULL, matrix, (void *)(size_t)i);	//creates N threads and passes the value of i to the function matrix
	}
	for(i=0; i<N; i++) {
		pthread_join(threads[i],NULL);					//joins the threads so each one finishes executing before executing any more of the main function
	}
	for(i=0; i<N; i++) {
		for(j=0; j<L; j++) {
			printf("%f ", matrixC[i][j]);				//prints out matrix C
		}
		printf("\n"); 
	}
	return 0;
}


