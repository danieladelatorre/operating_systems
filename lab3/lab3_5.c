/*	Daniela De La Torre
	April 14, 2020
	Lab 3-pthreads and inter-process communication-pipes
	This part of the lab takes a message from the producer and writes it to the upstream end of the pipe. The other child process then reads from the downstream end and writes it to a buffer which is then written to the standard output	
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
   char buff[100];
   char *message = malloc(100*sizeof(char));					//allocates memory for the message
   int count;
   int i;
   pipe(fds);
   
   if (fork()==0){
       printf("This is the producer sending a message to the consumer\n");
       message = "MESSAGE FROM PRODUCER";						//this is the message from the producer
       close(fds[0]);									//closes the downstream end of the pipe
       write(fds[1],message,strlen(message));						//writes the message to the upstream end of the pipe
       exit(0);
   }
   else if(fork()==0){
       printf("This is the consumer reading the message from the parent\n");
       close(fds[1]);									//closes the upstream end of the pipe
       while((count=read(fds[0],buff,100))>0){						//while there is still stuff to read from the downstream end of the pipe
           for(i=0;i<count;i++){
               write(1,buff+i,1);							//prints whats in the buffer
           }
           printf("\n");
       }
       exit(0);
    }
   else{     
      close(fds[0]);
      close(fds[1]);
      wait(0);
      wait(0);
   }
return 0;
}
