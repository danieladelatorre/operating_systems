/*	Daniela De La Torre
	April 14, 2020
	Lab 3-pthreads and inter-process communication-pipes
	This part of the lab finds the word root and prints it. does the same as cat /etc/passwd | grep root
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
		dup2(fds[0], 0);					//copies the files descriptor for the downstream end of the pipe to standard input
		close(fds[1]);						//closes the upstream end of the pipe
		execlp("grep", "grep", "root", 0); 			//executes grep root
	}
	/*child 2 duplicates upstream into stdout */
	else if (fork() == 0) {
		dup2(fds[1], 1);					//copies the files descriptor for the upstream end of the pipe to standard output
		close(fds[0]);						//closes the downstream end of the pipe
		execlp("cat", "cat", "/etc/passwd", 0); 		//executes cat /etc/passwd
	}
	else {  /*parent closes both ends and wait for children*/
		close(fds[0]);						//closes downstream end of the pipe
		close(fds[1]);						//closes upstream end of the pipe
		wait(0);						//waits for child process to finish
		wait(0); 
	}
} 
