#include <sys/wait.h>
#include "sys/types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAXLINE 4096

int main(void) 
{
   char buf[MAXLINE]; /* from apue.h */
   pid_t pid;
   int status;
   printf("%% "); /* print prompt (printf requires %% to print %) */
   while (fgets(buf, MAXLINE, stdin) != NULL)
   {
      if (buf[strlen(buf) - 1] == '\n')
         buf[strlen(buf) - 1] = 0; /* replace newline with null */
      if ((pid = fork()) < 0)
      {
         perror(NULL);
         exit(EXIT_FAILURE);
      }
      else if (pid == 0)
      { /* child */
         execlp(buf, buf, (char *)0);
         perror(NULL);
         exit(EXIT_FAILURE);
      }
      /* parent */
      if ((pid = waitpid(pid, &status, 0)) < 0)
      {
         perror(NULL);
         exit(EXIT_FAILURE);
      }
      printf("%% ");
   }
   exit(0);
}

