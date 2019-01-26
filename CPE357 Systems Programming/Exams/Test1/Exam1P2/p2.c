#include <stdio.h>

int approxEq(double a, double b, double epsilon)
{
   double temp = a - b;
   if ( temp < 0)
   {
      temp = b - a;
   }
   if ( temp <= epsilon )
   {
      return 1;
   }
   return 0;
}