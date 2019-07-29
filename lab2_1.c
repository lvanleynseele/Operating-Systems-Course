/*
Assignment:
===========
The Basic Programming Task (up to 20 points)

The goal of this assignment is to make sure you fully comprehend (and are able to realize) the creation of processes with Unix-like operating systems. To this end you will be using the fork() system call.
You are to write a very simple shell program, similar to the example covered in lecture. The shell should terminate if the user enters “exit” at the command line, and should attempt to launch a program in response to any other input string. You do not have to parse any parameters, nor do you need to support background execution of processes. The simplest possible shell to demonstrate is all that is required. You may wish to write a “hello world” program, so that you have an executable file that you could launch from your shell.
------------------------------------------------------------------------------------------------
This script is intended to take user inputs from the terminal until the user enters exit, at which point the shell will kill all child processes and terminate the shell.

I tested this program by running the shell from the terminal, and trying various inouts, including exit. Each time I entered an arbitrary command, under 20 characters, the shell did nothing, as expected. When I entered exit, the shell terminated, as expected. 
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main(){
	char command[20];
	char command_exit[] = "exit";
	printf("Enter command: ");
	scanf("%s", command);
    
//  strmcmp returns a negative, zero, or positive int. Use this num to determine if string1 
//is >,=,< s2 to compare command to "exit"
	
	while(strcmp(command, command_exit) != 0){
	        char *args[] = {command, NULL};
	        pid_t pid = fork();
	        if (pid == -1){
            		printf("Fork failed!\n");
        	}
        	if (pid != 0){                    //parent process
            		waitpid(pid, NULL, 0);     //wait for child to exit
        	}
        	else{                          //child process
            		execvp(command, args);
            		exit(1);
        	}
        
    // strcpy copies s2 into array s1 so new command can be inputted
        	strcpy(command, "");
        	printf("Enter command: ");
       		 scanf("%s", command);
   	 }
    	printf("Exiting shell\n");
    	return 0;
}
