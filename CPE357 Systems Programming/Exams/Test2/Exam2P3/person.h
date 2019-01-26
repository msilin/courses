/*
 * PROVIDED FILE - DO NOT MODIFY!
 *
 * An unmodified version of this file will be used during evaluation.
 */
#ifndef PERSON_H
#define PERSON_H

#define LEN_FIRST 20
#define LEN_LAST 30
#define LEN_STATE 2

typedef struct
{
   char first[LEN_FIRST + 1];
   char last[LEN_LAST + 1];
   char state[LEN_STATE + 1];
   unsigned short age;
} Person;

/* Function you must write that uses qsort to sort the Person array
 */
void sortPeople(Person people[], int size);

#endif
