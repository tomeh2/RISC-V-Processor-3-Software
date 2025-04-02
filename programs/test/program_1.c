#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void program_1_main(char** argv, unsigned int argc)
{
    clock_t time_start = clock();

    for (volatile int i = 0; i < 10000000; i++) ;

    clock_t time_end = clock();
    clock_t time_elapsed = time_end - time_start;
    printf("Time elapsed: %d.%d sec\n\r", time_elapsed / CLOCKS_PER_SEC, time_elapsed % CLOCKS_PER_SEC);

    printf("Trying to allocate 1KB of memory...\n\r");
    void* ptr = malloc(1024);
    if (ptr)
        printf("Success! Allocated 1024 bytes at %08x\n\r", ptr);
    else
        printf("Allocation failed\n\r");
    
    printf("Trying to allocate 2KB of memory...\n\r");
    ptr = malloc(2048);
    if (ptr)
        printf("Success! Allocated 2048 bytes at %08x\n\r", ptr);
    else
        printf("Allocation failed\n\r");

    printf("Trying to allocate 4KB of memory...\n\r");
    ptr = malloc(4096);
    if (ptr)
        printf("Success! Allocated 4096 bytes at %08x\n\r", ptr);
    else
        printf("Allocation failed\n\r");

    free(ptr);
}