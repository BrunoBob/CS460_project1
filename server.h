 //General includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

//Threads include
#include <pthread.h>

//Socket include
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 2222

#define MAX_CONNECTION_QUEUE 1 // Number of maximum cients waiting for a connection

#define ERROR_CREATING_SOCKET 1
#define ERROR_BIDING_SOCKET 2
#define ERROR_LISTENING_SOCKET 3

#define ERROR_MUTEX_INIT 4
#define ERROR_CREATE_THREAD 5

#define ERROR_READING_SOCKET 6
#define ERROR_WRITING_SOCKET 7

typedef struct{
  int socket;
  int number;
  pthread_mutex_t* connectionMutex;
} Client;

void launchServer();

void* newClient(void* arg);
