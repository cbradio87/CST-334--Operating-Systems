/*
 #Name: Christopher Bray
 # Date: 7/6/2021
 # Title: Lab2–task# Description: This program computes whether a child ends
    before the parent or not
 */
#include <stdio.h> /* printf, stderr */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* fork */
#include <stdlib.h> /* atoi */
#include <errno.h> /* errno */
/* main function with command-line arguments to pass */

pid_t wait(int *status);

void thisOne(pid_t pid)
{
    if(pid == 0)
    {
        execlp("/bin/ls", "ls", NULL);
    }
    else
    {
        wait(NULL);
        printf("child is complete");
        exit(0);
    }
}

void child(pid_t pid)
{
    printf(" child is alive\n");
    thisOne(pid);
    exit(EXIT_SUCCESS);
}

void parent(pid_t pid)
{
    printf("parent spawned child\n");
    thisOne(pid);
    printf("parent complete\n");
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
    pid_t pid;
    int i, n = atoi(argv[0]); // n microseconds to input from keyboard for delay
    printf("\n Before forking.\n");
    pid = fork();
    //printf("%d\n",pid);

    switch (pid)
    {
        case -1:
            fprintf(stderr, "can't fork, error %d\n", errno);
            exit(EXIT_FAILURE);
        case 0:
            // Child process
            child(pid);
        default:
            // Parent process
            parent(pid);
    }
return 0;
}
