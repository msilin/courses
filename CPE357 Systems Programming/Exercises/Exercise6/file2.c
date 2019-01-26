#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void print(char* arg, int num, int type, int temp, double temp2);
int argType(char *argv, int *temp, double *temp2);
void improperArgs();

int main (int argc, char * argv[])
{
   /*char output;*/
   int i , temp, type;
   double temp2;
   i = 1;
   if (argc < 2)
   {
      improperArgs();
      return 1;
   }
   do 
   {  
      type = argType(argv[i], &temp, &temp2);
      print(argv[i], i, type, temp, temp2);
      i++;
   } while ( i < argc);
   return 0;
}

int argType(char *argv, int *temp, double *temp2)
{
   int j = 0;
   /*char argument*/ 
   if (strlen(argv) == 1 && !isdigit(argv[0])) 
   {  
      
      if ( sscanf(argv,"%c", argv))
      {
         return 0;
      }        
   }
   /*int or double*/ 
   if (isdigit(argv[0]) || ((argv[0] == '.') && isdigit(argv[1])))
   {
      for (; j < strlen(argv); j++)
      {      
         if (argv[j] == '.')
         {
            if ( sscanf(argv,"%lf", temp2))
            { 
               return 1; /*looks like a double*/
            }
         }
      }
      if (sscanf(argv,"%d", temp) )
      {      
         return 2; /*must be an int*/      
      }
   }
   return 3;  /*must be an string*/
}

void improperArgs()
{
   fprintf( stderr, "Usage: dataTyper argument [argument ...]\n");
}
void print(char* arg, int num, int type, int temp, double temp2)
{
   if (type == 0)
   {
      printf("   Argument %d is a char, its value is %s\n", num, arg);
   }
   else if (type == 1)
   {
      printf("   Argument %d is a double, its value is %.6f\n", num, temp2);
   }
   else if (type == 2)
   {
      printf("   Argument %d is an int, its value is %d\n", num, temp);
   }
   else if (type == 3)
   {
      printf("   Argument %d is a string, its value is %s\n", num, arg);
   }
}

