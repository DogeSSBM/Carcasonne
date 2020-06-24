#define PORT	8421
#define BUFFERLEN	1024
#include "Includes.h"

int main(int argc, char const *argv[])
{
	init();

	TCPsocket sSock = tcpStartServer(PORT);
	TCPsocket cSock = tcpWaitForClient(sSock);
	IPaddress *cIp = NULL;

	while(1){
		char buffer[BUFFERLEN] = {0};
		if(SDLNet_TCP_Recv(cSock, buffer, BUFFERLEN) <= 0){
			printf(
				"SDLNet_TCP_Recv error:\n\t%s\n",
				SDLNet_GetError()
			);
			exit(1);
		}
		buffer[BUFFERLEN-1] = '\0';
		if(buffer[0] == '!' && buffer[1] == 'Q'){
			printf("Exiting :3\n");
			SDLNet_TCP_Close(cSock);
			exit(0);
		}
		printf("Message -\n%s\n", buffer);
	}

	printf("WOOOO\n");
	exit(0);
	return 0;
}
