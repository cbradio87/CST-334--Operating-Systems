/*
 # Name: Christopher Bray
 # Date: 7/27/2021
 # Title: Lab5 – task #3 Description: This program computes. Here we are doing
 # matrix multiplications with threads.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#define L 5 // the amount of columns of matrix B
#define M 5 // the amount of columns of matrix A and the amount of rows of matrix B
#define N 5 // the amount of rows for matrix A
#define NTHREADS N // the amount of threads

// make the matrices
int matrixA[N][M]; // this is matrix A
int matrixB[M][L]; // this is matrix B
int matrixC[N][L]; // theis is matrix C which is just A.B

// make N threads
pthread_t threads[NTHREADS];

// this is a struct to hold the i value
typedef struct
{
    int num;
}
i_holder;

// this is a function to multiply the matrices
void *multiply_matrices(void *arg)
{
    i_holder *x = (i_holder *) arg;
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < L; j++)
        {
            matrixC[(*x).num][j] += matrixA[(*x).num][i] * matrixB[i][j];
        }
    }
    return NULL;
}

int main()
{
    srand(time(NULL));

    // fill matrix A with random integer values
    printf("* * * * * * * * * *\n");
    printf("* Matrix A        *\n");
    printf("* * * * * * * * * *\n");
    for (int i = 0 ;  i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            matrixA[i][j] = rand() % 10;
            printf("%d\t", matrixA[i][j]);
        }
        printf("\n");
    }
    printf("******************\n\n");

    // fill matrix B with random integer values
    printf("* * * * * * * * * *\n");
    printf("* Matrix B        *\n");
    printf("* * * * * * * * * *\n");
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < L; j++)
        {
            matrixB[i][j] = rand() % 10;
            printf("%d\t", matrixB[i][j]);
        }
        printf("\n");
    }
    printf("******************\n\n");

    // now make threads
    for (int i = 0; i < NTHREADS; i++) {
        i_holder *x;
        x = malloc(sizeof(i_holder));
        (*x).num = i;
        pthread_create(&threads[i], NULL, multiply_matrices, (void *) x);
    }

    // join every thread, wait for threads to finish their task
    for (int i = 0; i < NTHREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // shows result of matrix C
    printf("* * * * * * * * * *\n");
    printf("* Matrix C        *\n");
    printf("* * * * * * * * * *\n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < L; j++)
            printf("%d\t\t", matrixC[i][j]);
        printf("\n");
    }

    return 0;
}
