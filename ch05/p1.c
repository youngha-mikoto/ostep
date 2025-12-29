#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    // Print the message and PID before calling fork()
    printf("hello world (pid:%d)\n", (int)getpid());

    // Create a new process (child process) by duplicating the current one
    int rc = fork();

    if (rc < 0)
    {
        // Fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        // Inside the CHILD process: fork() returns 0 to the child
        printf("hello, I am child (pid:%d)\n", (int)getpid());
    }
    else
    {
        // Inside the PARENT process: fork() returns the PID of the child
        printf("hello, I am parent of %d (pid:%d)\n", rc, (int)getpid());
    }

    return 0;
}
