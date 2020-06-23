/*	Daniela De La Torre
	April 14, 2020
	Lab 3-Pthreads and inter-process communication-pipes
	This part of the lab writes each argument passed to the main function to a buffer which then prints each individual character to standard output followed by a space
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
       printf("\nWriter on the upstream end of the pipe -> %d arguments \n",argc);	//prints the number of arguments passed to the main function
       close(fds[0]);									//closes the downstream end of the pipe
       for(i=0;i<argc;i++){								//for each argument
           write(fds[1],argv[i],strlen(argv[i]));					//writes each argument to the upstream end of the pipe
       }
       exit(0);
   }
   else if(fork()==0){
       printf("\nReader on the downstream end of the pipe \n");
       close(fds[1]);									//closes the upstream end of the pipe
       while((count=read(fds[0],buff,60))>0){						//while there is still stuff to read from the downstream end of the pipe
           for(i=0;i<count;i++){	
               write(1,buff+i,1);							//writes each individual letter of what's in the buffer to standard output followed by a space
               write(1," ",1);
           }
           printf("\n");
       }
       exit(0);
    }
   else{     
      close(fds[0]);	//closes the downstream end of the pipe
      close(fds[1]);	//closes the upstream end of the pipe
      wait(0);		//waits for one of the child processes to finish
      wait(0);		//waits for the other child process to finish
   }
return 0;
}
