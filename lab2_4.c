/*
Assignment:
===========
The Fourth Programming Task (up to an additional 20 points)

You are to write a program that, when launched, will result in a total of seventeen child processes to run. This is the same task as described above, again this time you are not to allow any single process which creates children to create less than two child processes, or more than three. In other words, the program you write can only launch a maximum of three child processes directly, and any other “children” will have to be created by the children of this parent process (subject to the restriction of only creating two or three processes each). Once again, any process that creates other processes must create either two or three processes only, no more and no less.
----------------------------------------------------------------------------------------------
This script is designed to create exactly 17 child processes, with the caveat that no single proccess can fewer than two and more than 3 child processes at once. Again, the biggest struggle with this task was understanding a structure that would work, which is demonstrated below. 
   			


			  (            root           )
		         /               |             \
		       c1    	        c10               c15
                    /     \             /  \		 /   \
                  c2       c7        c11    c14       c16    c17
                 /  \     /  \	    /   \
               c3    c6  c8   c9   c12   c13
	      /  \
 	     c4   c5

The fact that there was an odd number of children that needed to be created meant there wasn't a uniform way to create the structure. This structure was the first one I found that worked , so i is what I worked to create. 


I tested tht this program was running correctly by having each child print its pit_t number, and that of its parent in terminal. 
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(){
    int i;
    int process_count = 17;
    
    // Generates the first 3 children off of the main parent process to begin.
    if (process_count > 14){
        pid_t pid_1, pid_2, pid_3;
        pid_1 = fork();
        process_count--;
        if (pid_1 == -1)                    // fork error
            printf("Fork failed.\n");
        else if (pid_1 != 0){                // parent process
            waitpid(pid_1, NULL, 0);
            pid_2 = fork();
            process_count--;
            
            if (pid_2 == -1)                // fork error
                printf("Fork failed.\n");
            else if (pid_2 != 0){            // parent process
                waitpid(pid_2, NULL, 0);
                
                pid_3 = fork();
                process_count--;
                if (pid_3 == -1)            // fork error
                    printf("Fork failed.\n");
                else if (pid_3 != 0){        //parent process
                    waitpid(pid_3, NULL, 0);
                    exit(1);
                }
// Spawn two children from right branch
                else{
                    process_count = 1;
                    printf("Child PID: %d | Parent PID: %d\n", getpid(), getppid());
                }
            }
// Spawn four children from middle branch
            else{
                process_count = 2;
                printf("Child PID: %d | Parent PID: %d\n",getpid() ,getppid());
            }
        }
// Spawn eight children from left branch
        else{
            process_count = 3;
            printf("Child PID: %d | Parent PID: %d\n",getpid() ,getppid());
        }
    }
    pid_t pid_1, pid_2;
    while (process_count > 0){
        pid_1 = fork();
        process_count -= 1;
        if (pid_1 == -1)                // fork error
            printf("Fork failed.\n");
        else if (pid_1 != 0){            // parent process
            waitpid(pid_1, NULL, 0);
            pid_2 = fork();
            process_count -= 1;
            if (pid_2 == -1)            // fork error
                printf("Fork failed.\n");
            else if (pid_2 != 0){        // parent process
                waitpid(pid_2, NULL, 0);
                exit(1);
            }
            else{
                printf("Child PID: %d | Parent PID: %d\n",getpid() ,getppid());
            }
        }
        else{
            printf("Child PID: %d | Parent PID: %d\n",getpid() ,getppid());
        }
    }
}
