/*
 # Name: Christopher Bray
 # Date: 7/27/2021
 # Title: Lab5 – task #2 Description:
 # The error at hand is solved when makins sure the address for common variables isn't
 # given to alternate threads. This can be done when making an array that keeps the
 # iteration quanitity.
 */


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *go(void* );
#define NTHREADS 10
pthread_t threads[NTHREADS];

int main()
{
    int i;
    int thisOne[10];
    for(i = 0; i < NTHREADS; i++)
    {
        thisOne[i] = i;
        pthread_create(&threads[i], NULL,go,&thisOne[i]);
    }
    for(i = 0; i < NTHREADS; i++)
    {
        printf("Thread %d returned\n", i);
        pthread_join(threads[i],NULL);
    }
    printf("Main thread done\n");
    return 0;
}

void *go(void *arg)
{
    printf("Hello from thread %d with iteration %d\n", (int)pthread_self(), *(int*)arg);
    return 0;
}
