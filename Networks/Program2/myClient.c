
/******************************************************************************
* tcp_client.c
*
   /\   /\
  //\\_//\\     ____
  \_     _/    /   /
   /🐸🐸\    /^^^]
   \_\o/_/    [   ]
    /   \_    [   /
    \     \_  /  /
     [ [ /  \/ _/
    _[ [ \  /_/

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
#include <ctype.h>
#include "networks.h"

#define MAXBUF 1400
#define DEBUG_FLAG 1
#define xstr(a) str(a)
#define str(a) #a
void printMpkt(u_char * mpkt);
void readCommand(char * handle, int socketNum);
void broadcast(char * handle, int socketNum);
void message(char * handle, int socketNum);
void checkArgs(int argc, char * argv[]);
void recvFromServer(int socketNum);
void connectToServer(char*handle, int socketNum);
//void exitC(int socketNum);

int main(int argc, char * argv[])
{
   int socketNum = 0;         //socket descriptor
   //fd_set fdset;
   checkArgs(argc, argv);
   /* set up the TCP Client socket connect */

   socketNum = tcpClientSetup(argv[2], argv[3], DEBUG_FLAG);
   printf("SOCKET: %d\n", socketNum);
   connectToServer(argv[1], socketNum);
   //FD_SET(socketNum, &fdset);
   
   while (1)
   {
      readCommand(argv[1], socketNum);
   }
   close(socketNum);
   
   return 0;
}

void connectToServer(char*handle, int socketNum)
{
   int pkt_len = strlen(handle)+4;
   char pkt[pkt_len];
   pkt[0]= htons(pkt_len) & 0x00ff;
   pkt[1]= htons(pkt_len) >> 8; 
   pkt[2]=1;
   pkt[3]=strlen(handle); 
   memcpy(&pkt[4],handle, strlen(handle));

   if (send(socketNum, pkt, pkt_len, 0) < 0)
   {
      perror("send call");
      exit(-1);
   }
   recvFromServer(socketNum);
}

void listClients(char* buf,int socketNum)
{
   char pkt[3];
   pkt[0]= htons(3) & 0x00ff;
   pkt[1]= htons(3) >> 8; 
   pkt[2]=10;
   send(socketNum, pkt, 3, 0);

}
void recvFromServer(int socketNum)
{
   char buf[MAXBUF];
   int messageLen = 0;
   
   //char* buff = buf;
   if ((messageLen = recv(socketNum, buf, MAXBUF, 0)) < 0)
   {
      perror("recv call");
      exit(-1);
   }
   //printf("Message received, length: %d Data: %s\n", messageLen, buf);
   switch(buf[2]){
         case 2:
         printf("GOOD HANDLE");
         break;
         case 3:
         printf("data 1: %02x ", buf[0]);
         printf("data 2 %02x ", buf[1]);
         printf("data 3 %02x ", buf[2]);
         perror("handle already exists");
         exit(-1);
         break;
         case 7:
         printf("Client with handle %s does not exist.", &buf[5]);
         break;
         case 9:
         //Good ACK for exit
         exit(0);
         break;
         case 11:            
         for (int i = 0; i < ntohs(buf[3]); i++)
         {
            printf("nstoh + %d",ntohs(buf[3]));
            recv(socketNum, buf, MAXBUF, 0);
            printf("\t %s\n", buf);
         }
         /* Flag = 11
         o Server to client, responding to flag = 10, giving the client the number of handles
         stored on the server.
         o Format: chat-header, 4 byte number (integer, in network order) stating how
         many handles are currently known by the server. */
         //printHandles(int numHandles);
         break;
         case 12:
         /* Format: chat-header, then one handle in the format of: 1 byte handle length, then
         the handle (no null or padding). */
         break;
         case 13:/*Server to client. This packet tells the client the %L is finished.
         o Immediately follows the last flag = 12 packet
         o Format: chat-header */
         break;
   }


   // assume chat message for now select which function to call?
   // add switch statements based on FLAG
   /*
      switch(buf[3]);
   */
   //forwardMsg(buf, messageLen);
}

