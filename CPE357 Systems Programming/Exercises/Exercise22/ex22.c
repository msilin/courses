#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
   unsigned num, RHS, b=1;
   char operator[20];
   printf("\n");
   while (1)
   {
      if (b)
         printf("Current value: 0x%08X\n", num);
      printf("Enter bitwise operator (or \"quit\"): ");
      scanf(" %s", operator);
      if(!strcmp(operator, "~"))
      {
         printf("~0x%08X", num);
         num = ~num;
         printf(" is 0x%08X\n\n", num);
         b=1;
      }
      else if(!strcmp(operator, "&"))
      {
         printf("Enter RHS for the & operator in hex: ");
         scanf("%x", &RHS);
         printf("0x%08X & 0x%08X is ", num, RHS);
         num &= RHS;
         printf("0x%08X\n\n", num);
         b=1;
      }
      else if(!strcmp(operator, "^"))
      {
         printf("Enter RHS for the ^ operator in hex: ");
         scanf("%x", &RHS);
         printf("0x%08X ^ 0x%08X is ", num, RHS);
         num ^= RHS;
         printf("0x%08X\n\n", num);
         b=1;
      }
      else if(!strcmp(operator, ">>"))
      {
         printf("Enter RHS for the >> operator in decimal: ");
         scanf("%u", &RHS);
         printf("0x%08X >> %d is ", num, RHS);
         num >>= RHS;
         printf("0x%08X\n\n", num);
         b=1;
      }
      else if(!strcmp(operator, "<<"))
      {
         printf("Enter RHS for the << operator in decimal: ");
         scanf("%u", &RHS);
         printf("0x%08X << %d is ", num, RHS);
         num <<= RHS;
         printf("0x%08X\n\n", num);
         b=1;
      }
      else if(!strcmp(operator, "|"))
      {
         printf("Enter RHS for the | operator in hex: ");
         scanf("%x", &RHS);
         printf("0x%08X | 0x%08X is ", num, RHS);
         num |= RHS;
         printf("0x%08X\n\n", num);
         b=1;
      }
      else if(!strcmp(operator, "quit"))
      {
         exit(0);
      }
      else
      {
         printf("Unrecognized operator '%s', please try again\n", operator);
         b = 0;
      }
   }
}