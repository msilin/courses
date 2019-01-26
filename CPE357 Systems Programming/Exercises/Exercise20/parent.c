#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define SIZE_MSG 100

void newPipe(int* fd)
{
   if (pipe(fd) == -1) {
      perror("pipe");
      exit(EXIT_FAILURE);
   }
}

static void writeMessage(int fd, const char *msg)
{
   int len = strlen(msg) + 1;

   if (len != write(fd, msg, len))
   {
      fprintf(stderr, "write failure in %s at line %d\n", __FILE__, __LINE__);
      exit(EXIT_FAILURE);
   }
}

static int readMessage(int fd, char *msg)
{
   int i = 0, ret;

   /* Read in an entire string, including the null-termination */
   while(1)
   {
      /* This call will block until there is something to read or end-of-file */
      if (0 == (ret = read(fd, &msg[i], 1)))
         return EOF;
      else if (ret == -1)
      {
         fprintf(stderr, "write failure in %s at line %d\n"
            , __FILE__, __LINE__);
         exit(EXIT_FAILURE);
      }
      else if (msg[i] == 0) /* Breaks on end-of-string */
         return 0;
      i++;
   }
   return ret;
}
int main(int argc, char**argv, char *envp[] )
{
   int fd[4];
   int i = 0;
   unsigned r = 0 ;
   pid_t pid;
   int status; 
   char buffer[100];
   char ch[5];
   char ch2[5];

   newPipe(fd);
   newPipe(fd+2);
   sprintf(ch, "%d", fd[0]);
   sprintf(ch2, "%d", fd[3]);

   if ( argc != 2 )
   {
      fprintf(stderr, "Usage: parent child\n");
      exit(EXIT_FAILURE);
   }
   pid = fork();
   if ( pid == 0)
   {
      close(fd[1]);
      close(fd[2]);
      execl( "b.out", "b.out", ch, ch2, (char*)NULL);
      exit(0);
   }
   else
   { 
      close(fd[0]);
      close(fd[3]); 
      if (0 == readMessage(fd[2], buffer))
         printf("Message from child: %s", buffer);
      



































      while(1)
      {
         printf("\nEnter a message for the child: ");
         i = 0;
         while ( (r=getchar())!='\n')
         {
            buffer[i]=r;
            i++;
         }
         buffer[i] = 0;
         if (!strcmp(buffer, "quit"))
         {
            printf("Parent closing the write-end of pipe to child\n");
            close(fd[1]);
            break;
         }
         writeMessage(fd[1], buffer);   
         while(1)
         {
            if (0 == readMessage(fd[2], buffer))
            {
               break;
            }
         }
         printf("Acknowledgement from Child: ");
         printf("%s\n", buffer);
      }

      readMessage(fd[2], buffer);
      printf("Acknowledgement from Child: %s\n", buffer);
      pid = wait(&status);
      printf("\nParent waiting for child to terminate...\n");
      printf("Child has terminated, parent ending...\n");     
      exit(0); 
           
   }
 
   exit(0);

}

