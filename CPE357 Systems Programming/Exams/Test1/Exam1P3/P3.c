#include <stdio.h>

int main()
{
   int min, max, temp, total, nums, i;
   min = max = temp = total = nums = i = 0;
   printf("Enter the number of integer values to analyze: ");
   scanf("%d", &nums);
   for (; i < nums; i++)
   {
      printf("Enter an integer value %d: ", i+1 );
      scanf("%d", &temp);
      if ( i == 0 )
      {
         min = max = total = temp;
      }
      else
      {
         total += temp;
         if ( temp < min )
         {
            min = temp;
         }
         if ( temp > max )
         {
            max = temp;
         }
      }     
   }
   printf("\nResults:\n");
   printf("   Maximum: %d\n", max);
   printf("   Average: %.2f\n", (double)total / (double)nums);
   printf("   Minimum: %d\n", min);
   return  0;
}