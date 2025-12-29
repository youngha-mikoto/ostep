/* * Core Concept: I/O Redirection using fork(), close(), and open()
 * This example demonstrates how a shell implements output redirection.
 * By closing standard output (STDOUT) and opening a file before calling exec(),
 * the output of the new program ('wc') is redirected into a file instead of the screen.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int rc = fork();

    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        // 1. Close standard output (the screen)
        close(STDOUT_FILENO);

        // 2. Open a file. Since STDOUT (fd: 1) was just closed,
        // the OS will assign the smallest available fd (which is 1) to this file.
        open("./p4.output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

        // 3. Prepare to run 'wc'
        char *myargs[3];
        myargs[0] = strdup("wc");
        myargs[1] = strdup("p4.c");
        myargs[2] = NULL;

        // 4. Exec replaces the process image.
        // 'wc' thinks it's writing to STDOUT, but it's actually writing to the file.
        execvp(myargs[0], myargs);
    }
    else
    {
        int rc_wait = wait(NULL);
    }

    return 0;
}
