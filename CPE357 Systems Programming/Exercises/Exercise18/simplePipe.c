#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

#include <unistd.h>
#define QUIT 'q'
#define NEW_PIPE 'n'
#define WRITE_TO_PIPE 'w'
#define READ_FROM_PIPE 'r'
#define CLOSE_PIPE_END 'c'

void newPipe(int* fd)
{
   if (pipe(fd) == -1) {
      perror("pipe");
      exit(EXIT_FAILURE);
   }
   printf("Pipe successfully created, read-fd is %d, write-fd is %d\n"
      , fd[0], fd[1] );
}
void writePipe()
{
   int a, b;
   printf("Enter the fd of the write-end to write to: ");
   scanf("%d", &a);
   printf("Enter the integer value you wish to write: ");
   scanf("%d", &b);
   if (write(a, &b, sizeof(int)) < 0)
   {
      perror("");
      exit(EXIT_FAILURE);
   }
   else
   {
      printf("The value %d was written successfully to fd %d\n", b, a);
   }
}
void readPipe()
{
   int a, buf, r;
   printf("Enter the fd of the read-end to read from: ");
   scanf("%d", &a);

   if ( (r = read(a, &buf, sizeof(int))) > 0) 
   {

      printf("The value %d was read successfully from fd %d\n", buf, a);
   }
   else if ( r==0 )
   {
      printf("EOF encountered while attempting to read from fd %d\n", a);
   }
   else
   {
      perror("");
      exit(EXIT_FAILURE);
   }

}
void closePipe(int* fd)
{
   int a;
   printf("Enter the fd of the pipe-end you wish to close: ");
   scanf("%d", &a);
   if (close(a))
   {
      perror("");
      exit(EXIT_FAILURE);
   }
   printf("File descriptor %d successfully closed\n", a);
}

static int getCommand()
{
   char command;

   printf("\nCommand Menu:\n");
   printf("   n - Create a new pipe\n");
   printf("   w - Write to a pipe end\n");
   printf("   r - Read from a pipe end\n");
   printf("   c - Close a pipe end\n");
   printf("   q - Quit\n\n");
   printf("Enter a command: ");

   /* I know, this expects the user to be perfect - hey it's an exercise! */
   scanf(" %c", &command);
   return command;
}

static int doACommand()
{
   char command = getCommand();
   int fd[2];
   switch (command)
   {
      case NEW_PIPE:
         /* Good design/decompostion suggest calling a helper function here! */
         newPipe(fd);
      break;

      case WRITE_TO_PIPE:
         /* Good design/decompostion suggest calling a helper function here! */
         writePipe(fd);
      break;

      case READ_FROM_PIPE:
         /* Good design/decompostion suggest calling a helper function here! */
         readPipe(fd);
      break;

      case CLOSE_PIPE_END:
         /* Good design/decompostion suggest calling a helper function here! */
         closePipe(fd);
      break;

      case QUIT:
         printf("Bye Bye - see you next time!\n");
      break;

      default:
         printf("Unknown command, please try again...\n");
   }

   return command;
}

/*
 * NOTE: The SIGPIPE signal is ignored in this program so that you can see the
 *       error that occurs when you try to write to a pipe whose read-end is
 *       closed - be sure to try that scenario!
 */
int main()
{
   int command = !QUIT;

   /* See comment block preceding main */
   signal(SIGPIPE, SIG_IGN);

   while (command != QUIT)
      command = doACommand();

   return 0;
}
