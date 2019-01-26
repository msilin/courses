#include <stdio.h>

int findSubstring(const char *string, const char *substring)
{
   int i, j, k;
   i = j = k = 0;
   while (substring[k] != 0)
   {
      k++;
   }
   k--;
   while (string[j] != 0)
   {
      if (string[j] == substring[i])
      {
         while (substring[i] != 0)
         {
            if (string[j+i] != substring[i])
            {
               i = 0;
               break;
            }
            else if ( i == k )
            {
               return j;
            }
            i++;           
         }
      }
      j++;
   }
   if ( substring[0] == '\0' )
   {
      return j;
   }
   return -1;
}