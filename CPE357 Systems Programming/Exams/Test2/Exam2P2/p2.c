#include <stdio.h>
#include <stdlib.h>
#include "memmon.h"

int getLine(char**line, FILE* file)
{
   unsigned c, i = 0, mem = 20;
   *line = malloc(sizeof(char)*mem);
   if(!line)
   {
      perror("");
      exit(EXIT_FAILURE);
   }
   while (((c=fgetc(file))!='\n'))
   {
      if (c==EOF)
         break;
      if ( i > mem )
      {
         *line = realloc(*line, sizeof(char)*(mem*=2));
         if(!line)
         {
            perror("");
            exit(EXIT_FAILURE);
         }
      }
      (*line)[i] = c;
      i++;

   }
   (*line)[i] = 0;
   *line = realloc(*line, (i+1)*sizeof(char));
   if (c == EOF)
      return c;
   return 0;
}