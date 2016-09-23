Simple tcp multi-threaded server

To launch:
	-make
	-./server

Then any client can connect.

Client can disconnect by typing 'q'.

Return :
	-NO ERROR 0
	-ERROR_CREATING_SOCKET 1
	-ERROR_BIDING_SOCKET 2
	-ERROR_LISTENING_SOCKET 3
	-ERROR_MUTEX_INIT 4
	-ERROR_CREATE_THREAD 5
	-ERROR_READING_SOCKET 6
	-ERROR_WRITING_SOCKET 7

To change port go in server.h and change the #define PORT value
