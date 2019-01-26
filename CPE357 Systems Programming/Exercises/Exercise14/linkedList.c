#include <stdio.h>
#include <stdlib.h>
#include "memmon.h"
#include "linkedList.h"

ListNode* addHead(ListNode *list, int value)
{
   ListNode * temp =(ListNode*)malloc(sizeof(ListNode));
   if (!temp)
   {
      fprintf(stderr, "malloc failure attempting to add %d\n", value);
      exit(EXIT_FAILURE);
   }
   temp->value = value;
   temp->next = list;
   return temp;
}

ListNode* addTail(ListNode *list, int value)
{
   ListNode * temp = list;
   ListNode * temp_prev = list;
   while (temp)
   {
      temp_prev = temp;
      temp = temp->next;
   }
   temp = (ListNode*)malloc(sizeof(ListNode));
   if (!temp)
   {
      fprintf(stderr, "malloc failure attempting to add %d\n", value);
      exit(EXIT_FAILURE);
   }
   temp->value = value;
   if ( !list)
      return temp;
   temp_prev->next = temp;
   temp->next = NULL;
   return list;
}

ListNode* deleteNode(ListNode *list, int index)
{
   ListNode * temp = list;
   ListNode * temp_prev = list;
   int i = index;
   while (temp && index > 0)
   {
      temp_prev = temp;
      temp = temp->next;
      index--;
   }
   if ( index != 0 || !temp )
   {
      printf("Index %d is out of bounds\n", i);
      return list;
   }
   if ( i == 0 )
   {
      list = list->next;
   }
   (temp->next) ? (temp_prev->next = temp->next) : (temp_prev->next = NULL);
   free(temp);
   return list;
}
void printList(ListNode *list)
{
   ListNode * temp = list;
   printf("List: ");
   if ( !list )
   {
      printf("Empty\n");
      return;
   }
   while (temp->next)
   {
      printf("%d ", temp->value);
      temp = temp->next;
   }
   printf("%d\n", temp->value);
}

