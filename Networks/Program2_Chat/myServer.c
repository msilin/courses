
/******************************************************************************
* tcp_server.c
*
* CPE 464 - Program 1
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "networks.h"
#include "linkedlist.h"
#define MAXBUF 1200
#define MAXHANDLE 100
#define DEBUG_FLAG 1

void recvFromClient(int clientSocket,node * clients);
int checkArgs(int argc, char *argv[]);
void fwdMsg(char* buf, int messageLen, node* clients);
int lookup(node * head, char* handle, char handle_len);

int main(int argc, char *argv[])
{
   int serverSocket = 0;   //socket descriptor for the server socket
   int clientSocket = 0;   //socket descriptor for the client socket
   int portNumber = 0;
   int i =0;
   fd_set readfds, master;
   node* clients = NULL;

   portNumber = checkArgs(argc, argv);
   
   //create the server socket
   serverSocket = tcpServerSetup(portNumber);

   printf(" serverSocket: %d\n", serverSocket);   

   FD_ZERO(&master);
   FD_SET(serverSocket, &master);
   
      
   while (1)
   {
      readfds = master;
      printf("start loop select returns %d\n", select(6, &readfds, NULL, NULL, NULL));
      for ( int i =0; i < 6; i++)
         if ( (FD_ISSET(i, &readfds)))
            printf("SET %d\n", i);
      if (FD_ISSET(serverSocket, &readfds))
      {
         clientSocket = tcpAccept(serverSocket, DEBUG_FLAG);
         printf("client socket %d\n", clientSocket);
         FD_CLR(serverSocket, &master);
         FD_SET(clientSocket, &master);
      }
      else  
      {
         if (FD_ISSET(4, &readfds))
         {
            printf("RECV FROM CLIENT PORT %d", 4);
            recvFromClient(4, clients);
            //FD_CLR(4,&readfds);
         }

         //for (int i =0; i < 5 ;i++)
            //if (FD_ISSET(i, &fdset))
            //{
              // printf("RECV FROM CLIENT PORT %d", i);
               //recvFromClient(i, clients);
      }
         
    
      printf("end loop\n");
      //}
      //FD_CLR(clientSocket, &fdset);
   }
   close(clientSocket);
   close(serverSocket);
   /* close the sockets */
 
   return 0;
}

void recvFromClient(int clientSocket, node* clients)
{
   char buf[MAXBUF];
   char pkt[3];
   int messageLen = 0;
   int i = 0;
   //char* buff = buf;
   pkt[0]= 3;
   pkt[1]= 0;
   if ((messageLen = recv(clientSocket, buf, MAXBUF, 0)) < 0)
   {
      perror("recv call");
      exit(-1);
   }
   printf("Message length? %d\n", messageLen);
   printf("data 1: %02x ", buf[0]);
   printf("data 2 %02x ", buf[1]);
   printf("data 3 %02x ", buf[2]);
   printf("data 4 %02x ", buf[3]);
   printf("data 5 %c ", buf[4]);
   printf("data 6 %c", buf[5]);
   printf("data 7 %c\n", buf[6]);
   switch(buf[2]){
         case 1:
         // client connects
         i = lookup(clients, &buf[4], buf[3] );
         printf("i %d\n", i);
         if (i == -1)
         {
            pkt[2]=2; // good handle
            clients = push(clients, &buf[4], (int)buf[3], clientSocket);
         }
         else
            pkt[2]=3; // send error
         send(clientSocket, pkt, 3, 0);
         break;
         case 4:
         // broadcast
         break;
         case 5:
         // message
         printf("I am a potato");
         //fwdMsg(buf,messageLen, clients);
         break;
         case 8:
         // exit
         break;
         case 10:
         // list clients
         break;

   }
}

void fwdMsg(char* buf, int messageLen, node* clients)
{
   char pkt[3];

   int socket;
   int numClients = buf[4+buf[3]];
   char* pkt_ptr = &buf[5+buf[3]];
   for (int i =0; i < numClients; i++)
   {
      if ((socket = lookup(clients,pkt_ptr+1,*pkt_ptr))!= -1)
      {
         if (send(socket, buf, messageLen, 0))
         {
            perror("send call");
            exit(-1);
         }
      }
      else // send error packet
      {
         pkt[0]= 3;
         pkt[1]= 0;
         pkt[2]= 7;
         if (send(socket, pkt, 3, 0))
         {
            perror("send call");
            exit(-1);
         }
      }

      pkt_ptr+= (*pkt_ptr)+1;
   }
}
int lookup(node * head, char* handle, char handle_len)
{
   node * temp = head;
   while ( temp )
   {
      if (!memcmp(handle, temp->handle, handle_len))
         return temp->socket; 
      temp = temp->next;
   }
   return -1;
}
/* Message Format
   ✓• Normal 3 byte chat-header (message packet length (2 byte), flag (1 byte)) 
   ✓• 1-byte containing the length of the sending clients handle 
   ✓• Handle name of the sending client (no nulls or padding allowed) 
   ✓• 1 byte specifying the number of destination handles contained in this message. 
   ✓• For each destination handle in the message
      ✓◦ 1 byte containing the length of the handle of the destination client you want to talk with1 
      ✓◦ Handle name of the destination client (no nulls or padding allowed) 
   ✓• Text message (a null terminated string)
*/
/*
void sendMsg(char* buf, int messageLen)
{
   int numclients = buf[5 + buf[4]];
   char* client_ptr = &buf[6 + buf[4]];

   while ( numclients-- > 0)
   {
      //lookup socket
      send(socketNum, mpkt, mpkt_len, 0);

   }
   // assume chat message for now
   while(*buff)
    printf("%02x ", (unsigned int) *buff++);
  printf("\n");
}*/


int checkArgs(int argc, char *argv[])
{
   // Checks args and returns port number
   int portNumber = 0;
   if (argc > 2)
   {
      fprintf(stderr, "Usage %s [optional port number]\n", argv[0]);
      exit(-1);
   }
   if (argc == 2)
      portNumber = atoi(argv[1]);
   return portNumber;
}
