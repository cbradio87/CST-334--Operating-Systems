/*
# Name: Christopher Bray
# Date: 8/3/2021
# Title: Lab6 – task 2
# Description: This Program computes. Step 2. Write  a  program  that  solves the
# producer- consumer  problem.
#
# The error is solved through controlling the address to a shared variable that’s
# not given to different threads. It is through making the array that keeps the
# iteration values.
 */


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void *go(void*);
#define NTHREADS 10
pthread_t threads[NTHREADS];
int main()
{
    int i;
    int it[10];
    for(i = 0; i < NTHREADS; i++)
    {
        it[i] = i;
        pthread_create(&threads[i], NULL, go, &it[i]);
    }
    for(i = 0; i < NTHREADS; i++)
    {
        printf("Thread %d returned\n", i);
        pthread_join(threads[i],NULL);
    }
    printf("Main thread complete!\n");
    return 0;
}
void *go(void *arg)
{
    printf("This is thread %d on iteration %d\n", (int)pthread_self(), *(int*)arg);
    return 0;
}
