/*	Daniela De La Torre
	April 14,2020
	Lab 3-Pthreads and inter-process communication pipes
	This part of the lab makes the output of the ls command become the input of child executing the more process so that each file is outputted line by line 
*/
/**************************
*	pipe()
**************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <sys/wait.h> 
//main
int main() {
 	int fds[2];
 	pipe(fds);
	/*child 1 duplicates downstream into stdin */
	if (fork() == 0) {
		dup2(fds[0], 0);	//copies the file descriptor of the downstream end of the pipe to the standard input file descriptor
		close(fds[1]);		//closes the upstream end of the pipe
		execlp("more", "more", 0); //executes the more command
	}
	/*child 2 duplicates upstream into stdout */
	else if (fork() == 0) {
		dup2(fds[1], 1);	//copies file descriptor of the upstream end of the pipe to the standard output file descriptor
		close(fds[0]);		//closes the downstream end of the pipe
		execlp("ls", "ls", 0);	//executes the ls command
	}
	else {  /*parent closes both ends and wait for children*/
		close(fds[0]);		//closes the downstream end of the pipe
		close(fds[1]);		//closes the upstream end of the pipe
		wait(0);
		wait(0); 
	}
} 
