#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "unitTest.h"
#include "hashTable.h"
#include "struct.h"

#define TEST_ALL -1
#define NORMAL -2 
#define SPECIAL -3

/* Prototype of all test functions. This allows the creation of an array of
 * function pointers which makes the testing code shorter and more clear. It
 * also makes it easier/faster to add new tests - NICE!
 */
typedef void (*TEST_FUNC)();

/* Modified hash algorithm from K&R (page 144). This version does NOT mod the
 * calculated hash value by the table size because it does not know the table
 * size - the caller does though!
 *
 * Also note the following:
 *   * Not the best/fastest/most flexible hash - you'll want something better
 *     for the word frequency project.
 *   * Assumes the data is a C string (nul-terminated sequence of char values).
 *   * You should test with more than just C strings - that implies you will
 *     need to develop a different hash function for the different types.
 *     Writing one that works on a struct (like you'll be using in the word
 *     frequency project) would be a good idea!
 */
static unsigned hashString(const void *data)
{
   unsigned hash;
   const char *str = data;

   for (hash = 0; *str;  str++)
      hash = *str + 31 * hash;

   /* Return the raw hash value - the modulo must be done by caller */
   return hash;
}

static int compareString(const void *a, const void *b)
{
   return strcmp(a, b);
}

/* Helper function to make random strings for robust testing.
 */
static char* randomString()
{
   char *str; 
   int i, length = (rand() % 70) + 3; /* 3 to 72 character random strings  */

   if (NULL == (str = malloc(length + 1)))
   {
      perror("randomString()");
      exit(EXIT_FAILURE);
   }

   /* Put random but visible char values in the string */
   for (i = 0; i < length; i++)
      str[i] = (rand() % (' ' - '~' + 1)) + ' ';

   str[length] = 0; /* nul-terminate it! */

   return str; 
}

/* Good practice suggests:
 *    1. Choosing descriptive test function names.
 *    2. Including a brief description of each test.
 * 
 * Test creating an empty hash table.
 */
static void testCreateEmpty()
{
   /* Set up the test */
   void *ht;

   /* Note that the arra is on the stack - htCreate must make a deep copy! */
   unsigned sizes[] = {7};
   
   /* Note that struct is on the stack - htCreate must make a deep copy! */
   HTFunctions functions = {hashString, compareString, NULL};

   /* Call the function being tested */
   ht = htCreate(&functions, sizes, 1, 0.73);

   /* Do the test(s) */
   TEST_UNSIGNED(htCapacity(ht), 7);
   TEST_UNSIGNED(htUniqueEntries(ht), 0);
   TEST_UNSIGNED(htTotalEntries(ht), 0);

   /* Clean up, destroyData is false because there is not data */
   htDestroy(ht, 0); /* Note: destroyData true should work here too! */
}

/* Test that htCreate asserts when zero sizes specified 
 */
static void testErrorCreateZeroSizes()
{
   /* Set up the test */
   unsigned sizes[] = {7};
   HTFunctions functions = {hashString, compareString, NULL};

   /* Call the function being tested */
   TEST_ERROR(htCreate(&functions, sizes, 0, 0.73));

   /* No clean up necessary - expect assert/program abort by htCreate */
}

/* Test 7: Test that htCreate asserts when the load factor exceeds 1.0.
 */
static void testHTCreateWithHighLoad()
{
   unsigned sizes[] = {1,2,3};
   HTFunctions functions = {hashString, compareString, NULL};
   TEST_ERROR(htCreate(&functions, sizes, 3, 1.1));
}

/* Test 11: Test that htAdd asserts when you attempt to add NULL data.
 */
static void testHTAddAssertForNull()
{
   /*TEST_ERROR(htAdd());*/
}

/* Test 15: Creates a hash table and adds multiple entries, no rehashing. 
 * The test
 * verifies that the following:
 *
 *  An entry is not found by htLookUp before it is added.
 *  An entry can be found by htLookUp after it is added.
 *  That the correct frequency is returned by htLookUp in a variety of cases.
 */
