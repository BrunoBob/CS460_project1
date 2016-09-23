#include "server.h"

void launchServer(){
  int serverSocket, clientSocket;                 // descriptor of sockets
  struct sockaddr_in server_address; // for naming the server's listening socket

  // create unnamed network socket for server to listen on
  if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("Error creating socket");
    exit(ERROR_CREATING_SOCKET);
  }

  // fills socket information
  server_address.sin_family      = AF_INET;           // accept IP addresses
  server_address.sin_addr.s_addr = htonl(INADDR_ANY); // accept clients on any interface
  server_address.sin_port        = htons(PORT);       // port to listen on

  // binding socket to a port
  if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
    perror("Error binding socket");
    exit(ERROR_BIDING_SOCKET);
  }

  // listening for client connection
  if (listen(server_socket, NUM_CONNECTIONS) == -1) {
    perror("Error listening on socket");
    exit(ERROR_LISTENING_SOCKET);
  }

  // server loop
  while (1) {
    // accept connection to client
    if ((client_socket = accept(server_socket, NULL, NULL)) == -1) {
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
