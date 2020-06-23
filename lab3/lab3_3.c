/*	Daniela De La Torre
	April 14, 2020
	Lab 3-pthreads and inter-process communication-pipes
	This part of the lab has the ls command being put into the upstream end of the pipe and then the other child process takes the input and prints each individual character followed by a space
*/
/**************************
*   Lab3 - pipe()
**************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <string.h>
#include <sys/wait.h> 

// main
int main(int argc,char *argv[]){
   int  fds[2];
   char buff[60];
   int count;
   int i;
   pipe(fds);
   
   if (fork()==0){
       printf("\nWriter on the upstream end of the pipe -> %d arguments \n",argc);	//prints the number of arguments
       close(fds[0]);									//closes the downstream end of the pipe
       dup2(fds[1],1);									//copies file descriptor of the upstream end of the pipe to standard output
       execlp("ls","ls",0);								//executes the ls command
       exit(0);
   }
   else if(fork()==0){
       printf("\nReader on the downstream end of the pipe \n");
       close(fds[1]);									//closes the upstream end of the pipe
       while((count=read(fds[0],buff,60))>0){						//while there is still stuff to read from the downstream end of the pipe
           for(i=0;i<count;i++){
               write(1,buff+i,1);							//prints each individual character in the buffer to standard output
               write(1," ",1);								//prints a space after each character
           }
           printf("\n");
       }
       exit(0);
    }
   else{     
      close(fds[0]);									//closes the downstream end of the pipe
      close(fds[1]);									//closes the upstream end of the pipe
      wait(0);										//waits for the child process to finish
      wait(0);
   }
return 0;
}
