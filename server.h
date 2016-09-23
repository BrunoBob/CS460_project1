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

#define SERVER_IP "127.0.0.1"
#define PORT 2222

#define ERROR_CREATING_SOCKET 1
#define ERROR_BIDING_SOCKET 2
#define ERROR_LISTENING_SOCKET 3

#define NUM_CONNECTIONS 1

void launchServer();

void newClient();
