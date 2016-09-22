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
#include <arpa/inet.h>
#include <netdb.h>

void launchServer();

void newClient();
