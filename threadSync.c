/*
# Name: Christopher Bray
# Date: 8/3/2021
# Title: Lab6 – task 1
# Description: This program computes . Step 1. Download the threadSync.c program
# from Canvas, then compile and run several times.  The comment at the top of
# program explains how to compile and run the program. Explain what happens when you
# run the threadSync.c program?
#
# As the program runs, the main thread makes 10 additional threads. All of the 10 threads
# execute the go() function. The main thread waits then as each of the threads take their
# turns ending also using pthread join() prior to continuation. As the go() function prints
# the message Hello including the iteration number, all the threads will print the message.
#
# With sequential runs alternate outputs occur. This is caused by threads being scheduled
# in different ways for individual runs. As the address of i is given to go() function, it
# becomes possible for it to be incremented ahead of the new just created thread executing
# the printf() function. thus, in certain runs multiple threads will print the exact same
# iteration value.
#
# When heavy applications run, the result is also not the same for differing running of the
# program. Arg, the variable in the go() function happens to be a variable on the stack.
# Thus, for each thread a copy is created. However, in the provided code arg has the value
# i. Thus, in the provided code the pointer, arg points to, for all threads, the same
# memory location.
#
# A shared state belongs to the variable i in main(). There happens to be 1 copy. When
# main() function ends, it, being a stack variable, goes out of scope.
#
# The bug involved happens because of the fact that the threads can be scheduled in all
# orders. Example, the thread made with i=3. It ought to print a hello message having
# iteration value being 3. It could be that the value for i in the main thread increments
# to 4 ahead of the occurrence. As the hello message prints the dereferencing arg pointer
# provides the value 4 as it refers to the variable i in the main() function. Thus the
# number for the iteration incorrectly prints to 4. All threads might end up with the wrong
# iteration printed.
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NTHREADS 10
pthread_t threads[NTHREADS];
sem_t mutex;

void *go(void *arg)
{
   sem_wait(&mutex);
   printf("Thread %lu Entered Critical Section..\n", (size_t)arg);
   sleep(1);
   sem_post(&mutex);
   return (NULL);
}

int main()
{
   sem_init(&mutex, 0, 1);
   static int i;

   for (i = 0; i < NTHREADS; i++)
      pthread_create(&threads[i], NULL, go, (void *)(size_t)i);

   for (i = 0; i < NTHREADS; i++)
   {
      pthread_join(threads[i], NULL);
      printf("Thread %d returned \n", i);
   }

   printf("Main thread done.\n");
   sem_destroy(&mutex);

   return 0;
}
