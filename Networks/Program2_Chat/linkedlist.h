#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

typedef struct node_t{
    int socket;
    char handle[1200];
    struct node_t* next;
}node;

node* pop(node * head);
node* push(node * head, char* handle, int handle_len, int socket);





#endif