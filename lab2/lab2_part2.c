//Daniela De La Torre
//April 7, 2020
//Lab 2-Programming in C and use of System Calls
//This part of the lab creates exactly seven processes with each parent having either 2 or 0 children. This prints the pid of the parent and then the pid of the child. 

#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */
int child = 0; 
/* main function with command-line arguments to pass */
int main(int argc, char *argv[]) {
    int i, n = atoi(argv[1]); // n microseconds to input from keyboard for delay
    pid_t pid;
    pid = fork();
    if (pid) {
	pid = fork();
	if(pid) {
		child += 3;
	} else {
		child = 0;
	}
    } else {
	child = 0;
    }
    if (child == 0) {
	pid = fork();
	if(pid) {
		child ++;
	} else {
		child = 0;
	}
    }
    if (child == 1) {
	pid = fork();
	if(pid) {
		child++;
	} else {
		child = 0;
	}
    }
    if (child != 3) {
    	printf("Parent with pid %d and child with pid %d\n", getppid(), getpid());
    }
    wait(NULL);
    return 0;
}