static void test15()
{
   void* ht;
   unsigned sizes[] = {43};
   char* A;
   char* B;
   char* C;

   HTEntry testEntry;
   HTFunctions functions = {hashString, compareString, NULL};
   ht = htCreate(&functions, sizes, 1, .1);

   A = randomString();
   B = randomString();
   C = A;

   testEntry = (htLookUp(ht, A));
   TEST_UNSIGNED(testEntry.frequency, 0);

   TEST_UNSIGNED(htAdd(ht, A), 1);
   TEST_UNSIGNED(htAdd(ht, A), 2);
   TEST_UNSIGNED(htAdd(ht, B), 1);
   TEST_UNSIGNED(htAdd(ht, B), 2);
   TEST_UNSIGNED(htAdd(ht, C), 3);

   testEntry = (htLookUp(ht, A));
   TEST_BOOLEAN(testEntry.frequency, 3);
   htDestroy(ht, 1);
}

/* Test 16: Test rehashing through several cycles. Testing includes:
 *
 * * Verifying the recycling happens at the correct time based on the load
 *   factor specified to htCreate and the contents of the hash table.
 * * The hash table grows its capacity as specified by the sizes array
 *   specified to htCreate.
 * * That the number of unique entries is maintained correctly.
 * * That the number of total entries is maintained correctly.
 * * That all of the entries can be found by htLookUp after rehashing.
 */
/*
 *static void test16()
 *{
 *
 *}
 *
 * Test 17: Test rehashing behavior when the load factor specified to 
 * htCreate is 1.0.
 *static void test17()
 *{
 *   unsigned sizes[] = {9};
 *   HTFunctions functions = {hashString, compareString, NULL};
 *   TEST_ERROR(htCreate(&functions, sizes, 1, 1.0));
 *}
 */

/*Test 1*/
static void test01()
{
   void* ht;
   unsigned sizes[] = {0};
   HTFunctions functions= {hashString, compareString, NULL};
   ht = htCreate(&functions, sizes, 1, .5);

   htDestroy(ht,1);
}

/*Test 2*/
static void test02()
{
   void* ht;
   unsigned sizes[] = {2,5};
   HTFunctions functions= {hashString, compareString, NULL};
   htCreate(&functions, sizes, -5, .5);

   htDestroy(ht,1);
}

/*Test 3: Test that htCreate asserts when a size in the array of sizes is zero.*/
static void test03()
{
   void* ht;
   unsigned sizes[] = {0, 0};
   HTFunctions functions= {hashString, compareString, NULL};
   htCreate(&functions, sizes, 1, .5);

   htDestroy(ht,1);
}

/*Test4 : Test that htCreate asserts when sizes in the array of sizes are not
 *strictly ascending (increasing) values - in this test a size is equal
 *to the immediately previous size.
 */
static void test04()
{
   unsigned sizes[] = {1,2,2};
   HTFunctions functions = {hashString, compareString, NULL};

   TEST_ERROR(htCreate(&functions, sizes, 3, .73));   
}

/* Test 5: Test that htCreate asserts when sizes in the array of sizes are not
 *         strictly ascending (increasing) values - in this test a size is less 
 *         than the immediately previous size. SPECIAL
 */
static void test05()
{
   unsigned sizes[] = {3,2,1};
   HTFunctions functions = {hashString, compareString, NULL};

   TEST_ERROR(htCreate(&functions, sizes, 3, .73));
}

/*Test 6: Test that htCreate asserts when the load factor is zero.*/
static void test06()
{
   unsigned sizes[] = {1,2,3};
   HTFunctions functions = {hashString, compareString, NULL};

   TEST_ERROR(htCreate(&functions, sizes, 3, 0));  
}

/*Test 7: Test that htCreate asserts when the load factor exceeds 1.0.*/
static void test07()
{
   unsigned sizes[] = {1,2,3};
   HTFunctions functions = {hashString, compareString, NULL};

   TEST_ERROR(htCreate(&functions, sizes, 3, 1.01));  
}

/*Test 8: Creates an empty hash table and verifies its capacity, number of unique
 *        entries, and number of total entries.
 *
 *        Note: The hash table is destroyed with the destroy flag set to false (0)
 *        after testing to allow for the use of valgrind to verify no memory is
 *        leaked.
 */
static void test08()
{
   void* ht;
   unsigned sizes[] = {50, 79, 97};
   HTFunctions functions = {hashString, compareString, NULL};

   ht = htCreate(&functions, sizes, 3, .7);

   TEST_UNSIGNED(htCapacity(ht), 50);
   TEST_UNSIGNED((unsigned)(((HTable*) ht)->uniquEnt), 0);
   TEST_UNSIGNED((unsigned)(((HTable*) ht)->totalEnt), 0);

   htDestroy(ht, 0);
}

