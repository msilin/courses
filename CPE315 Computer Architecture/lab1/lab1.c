#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

/* prints out an array of size 16 of unsigned chars as if it were run on a little
 * endian machine. This function has no return value 
 */
static void printArray2a(unsigned char testArray[]){
   int i;
   printf("problem2a: ");
   for(i=0; i<16; i++){
      printf("0x%x, ", testArray[i]);
   }
   printf("\n");
}
/* prints out an array of size 16 of unsigned chars as if it were run on a big
 * endian machine. This function has no return value 
 */
static void printArray2e(unsigned char testArray[]){
   int i=0;
   printf("problem 2e: ");
   for(i=15;i>=0;i--){
      printf("0x%x, ",testArray[i]);
   }
   printf("\n");
}
/* this function prints out an array in the following formats: unsigned char, short, int, long.
 * It also prints that array out starting from low byte order as if it were run on both big and little
 * endian machines. This function has no return value. Problems 2a- 2e print the array out as if this was run on little endian machine.
 * Problems 2a and 2e print the array out as unsigned chars. Problems 2b and 2f print the array out as shorts. Problems 
 * 2c and 2g print the array out as ints. Problems 2d and 2h print the array out as longs.
 */
void runProblem2(){
   unsigned char testArray[]= {0x41, 0x33, 0x54, 0x80, 0xFF, 0x99,0x01, 0x78,
      0x55, 0x20, 0xFE, 0xEE, 0x00, 0x00, 0x00, 0x00};
   short int* i1=(short int*)&testArray[0];
   long int* i2=(long int*)&testArray[0];
   int* i3=(int*)&testArray[0];
   printArray2a(testArray);
   printf("Problem 2b: 0x%x, 0x%x, 0x%x, 0x%x\n",i1[0],i1[1],i1[2],i1[3]);
   printf("Problem 2c: 0x%x, 0x%x\n",i3[0],i3[1]);
   printf("Problem 2d: 0x%lx\n",*i2);
   printArray2e(testArray);
   printf("Problem 2f: 0x%x, 0x%x, 0x%x, 0x%x\n",i1[7],i1[6],i1[5],i1[4]);
   printf("Problem 2g: 0x%x, 0x%x\n",i3[3],i3[2]);
   printf("Problem 2h: 0x%lx\n",i2[1]);
}
/* prints out the size of a char, short, int, and long on a given machine
 * this function has no return value
 */
void runProblem1(){
   printf("1a: %lu\n 1b: %lu\n 1c: %lu\n 1d: %lu\n", sizeof(char), sizeof(short int), sizeof(int), sizeof(long int));
}


/*static unsigned char addUnsignedChars(unsigned char a, unsigned char b);
static unsigned char determineCarry(unsigned char a, unsigned char b);
static char determineOverFlow(char a, char b);*/
/* adds 2 unsigned chars. Displays the result as an unsigned char. returns an unsigned char for use
 * later problems if necessary.
 */
static unsigned char addUnsignedChars(unsigned char a, unsigned char b){
   unsigned char result= a + b;
   //result= result & 0xFF;
   /*NOTE: to show answers to problem 3 uncomment out next line*/
   printf("0X%02x\n",result);
   return result;
}
/* this function makes function calls to addUnsignedChars. has no return value.
 */
void runProblem3(){
   printf("Problem 3a: ");
   addUnsignedChars(0x20, 0x35);
   printf("Problem 3b: ");
   addUnsignedChars(0x80, 0x7F);
   printf("Problem 3c: ");
   addUnsignedChars(0x80, 0xFF);
   printf("Problem 3d: ");
   addUnsignedChars(0xFF, 0x01);
}

/* This function deteremines if a carry occured when adding 2 values. 
 * This function returns an unsigned char as return value may be needed 
 * in later problems. 
 */
static unsigned char determineCarry(unsigned char a, unsigned char b){
   unsigned char result= (a+b)&0xff;
   printf("result: 0x%x, ", result);
   if(result<a||result<b){
      /*NOTE: to show answers to problem 4 uncomment out next line*/
      printf("carry occured\n");
      return TRUE;
   }
   else{
      /*NOTE: to show answers to problem 4 uncomment out next line*/
      printf("no carry occured.\n");
      return FALSE;
   }
}
/* This function makes function calls to determineCarry. Has no return value 
 */
