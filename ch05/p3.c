/* * Core Concept: Loading and Running Programs with execvp()
 * The exec() family of functions transforms the current process by
 * replacing its memory image with a new program (e.g., 'wc'),
 * effectively switching the process execution without creating a new PID.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    printf("hello world (pid:%d)\n", (int)getpid());
    int rc = fork();

    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        // CHILD PROCESS: Prepare to transform into 'wc'
        printf("hello, I am child (pid:%d)\n", (int)getpid());

        char *myargs[3];
        myargs[0] = strdup("wc");   // Program: word count
        myargs[1] = strdup("p3.c"); // Argument: target file
        myargs[2] = NULL;           // End of arguments

        // EXECUTION: Current process image is replaced here
        execvp(myargs[0], myargs);

        // If execvp is successful, the following line is NEVER reached
        printf("this shouldn't print out");
    }
    else
    {
        // PARENT PROCESS: Wait for the child to finish its 'wc' task
        int wc = wait(NULL);
        printf("hello, I am parent of %d (wc:%d) (pid:%d)\n",
               rc, wc, (int)getpid());
    }

    return 0;
}