/*Test 9: Creates an empty hash table and verifies its capacity, number of unique
 *        entries, and number of total entries.
 *
 *        Note: The hash table is destroyed with the destroy flag set to true (!0)
 *        after testing to allow for the use of valgrind to verify no memory is
 *        leaked.
 */
static void test09()
{
   void* ht;
   unsigned sizes[] = {50, 79, 97};
   HTFunctions functions = {hashString, compareString, NULL};

   ht = htCreate(&functions, sizes, 3, .7);

   TEST_UNSIGNED(htCapacity(ht), 50);
   TEST_UNSIGNED((unsigned)(((HTable*) ht)->uniquEnt), 0);
   TEST_UNSIGNED((unsigned)(((HTable*) ht)->totalEnt), 0);

   htDestroy(ht, 1);
}

/* Test 10: Verifies that the hash table makes a deep copy of the array 
 *  of sizes passed
 *  to htCreate. This is done as follows:
 *
 *  1. Call htCreate with an array of sizes.
 *  2. Change the first value in the array AFTER the call to htCreate.
 *  3. Call htCapacity and verify that it is the original value passed to
 *     htCreate and NOT the value after changing it.
 */
static void test10()
{
   void* ht;
   unsigned sizes[] = {1,2,3};

   HTFunctions functions = {hashString, compareString, NULL};
   ht = htCreate(&functions, sizes, 3, .73);

   ((HTable*)ht)->hSizes[0] = 4; 

   TEST_UNSIGNED(htCapacity((((HTable*)ht))), 1);

   htDestroy(ht, 0);

}

/* Test 11: Test that htAdd asserts when you attempt to add NULL data.*/
static void test11()
{
   void* ht;
   unsigned sizes[] = {1,2,3};

   HTFunctions functions = {hashString, compareString, NULL};
   ht = htCreate(&functions, sizes, 3, .73);
   
   htAdd(ht, NULL);
   
   htDestroy(ht, 0);
}

/* Test 12: Creates a hash table, adds a single entry, and verifies the following:
 *
 *  htAdd returns a frequency of 1.
 *  The capacity of the hash table is as expected (unchanged from creation).
 *  The number of unique entries in the hash table is 1.
 *  The number of total entries in the hash table is 1.
 *
 *  Note: The hash table is destroyed after testing to allow for the use of
 *  valgrind to verify no memory is leaked.
 */
static void test12()
{
   void *ht;
   
   unsigned sizes[] = {11, 23};

   HTFunctions functions = {hashString, compareString, NULL};

   ht = htCreate(&functions, sizes, 1, 0.73);

   TEST_UNSIGNED(htAdd(ht, randomString()), 1);

   TEST_UNSIGNED(htCapacity(ht), 11);
   TEST_UNSIGNED(htUniqueEntries(ht), 1);
   TEST_UNSIGNED(htTotalEntries(ht), 1);

   htDestroy(ht, 1);
}

/* Test 13: Creates a hash table and adds multiple entries 
 * without rehashing. Some of
 * the added entries are duplicates, some not. After each call to htAdd the
 * following values are verified:
 *
 *   The correct frequency is returned by htAdd. 
 *  The capacity of the hash table is as expected (unchanged from creation).
 *  The hash table has the correct number unique entries.
 *  The hash table has the correct number of total entries.
 */
static void test13()
{
   void* ht;
   unsigned sizes[] = {43};
   char* A;
   char* B;
   char* C;

   HTFunctions functions = {hashString, compareString, NULL};
   ht = htCreate(&functions, sizes, 1, .1);
   
   A = randomString();
   B = randomString();
   C = randomString();

   TEST_UNSIGNED(htUniqueEntries(ht), 0);
   TEST_UNSIGNED(htAdd(ht, A), 1);
   TEST_UNSIGNED(htAdd(ht, B), 1);
   TEST_UNSIGNED(htAdd(ht, C), 1);
   TEST_UNSIGNED(htAdd(ht, A), 2);
   TEST_UNSIGNED(htAdd(ht, A), 3);
   TEST_UNSIGNED(htAdd(ht, B), 2);
   TEST_UNSIGNED(htUniqueEntries(ht), 3);
   TEST_UNSIGNED(htTotalEntries(ht), 6);
   htDestroy(ht, 1);
}

