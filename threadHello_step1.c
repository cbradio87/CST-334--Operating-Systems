/*
 # Name: Christopher Bray
 # Date: 7/27/2021
 # Title: Lab5 – task #1 Description: This program computes.
 # If the program is made to run, the thread being main starts 10 more threads. All of these
 # ten threads execute the function called go(). The thread called main waits for all of
 # these threads to complete via pthread_join() first before it continues. As the go()
 # function prints the Hello message that has the iteration number, all the threads results
 # within printing the message.
 #
 # During many runs, altered outputs are gathered. This is due to the threads being sheduled
 # alternatively for every run. As the address for i is giben to go() the function, its
 # a possablitiy for it to increment ahead of the new thread executing the printf()
 # function. Thus during certain runs, more than one threads print the identical iteration
 # value. In the case that other weighted applications ar being run, the result is also not
 # the same for alternate runs of the program.
 #
 # Arg, the variable in the go() function is on the stack as a variable. Thus a duplicate
 # is made for the all the threads. The value assigned to arg is the address of i, the
 # variable. Thus, within the code at hand the poioter, arg,  points to the very same
 # memory location in all threads.
 #
 # i, the variable in main() has a state being shared. There is a copy and only one. Being
 # a stack variable, it goes outside of scope once the main() function completes.
 #
 # The bug is the result of the threads possibly being scheduled with any order. Take in
 # the thread produced with i=3. The thread aught to print  hello, the message including
 # iteration value being 3. However its within reason for the value of i in the main thread
 # to be incremented to 4 ahead of this happening. If the hello message is printed the
 # dereferencing of the pointer, arg, puts out iteration number 4, as it points to i, the
 # variable, within the main() function. Thus the iteration value is incorrectly returned
 # as 4. All of the threads can print an incorrect quantity for the iteration.
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
    for (i = 0; i < NTHREADS; i++)
        pthread_create(&threads[i], NULL, go, &i);
    for (i = 0; i < NTHREADS; i++)
    {
        printf("Thread %d returned\n", i);
        pthread_join(threads[i], NULL);
    }
    printf("Main thread done.\n");
    return 0;
}

void *go(void *arg)
{
    printf("Hello from thread %d with iteration %d\n", (int)pthread_self(),*(int *)arg);
    return 0;
}