void runProblem4(){
   printf("Problem 4a: ");
   determineCarry(0x20, 0x35);
   printf("Problem 4b: ");
   determineCarry(0x80, 0x7F);
   printf("Problem 4c: ");
   determineCarry(0x80, 0xFF);
   printf("Problem 4d: ");
   determineCarry(0xFF, 0x01);
}
/* This function adds 2 signed chars and then determines if overflow occured.
 * This functions return TRUE if overflow occured and FALSE if overflow didn't occur.
 */
static char determineOverFlow(char a, char b){
   char result= (a+b)&0xFF;
   if(a>=0&&b>=0&&result<=0){
      printf("overflow occured\n");
      return TRUE;
   }
   else if(a<=0 && b<=0 && result>=0){
      printf("overflow occured\n");
      return TRUE;
   }
   printf("overflow did not occur\n");
   return FALSE;
}
/* This function makes function calls to determineOverFlow. Has no return value
 */
void runProblem5(){
   printf("Problem 5a: ");
   determineOverFlow(0x20, 0x35);
   printf("Problem 5b: ");
   determineOverFlow(0x80, 0x7F);
   printf("Problem 5c: ");
   determineOverFlow(0x80, 0xFF);
   printf("Problem 5d: ");
   determineOverFlow(0xFF, 0x01);
}
/* This function adds 2 1 byte numbers, and determines if there's any carry. This function returns the left most carry.
 */
unsigned int arbitrary_byte_add (unsigned char *result, unsigned char *a1, unsigned char *a2, int size, unsigned int carry_in){
   int i;
   /*temp a flag to see if either of the first two if statement run*/
   for(i=size-1; i>=0;i--){
      if(*a2==0xff&&*a1==0xff&&carry_in==1){
         *result= 0xFF;
         carry_in= 1;
      }
      else if(*a1!=0xFF&&carry_in==1){
         *a1+=1;
      }
      else if(*a2!=0xFF&&carry_in==1){
         *a2+=1;
      }
      if(*result!=0xFF||carry_in==0){
         *result=addUnsignedChars(*a1, *a2);
      if(determineCarry(*a1, *a2)==TRUE)
         carry_in=1;
      }
      result[i]= *result;
      a1= a1-1;
      a2= a2-1;
   }
   printf("\n");
   for(i=0;i<size;i++){
      fprintf(stdout, "%02x ", result[i]);
   }
   free(result);
   return carry_in;
}
/*this function calls arbitrary_byte_add. It has no return value.
 */
void runProblem6a(){
   unsigned int carryIn=0;
   int b;
   unsigned char* result= malloc(sizeof(unsigned char)*5);
   printf("Problem 6a: 0x");
   /*use the following 2 arrays to store the operands*/
   unsigned char o1[5]= {0x44, 0x00, 0x00, 0x00, 0x01};
   unsigned char o2[5]={0x30, 0xFF, 0xFF, 0x00, 0x00};
   /*allocate memory to store the answer*/
   *result=0;
   b=arbitrary_byte_add(result, &o1[4], &o2[4], 5, carryIn);
   printf("carry_in: %d\n", b);
   printf("\n");
}
/*this function calls arbitrary_byte_add. It has no return value.
 */
void runProblem6b(){
   unsigned int carryIn=0;
   int b;
   unsigned char* result= malloc(sizeof(unsigned char)*5);
   printf("Problem 6b: 0x");
   /*use the following 2 arrays to store the operands*/
   unsigned char o1[5]= {0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
   unsigned char o2[5]={0x00, 0x00, 0x00, 0x00, 0x01};
   /*allocate memory to store the answer*/
   *result=0;
   b=arbitrary_byte_add(result, &o1[4], &o2[4], 5, carryIn);
   printf("carry_in: %d\n", b);
   printf("\n");
}
int main(){
   runProblem1();
   runProblem2();
   runProblem3();
   runProblem4();
   runProblem5();
   runProblem6a();
   runProblem6b();
   return 0;
}