#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "arpa/inet.h"
#include "sys/socket.h"
#include "unistd.h"


int socket_connect(int port, char *serverIP, char *sendbuf, char *recvbuf)
{
	struct sockaddr_in server_address;
	int sock;
	
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;

	// creates binary representation of server name
	// and stores it as sin_addr
	// http://beej.us/guide/bgnet/output/html/multipage/inet_ntopman.html
	inet_pton(AF_INET, serverIP, &server_address.sin_addr);

	// htons: port in network order format
	server_address.sin_port = htons(port);

	// open a stream socket
	if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0 )
  	{
		printf("could not create socket\n");
		return 1;
	}

	// TCP is connection oriented, a reliable connection
	// **must** be established before any data is exchanged
	if (connect(sock, (struct sockaddr*)&server_address, sizeof(server_address)) < 0)
 	{	
		printf("could not connect to server\n");
		return 1;

	}
	
	//Send and receive information
	
	send(sock, sendbuf, sizeof(sendbuf), 0);
	recv(sock, recvbuf, sizeof(recvbuf), 0);

  	return sock;
}