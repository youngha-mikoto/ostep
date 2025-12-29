/* * Core Concept: Process Synchronization using wait()
 * The parent process uses wait() to pause its execution until the child process
 * finishes, ensuring a deterministic execution order.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
        printf("hello, I am child (pid:%d)\n", (int)getpid());
    }
    else // Parent process
    {
        /* --- WAIT SECTION START --- */

        // Parent process pauses here until the child terminates.
        // It returns the PID of the terminated child.
        int rc_wait = wait(NULL);

        // This line will ALWAYS execute AFTER the child's printf.
        printf("hello, I am parent of %d (rc_wait:%d) (pid:%d)\n", rc, rc_wait, (int)getpid());

        /* --- WAIT SECTION END --- */
    }

    return 0;
}
