#include <stdio.h>

FILE* fileOpen(const char *fname)
{
   FILE * fp = fopen(fname, "r");
   if (fp == NULL)
   {
      fprintf(stderr, "\n");
      perror(fname);
   }
   return fp;
}

void fileDump(FILE *file, const char *fname)
{

   int c;
   printf("\n%s:\n", fname);
   while (1)
   {
      c = fgetc(file);
      if (c == EOF)
      {
         break;
      }        
      printf("%c", c);
   }
}