static void testAll(TEST_FUNC* testFuncs)
{
   int i; 

   for (i = 0; testFuncs[i] != NULL; i++)
   {
      printf("Running normal test function %d\n", i);

      /* Call the test function via function pointer in the array */
      testFuncs[i]();
   }
}

static void runTests(TEST_FUNC *testFuncs, int testType, int testNumber)
{
   if (testNumber == TEST_ALL)
      testAll(testFuncs);
   else
   {
      if (testType == NORMAL)
         printf("Running normal test function %d\n", testNumber);
      else
         printf("Running special test function %d\n", testNumber);
      
      /* Call the test function via function pointer in the array */
      testFuncs[testNumber]();
   }
}

static int numberOfTests(TEST_FUNC* testFuncs)
{
   int count = 0;

   while(testFuncs[count] != NULL)
      count++;

   return count;
}

static int checkArgs(int argc, char *argv[], TEST_FUNC *normalFuncs,
   TEST_FUNC *specialFuncs, int *testType)
{
   int testNumber;

   if (argc == 1)
   {
      *testType = NORMAL;      
      testNumber =  TEST_ALL;
   }
   else if (argc == 2)
   {
      if (1 != sscanf(argv[1], "%d", &testNumber))
      {
         fprintf(stderr, "Invalid test number, must be an integer\n");
         exit(EXIT_FAILURE);
      }

      if (testNumber >= numberOfTests(normalFuncs) || testNumber < 0)
      {
         fprintf(stderr, "Invalid test number (%d)\n", testNumber);
         exit(EXIT_FAILURE);
      }
      
      *testType = NORMAL;
   }
   else if (argc == 3)
   {
      if (0 != strcmp(argv[1], "-special"))
      {
         fprintf(stderr, "Invalid option '%s'\n", argv[1]);
         exit(EXIT_FAILURE);
      }
      
      if (1 != sscanf(argv[2], "%d", &testNumber))
      {
         fprintf(stderr, "Invalid test number, must be an integer\n");
         exit(EXIT_FAILURE);
      }

      if (testNumber >= numberOfTests(specialFuncs) || testNumber < 0)
      {
         fprintf(stderr, "Invalid test number (%d)\n", testNumber);
         exit(EXIT_FAILURE);
      }

      *testType = SPECIAL;
   }
   else
   {
      fprintf(stderr, "Usage: %s [N|-special N]\n", argv[0]);
      exit(EXIT_FAILURE);
   }

   return testNumber;
}

/* Test driver for Hash Table Project.
 *
 * Usage: testHashTable [N|-special N]
 * Where: N is the zero-based index of the test to run.
 *
 * When no option is specified ALL of the tests in normalFuncs are run.
 * When N is specified the specified test in normalFuncs is run.
 * When "-special N" is specified the specified test from specialFuncs is run.
 *
 * TODO:
 *    1) Write a test function.
 *    2) Add its name to the appropriate TEST_FUNC array below.
 *    3) Compile and test your test by:
 *          1. Does it report failure when run on a function known to be
 *             incorrect?
 *          2. Does it pass when run on a function believed to be correct?
 *    4) Be sure use Valgrind, where appropriate, to check for memory errors
 *       and/or leaks!
 */
int main(int argc, char *argv[])
{
   int testNumber, testType;

   /* The array of "normal" test functions, ALL of these run by default */
   TEST_FUNC normalFuncs[] = {
      test08, //0
      test09,
      test10,
      test11, //3
      test12,
      test13, //5
      test15,
      testCreateEmpty,
      /*test17,*/
      NULL
   };

   /* The array of "special" test functions - MUST be run one at a time */
   TEST_FUNC specialFuncs[] = {};/*
      testErrorCreateZeroSizes,
      test01,
      test02,
      test03,
      test04,
      test05,
      test06,
      test07,
      testHTCreateWithHighLoad,
      testHTAddAssertForNull,
      NULL
   };*/

   /* Random numbers used to produce "interesting" strings for testing */
   srand(182955);

   /* Make stdout unbuffered so that test output is synchronous on signals */
   setbuf(stdout, NULL);

   /* Get the test number and test type */
   testNumber = checkArgs(argc, argv, normalFuncs, specialFuncs, &testType);
 
   /* Run the test(s)... */
   if (testType == NORMAL)
      runTests(normalFuncs, NORMAL, testNumber);
   else
      runTests(specialFuncs, SPECIAL, testNumber);
   
   return 0;
}