void printHandles(int numHandles)
{
   //int i = 0;
   //while(i++ < numHandles)
   //{
      //recvFromServer(socketNum);
   //}
}
void readCommand(char*handle, int socketNum)
{
   char *token = NULL;
   char sendBuf[MAXBUF];    //data buffer

   int sendLen = 0;         //amount of data to send
   int sent = 0;            //actual amount of data sent/* get the data and send it   */
   memset(sendBuf, 0, MAXBUF*sizeof(char));
   printf("$: ");
   scanf("%" xstr(MAXBUF) "[^\n]%*[^\n]", sendBuf);
   printf("send buf%s\n", sendBuf);
   printf("send len%d\b", sendLen);
   sendLen = strlen(sendBuf) + 1;

   token = strtok(sendBuf, " ");
   if ((token[0]!='%') || (strlen(token) != 2))
      fprintf(stderr, "Usage: cclient %%M | %%B | %%L | %%E \n");

   switch(token[1]){
         case 'm':
         case 'M': 
         printf("hi");
         message(handle,socketNum);
         //FD_SET(4, &fdset);
         
         break;
         case 'b':
         case 'B': 
         broadcast(handle,socketNum);
         break;
         case 'l':
         case 'L':
         sendBuf[0]= htons(3) & 0x00ff;
         sendBuf[1]= htons(3) >> 8; 
         sendBuf[2]=10;
         send(socketNum, sendBuf, 3, 0);
         //select(6, &readfds, NULL, NULL, NULL);
         break;
         case 'e':
         case 'E': 
         //exitC(handle,socketNum);
         break;
   }

   //sendLen = strlen(sendBuf) + 1;

   //sent =  send(socketNum, sendBuf, sendLen, 0);
   if (sent < 0)
   {
      perror("send call");
      exit(-1);
   }

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
void broadcast(char*handle, int socketNum)
{
   u_char mpkt[MAXBUF];
   uint16_t mpkt_len;
   int16_t txt_len;
   char *token, *txt_ptr, *mpkt_ptr = (char*)&mpkt[4];
   memset(mpkt, 0, MAXBUF);
   token = strtok(NULL, " ");  
                                                               // Skip chat-header for now
   mpkt[3]=strlen(handle);                                     // Set Length of Client Handle
   
   memcpy(mpkt_ptr,handle,mpkt[3]);                            // Copy Client Handle
   mpkt_ptr += mpkt[3];
   txt_ptr = (token+strlen(token)+1);
   txt_len = strlen(txt_ptr);
   while(txt_len > 0)                                           // Break txt msg up into 200 byte chunks
   {
      memcpy(mpkt_ptr++, txt_ptr, 200);
      mpkt_ptr[200] = '\0';
      mpkt_len= mpkt_ptr - (char*)mpkt+strlen(txt_ptr);

      mpkt[0]= htons(mpkt_len) & 0x00ff;
      mpkt[1]= htons(mpkt_len) >> 8; 
      send(socketNum, mpkt, mpkt_len, 0);
      txt_len -= 200;
      txt_ptr += 200;
   }

}

void message(char*handle, int socketNum)
{
   u_char mpkt[MAXBUF];
   u_char numDests;
   uint16_t mpkt_len;
   int16_t txt_len;
   char *token, *txt_ptr, *mpkt_ptr = (char*)&mpkt[4];
   memset(mpkt, 0, MAXBUF);
   mpkt[2]=5;                                                           // Skip chat-header length for now
   mpkt[3]=strlen(handle);                                     // Set Length of Client Handle
   
   memcpy(mpkt_ptr,handle,mpkt[3]);                            // Copy Client Handle
   mpkt_ptr += mpkt[3];                
   token = strtok(NULL, " ");  
   *mpkt_ptr = isdigit(token[0]) ? (token[0] - '0') : (1);      //Determine # of destinations
   
   if(isdigit(token[0]))
      token = strtok(NULL, " ");
                       
   numDests = *mpkt_ptr++;
   while(numDests-- > 0)                                        // Set Destination Handle Info
   {
      *mpkt_ptr = strlen(token);
      memcpy(mpkt_ptr+1,token, *mpkt_ptr);
      mpkt_ptr += *mpkt_ptr+1;
      if (numDests > 0)               // don't want strtok to overwrite txt
         token = strtok(NULL, " ");
   }
   txt_ptr = (token+strlen(token)+1); 
   txt_len = strlen(txt_ptr);

   while(txt_len > 0)                                           // Break txt msg up into 200 byte chunks
   {
      memcpy(mpkt_ptr++, txt_ptr, 200);
      mpkt_ptr[200] = '\0';
      mpkt_len = mpkt_ptr - (char*)mpkt + strlen(txt_ptr);

      mpkt[0]= htons(mpkt_len) & 0x00ff;
      mpkt[1]= htons(mpkt_len) >> 8;

      send(3, mpkt, mpkt_len, 0);
      txt_len -= 200;
      txt_ptr += 200;
   }

}


void printMpkt(u_char * mpkt)
{
   int i =0,j=0;
   printf("size :%04x \n", (uint16_t)mpkt[0]);
   printf("flag :%02x \n", mpkt[2]);
   
   printf("Sending Client Handle Length: %02x\n", mpkt[3]);
   printf("Sending Handle Name: ");
   for(; i< mpkt[3]; i++)
      printf("%c", mpkt[i+4]);
   printf("\n");
   j = mpkt[i+=4];
   printf("NumDests: %02x\n", j);
   while ( j-- > 0)
   {
      printf("   Dest Handle Length: %02x\n", mpkt[++i]);
      printf("   Dest Handle Name: ");

      for(int k = 0; k<mpkt[i]; k++)
         printf("%c", mpkt[i+k+1]);
      i+=mpkt[i];
      printf("\n");
   }
   i++;
   printf("Text: %s\n", &mpkt[i]); 

    /*Print hex values
   printf("packet\n");
   for ( int i =0; i < 35; i++)
   {
      printf("i %02d ", i);
      
      if(mpkt[i] < 30)
         printf("%d", mpkt[i]);
      else
         printf("%c", mpkt[i]);
      printf("\n");
   }  
      printf("done\n");*/
}
void checkArgs(int argc, char * argv[])
{
   /* check command line arguments  */
   if (argc != 4)
   {
      printf("usage: %s handle server-name server-port \n", argv[0]);
      exit(1);
   }
}