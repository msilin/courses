#include <stdio.h>
#include <stdlib.h>
#include "getWord.h"
#include "memmon.h"
#include <ctype.h>

void checkMalloc(void* mem)
{
   if (!mem)
   {
      perror("");
      exit(EXIT_FAILURE);
   }
}
int getWord(FILE *file, Byte **word, unsigned *wordLength, int *hasPrintable)
{
   unsigned c, i, mem;
   i = *hasPrintable = 0;
   mem = 1;
   *word = malloc(sizeof(Byte)*mem);
   checkMalloc(*word);
   while (((c = fgetc(file)) != EOF) && isspace(c) );
   while (  (c != EOF) && !isspace(c))
   {
      if (i+1 > mem)
      {
         *word = realloc(*word, (mem*=2)*sizeof(Byte));
         checkMalloc(*word);
      }
      if (( 65 <=  c ) && ( c <= 90 )) 
         c+=32;
      (*word)[i]=c;
      i++;
      if (isprint(c))
         *hasPrintable = 1;            
      c = fgetc(file);
   }
   *wordLength = i;
   *word = realloc(*word, i*sizeof(Byte));
   if ( c != EOF )
      return 0;
   return c;
}