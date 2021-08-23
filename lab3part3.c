/*
# Name: Christopher Bray
# Date: 7/13/2021
# Title: Lab3 – part3
# Description: Write a C program that implements the shell command:cat /etc/passwd | grep root
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
   char *binPath="/bin/cat";
   char *argu1 = "/etc/passwd";
   char *argu2 = " | grep root";
  
   execl(binPath,binPath,argu1,argu2,NULL);
   return 0;
}
