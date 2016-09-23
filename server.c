#include "server.h"

void launchServer(){
  int serverSocket, clientSocket;                 // descriptor of sockets
  struct sockaddr_in serverAddress; // for naming the server's listening socket

  // create unnamed network socket for server to listen on
  if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("Error creating socket");
    exit(ERROR_CREATING_SOCKET);
  }

  // fills socket information
  serverAddress.sin_family      = AF_INET;           // accept IP addresses
  serverAddress.sin_addr.s_addr = htonl(INADDR_ANY); // accept clients on any interface
  serverAddress.sin_port        = htons(PORT);       // port to listen on

  // binding socket to a port
  if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
    perror("Error binding socket");
    exit(ERROR_BIDING_SOCKET);
  }

  // listening for client connection
  if (listen(serverSocket, NUM_CONNECTIONS) == -1) {
    perror("Error listening on socket");
    exit(ERROR_LISTENING_SOCKET);
  }

  // server loop
  while (1) {
    // accept connection to client
    if ((clientSocket = accept(serverSocket, NULL, NULL)) == -1) {
      perror("Error accepting client");
    } else {
      printf("\nAccepted client\n");
    }
  }
}

void newClient(){

}

int main(){
  launchServer();
  return 0;
}
