#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "common.h"

volatile int counter = 0; // 'volatile' prevents compiler optimization.
int loops;

// Thread worker function: increments the shared counter
void *worker(void *arg)
{
    int i;
    for (i = 0; i < loops; i++)
    {
        // Critical Section: Multiple threads access this shared variable
        counter++;
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "usage: threads <value>\n");
        exit(1);
    }
    loops = atoi(argv[1]);
    pthread_t p1, p2;
    printf("Initial value : %d\n", counter);

    // Create two threads (p1 and p2) that run the worker function
    Pthread_create(&p1, NULL, worker, NULL);
    Pthread_create(&p2, NULL, worker, NULL);

    // Wait for both threads to finish execution
    Pthread_join(p1, NULL);
    Pthread_join(p2, NULL);

    // Print the final result after both threads have completed
    printf("Final value : %d\n", counter);
    return 0;
}
