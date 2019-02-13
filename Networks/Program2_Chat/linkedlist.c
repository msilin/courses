#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include <string.h>
/*
node* remove_handle(node *head, char* handle) 
{

    node * current = head;
    node * temp = NULL;
    if ( !strcmp(handle, head->handle) )
    {
        free(head);
        return NULL;
    }
    do 
    {
        if (!current->next)
            return head;
        if ( !strcmp(handle, current->next->handle) )
        {
            temp = current->next;
            if (current->next->next)
                temp->next = current->next->next;
            free(temp->next);

        }
    } while (current = current->next);
    return head;
}*/

node* pop(node * head)
{
    node * temp = head;
    head = head->next;
    free(temp);
    return head;
}
node* push(node * head, char* handle, int handle_len, int socket) 
{
    node* temp = malloc(sizeof(node));
    memcpy(temp->handle,handle, handle_len);
    temp->socket = socket;
    temp->next = head;
    return temp;
}
