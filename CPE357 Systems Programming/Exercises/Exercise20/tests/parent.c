#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#define SIZE_MSG 100
int main(int argc, char**argv, char *envp[] )
{
   int fd[2];
   pipe(fd);
   int size = 0, total;
   char ch[65536];
   ch[0]='z';
   int i = 0;
   while (i < 65536)
   {

    /* Save the current flags */


      ch[i] = 'z';
      i++;
   }
   i = 0;
       int flags = fcntl(4, F_GETFL, 0);




    fcntl(4, F_SETFL, O_NONBLOCK);
   size = write(4, ch, 65538);

      printf("%d", size);
 

    exit(0);

}

