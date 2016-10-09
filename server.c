#include "server.h"

void launchServer(){
  int numberOfClient = 0;
  int serverSocket;                 // descriptor of server socket
  struct sockaddr_in serverAddress; // for naming the server's listening socket
  pthread_mutex_t connectionMutex;  //  mutex used for connection with a client

  //Mutex initialisation
  if(pthread_mutex_init(&connectionMutex, NULL) != 0){
    perror("Error : mutex initialisation");
    exit(ERROR_MUTEX_INIT);
  }

  // create unnamed network socket for server to listen on
  if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("Error : creating socket");
    exit(ERROR_CREATING_SOCKET);
  }

  // fills socket information
  serverAddress.sin_family      = AF_INET;           // accept IP addresses
  serverAddress.sin_addr.s_addr = htonl(INADDR_ANY); // accept any IP adress
  serverAddress.sin_port        = htons(PORT);       // port to listen on

  // binding socket to a port
  if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
    perror("Error : binding socket");
    exit(ERROR_BIDING_SOCKET);
  }

  // listening for client connection
  if (listen(serverSocket, MAX_CONNECTION_QUEUE) == -1) {
    perror("Error : listening on socket");
    exit(ERROR_LISTENING_SOCKET);
  }

  printf("Server start on port %d\n", PORT);

  // server loop
  while (1) {
    Client client;

    //give mutex address to client and lock it
    client.connectionMutex = &connectionMutex;
    pthread_mutex_lock(client.connectionMutex);

    // accept connection to client
    if ((client.socket = accept(serverSocket, NULL, NULL)) == -1) {
      perror("Error : accepting client");
    } else {
      numberOfClient++;
      client.number = numberOfClient;
      printf("\nAccepted client number %d\n", numberOfClient);

      //Create a new thread for the new client
      pthread_t clientThread;
      if(pthread_create(&clientThread, NULL, newClient, &client) != 0 ){
        perror("Error : Creation of thread");
        exit(ERROR_CREATE_THREAD);
      }
    }
  }
}

void* newClient(void* arg){
  Client client = *((Client*) arg);

  pthread_mutex_unlock(client.connectionMutex); //Unlock the mutex so other client can connect

  int connected = 1;
  char* buffer = (char*)malloc(2*sizeof(char));

  // Client exchange loop
  while(connected){
    if(recv(client.socket, buffer, 2, 0) < 0){ //Read receving data from socket
      perror("Error : not receiving data from socket");
      exit(ERROR_READING_SOCKET);
    }
    printf("%c", *buffer);
    //Send data back to socket
    if(write(client.socket, buffer, 1) < 0){
      perror("Error : not sendind data to socket");
      exit(ERROR_WRITING_SOCKET);
    }
    if(*buffer == 'q'){
      //Send a end of line character to the client and leave the main loop
      *buffer = '\n';
      if(write(client.socket, buffer, 1) < 0){
        perror("Error : not sendind data to socket");
        exit(ERROR_WRITING_SOCKET);
      }
      connected = 0;
      printf("\nClient number %d disconnected\n", client.number);
    }
  }

  //Wait until last message is sendind
  sleep(1);

  //Close the socket
  if (close(client.socket) == -1) {
    perror("Error : closing socket");
    exit(EXIT_FAILURE);
  }

  pthread_exit(NULL);  //End of the thread
}

int main(){
  launchServer();
  return 0;
}
