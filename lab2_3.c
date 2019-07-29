/*
Assignment:
===========
The Third Programming Task (up to an additional 20 points)

You are to write a program that, when launched, will result in a total of twelve child processes to run. This is the same task as described above, but this time you are not to allow any single process which creates children to create less than two child processes, or more than three. In other words, the program you write can only launch a maximum of three child processes directly, and any other “children” will have to be created by the children of this parent process (subject to the restriction of only creating two or three processes each). Once again, any process that creates other processes must create either two or three processes only, no more and no less.
----------------------------------------------------------------------------------------------
This script is designed to create exactly 12 child processes, with the caveat that no single proccess can fewer than two and more than 3 child processes at once. The main struggle was recognizing the structure of the tree that would be created, which is demonstrated below

			(         root          )
		       /           |             \
		     c1		   c5            c9
		    / | \        / | \         / |  \
		  c2 c3  c4     c6 c7 c8    c10 c11  c12
	     
After figuring this out, it was simply a matter of looping the correct number of times, and blocking a given branch after getting to the third level.

I tested tht this program was running correctly by having each child print its pit_t number, and that of its parent in terminal. 
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main(){
    	int height = 1;
	int child_processes = 3;
	int max_height = 3;
	int i;    	
	for (i = 0; i < child_processes; i++){  //loop will have each child created create 3 children until it reaches max_height. 3+3(3)=12
		pid_t pid = fork();
		if (pid == 0){    // in child process
		    height++;
		    printf("Child PID: %d | Parent PID: %d\n",getpid() ,getppid());
		    i = -1;	// resets loop to ensure each node under max height creates 3 children, as i is post incremented up
        	}
        	else{           // in parent process
		    // once the node has created 3 children, block it from creating any more
		    wait(NULL);
        	}
        	if (height >= max_height){
		//stop creating child processes once max tree hieght is reached
        	    exit(0);
        	}
    	}
}

