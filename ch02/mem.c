#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

int main(int argc, char *argv[])
{
    // a1: Allocate memory for an integer on the heap
    int *p = malloc(sizeof(int));
    assert(p != NULL);

    // a2: Print the process ID (PID) and the virtual address of the allocated memory
    // Using (unsigned) for simple printing, though %p usually handles pointers
    printf("(%d) memory address of p: %p\n",
           getpid(), (unsigned)p);

    // a3: Initialize the value at the allocated address to 0
    *p = 0;

    // a4: Infinite loop that increments the value every second
    while (1)
    {
        Spin(1);
        *p = *p + 1;
        printf("(%d) p: %d\n", getpid(), *p); // a4
    }
    return 0;
}
