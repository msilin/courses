/*
 *   !!! PROVIDED FILE - DO NOT MODIFY !!!
 */
#include <stdio.h>
#include <stdlib.h>

/*
 * Prototype of the functions you must write in a DIFFERENT file
 */
FILE* fileOpen(const char *fname);
void fileDump(FILE *file, const char *fname);

void checkArgs(int argc, char *argv[])
{
   if (argc < 2)
   {
      fprintf(stderr, "Usage: filedump file [file...]\n");
      exit(EXIT_FAILURE);
   }
}

int main(int argc, char *argv[])
{
   int i, failure = 0;
   FILE *file;

   /* Check the program invocation, display usage and exit if wrong */
   checkArgs(argc, argv);

   /* Loop through the specified files and dump their contents to stdout */
   for (i = 1; i < argc; i++)
   {
      file = fileOpen(argv[i]);

      if (file != NULL)
      {
         fileDump(file, argv[i]);
         fclose(file);
      }
      else
         failure = 1;
   }

   /* Example of the C ternary operator... */
   return failure ? EXIT_FAILURE : EXIT_SUCCESS;
}
