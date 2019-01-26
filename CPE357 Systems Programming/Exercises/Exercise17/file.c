#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashTable.h"
#include "getWord.h"
int htcmp( const void* ht1, const void* ht2)
{
   unsigned i,j;
   const HTEntry* ht_1 = ht1;
   const HTEntry* ht_2 = ht2;   
   Word* word1 = ht_1->data;
   Word* word2 = ht_2->data;
   i = j = 0;
   (word1->length >= word2->length) ? (j=word2->length): (j=word1->length);
   
   if ( ht_1->frequency < ht_2->frequency )
   {
      return 1;
   }
   else if ( ht_1->frequency > ht_2->frequency )
   {
      return -1;
   }
   while ( i < j )
   {
      if ( word1->bytes[i] > word2->bytes[i])
      {
         return 1;
      }
      else if ( word1->bytes[i] < word2->bytes[i])
      {
         return -1;
      }
      i++;
   }
   (word1->length > word2->length) ? (i=1): (i=-1);
   return i;
}

void qsortHTEntries(HTEntry *entries, int numberOfEntries)
{
   qsort((void*)entries, numberOfEntries, sizeof(HTEntry), htcmp);

}

