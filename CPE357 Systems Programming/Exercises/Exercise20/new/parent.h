#ifndef PARENT_H
#define PARENT_H
void newPipe(int* fd);
static void writeMessage(int fd, const char *msg);
static int readMessage(int fd, char *msg);





#endif
