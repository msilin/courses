#ifndef UNITTEST_H
#define UNITTEST_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define TEST_STRING(_ACTUAL, _EXPECT)\
{\
   if (strcmp(_ACTUAL, _EXPECT)!=0 ){\
      fprintf(stderr, "Failed test in %s at line %d:\n", __FILE__, __LINE__);\
      fprintf(stderr, "   Found substitution actual, value %s, expected %s\n",\
         _ACTUAL, _EXPECT);\
   }\
}
#define TEST_REAL(_ACTUAL, _EXPECT, _EPSILON)\
{\
   double _actual = _ACTUAL, _expect = _EXPECT, _epsilon = _EPSILON;\
   if ((_actual - (_expect) > (_epsilon))|| ((_expect) - (_actual)\
      > (_epsilon))){\
      fprintf(stderr, "Failed test in %s at line %d:\n", __FILE__, __LINE__);\
      fprintf(stderr, "   Found substitution actual, value %g, expected %g +/-%g\n",\
         _actual, _expect, _epsilon);\
   }\
}
#define TEST_UNSIGNED(_ACTUAL, _EXPECT)\
{\
   unsigned long _actual = _ACTUAL, _expect = _EXPECT;\
   if (_actual != _expect) {\
      fprintf(stderr, "Failed test in %s at line %d:\n", __FILE__, __LINE__);\
      fprintf(stderr, "   Found substitution %s, value %ld, expected %ld\n",\
         #_ACTUAL, _actual, _expect);\
   }\
}
#define TEST_SIGNED(_ACTUAL,_EXPECT)\
{\
   signed long _actual = _ACTUAL, _expect = _EXPECT;\
   if (_actual != _expect) {\
      fprintf(stderr, "Failed test in %s at line %d:\n", __FILE__, __LINE__);\
      fprintf(stderr, "   Found substitution %s, value %ld, expected %ld\n",\
         #_ACTUAL, _actual, _expect);\
   }\
}
#define TEST_CHAR(_ACTUAL, _EXPECT)\
{\
   int _actual = _ACTUAL, _expect = _EXPECT;\
   if (_actual != _expect) {\
      fprintf(stderr, "Failed test in %s at line %d:\n", __FILE__, __LINE__);\
      fprintf(stderr, "   Found substitution %s, value '%c', expected '%c'\n",\
         #_ACTUAL, _actual, _expect);\
   }\
}
#define TEST_BOOLEAN(_ACTUAL,_EXPECT)\
{\
   long _actual = _ACTUAL, _expect = _EXPECT;\
   if ( (_actual == 0 && _expect != 0) || (_expect == 0 && _actual != 0) )  {\
      fprintf(stderr, "Failed test in %s at line %d:\n", __FILE__, __LINE__);\
      fprintf(stderr, "   Found substitution %s, value %s, expected %s\n",\
         #_ACTUAL, _actual ? "true" : "false", _expect ? "true" : "false");\
   }\
}

#define TEST_ERROR(_FUNCTION_CALL)\
{\
   _FUNCTION_CALL;\
   fprintf(stderr, "Failed test in %s at line %d:\n", __FILE__, __LINE__);\
   fprintf(stderr, "   Expected error detection did not occur\n");\
}

#endif
