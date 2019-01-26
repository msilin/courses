#include <stdio.h>
#include <stdlib.h>
#include "getWord.h"
#include "memmon.h"
#include <ctype.h>
int getWord(FILE *file, Byte **word, unsigned *wordLength, int *hasPrintable)
{
   unsigned c, l;
   int i, j;
   Byte * ch_ptr;
   i = c = l = j = 0;
   *hasPrintable = 0;
   //c = fgetc(file);
    if ( feof(file) )
      {
         printf("nigger");
         return EOF;
      }
   while (( c = fgetc(file)) != EOF)
   {
 if ( feof(file) )
      {
         printf("nigger");
         return EOF;
      }
      if (!isspace(c))
      {
         i++;
         if ( isprint(c))
         {
            *hasPrintable = 1;            
         }
      }
      else if (i)
      {
         c = fgetc(file);
         break;
      }
   }
   if ( feof(file) )
      {
         printf("nigger");
         return EOF;
      }
   *wordLength = i;
   fseek(file, sizeof(Byte)*(-i-1), SEEK_CUR);
   ch_ptr = malloc((i)*sizeof(Byte));

   for (; l < i; l++)
   {

      if ( feof(file) )
      {
         return EOF;
      }
      if (( 65 <=  c ) && ( c <= 90 )) 
      {
         c+=32;
      }
      ch_ptr[l] = c;
   }
   //ch_ptr[l] = 0;
   *word = ch_ptr;
   return c;
}


/*c= fgetc(file);
      if ( !isspace(c))
      {
         if (( 65 <=  ch_ptr[l] ) && ( ch_ptr[l] <= 90 )) 
         {
            ch_ptr[l]+=32;
         }
         ch_ptr[l] = c;
      }
      else if (l)
      {
         break;
      }
*/