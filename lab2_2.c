/*
Assignment:
===========
The Second Programming Task (up to 10 additional points):

You are to write a program that will create exactly eight child processes (not including the initial program itself). You are not to allow any single process to create more than two child processes.
----------------------------------------------------------------------------------------------
This script is designed to simply create exactly 8 child processes, with the caveat that no single proccess can create more than 2 processes at once. I designed it so that each parent would simply create one child, and then get blocked from creating any more in the structure shown below
   			root
		       /
		     c1
		    /
		  c2
		 /
               c3
	      /
            c4
           /
         c5
        /
      c6
     /
   c7
  /
c8

I tested tht this program was running correctly by having each child print its pit_t number, and that of its parent in terminal. 
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main(){
    	printf("Main PID: %d\n" , getpid());
	int i;    	
	for(i = 0; i < 8; i++){	//repeat the child creating process 8 times
        	pid_t pid = fork();
        	if (pid != 0){
            		wait(NULL); 	//block new parent from creating more children 
           		break; 
        	}
        	else{			//shows the structure of parent child hierarchy
            		printf("Child PID: %d | Parent PID: %d\n",getpid() ,getppid());   
        	}
    	}
    	return 0;
}
    
