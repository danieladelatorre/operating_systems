//Daniela De La Torre
//April 7, 2020
//Lab 2-Programming in C and use of System Calls
//This part of the lab forks and uses the child process to print the files in the directory im in and then the parent process waits for the child to finish and then it prints "Child complete"

#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */ 
/* main function with command-line arguments to pass */
int main(int argc, char *argv[]) {
    pid_t  pid;
    int i, n = atoi(argv[1]); // n microseconds to input from keyboard for delay
    printf("\n Before forking.\n");
    pid = fork();
    if (pid == -1) {
        fprintf(stderr, "can't fork, error %d\n", errno);
    }    
    else if(pid == 0) {
	execlp("/bin/ls", "ls", NULL);
    }
    else {
	wait(NULL);
	printf("Child complete");
	exit(0);
    }
    return 0;
}
