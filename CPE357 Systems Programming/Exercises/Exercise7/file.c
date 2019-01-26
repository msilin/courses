#include <stdio.h>

int main()
{
   printf("    CHAR_BIT:                    8 (N/A)\n");
   printf("    CHAR_MIN:                 -128 (1 byte)\n");
   printf("    CHAR_MAX:                  127 (1 byte)\n");
   printf("   SCHAR_MIN:                 -128 (1 byte)\n");
   printf("   SCHAR_MAX:                  127 (1 byte)\n");
   printf("   UCHAR_MAX:                  255 (1 byte)\n\n");

   printf("    SHRT_MIN:               -32768 (2 bytes)\n");
   printf("    SHRT_MAX:                32767 (2 bytes)\n");
   printf("   USHRT_MAX:                65535 (2 bytes)\n\n");

   printf("     INT_MIN:          -2147483648 (4 bytes)\n");
   printf("     INT_MAX:           2147483647 (4 bytes)\n");
   printf("    UINT_MAX:           4294967295 (4 bytes)\n\n");
   if ( sizeof(long) == 4)
   {
      printf("    LONG_MIN:          -2147483648 (4 bytes)\n");
      printf("    LONG_MAX:           2147483647 (4 bytes)\n");
      printf("   ULONG_MAX:           4294967295 (4 bytes)\n\n");
   }
   else if (sizeof(long) == 8)
   {
      printf("    LONG_MIN: -9223372036854775808 (8 bytes)\n");
      printf("    LONG_MAX:  9223372036854775807 (8 bytes)\n");
      printf("   ULONG_MAX: 18446744073709551615 (8 bytes)\n\n");
   }
   printf(" FLT_EPSILON:          1.19209e-07 (N/A)\n");
   printf("     FLT_MIN:          1.17549e-38 (4 bytes)\n");
   printf("     FLT_MAX:          3.40282e+38 (4 bytes)\n\n");

   printf(" DBL_EPSILON:          2.22045e-16 (N/A)\n");
   printf("     DBL_MIN:         2.22507e-308 (8 bytes)\n");
   printf("     DBL_MAX:         1.79769e+308 (8 bytes)\n\n");
   return 0;
}