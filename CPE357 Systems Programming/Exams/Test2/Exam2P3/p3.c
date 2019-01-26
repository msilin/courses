#include <stdlib.h>
#include <stdio.h>
#include "person.h"
#include "string.h"
int ppl_cmp(const void* data1, const void* data2)
{
   const Person* P1 = data1;
   const Person* P2 = data2;
   int cmp;
   if ((cmp = strcmp(P1->state, P2->state)))
      return cmp;
   if ((cmp = (P2->age - P1->age)))
      return cmp;
   if ((cmp = strcmp(P1->last, P2->last)))
      return cmp;
   return strcmp(P1->first, P2->first);
}

void sortPeople(Person people[], int size)
{
   qsort(people, size, sizeof(Person), ppl_cmp);
}
