#define PORT	8421
#define BUFFERLEN	1024
#include "Includes.h"

int main(int argc, char const *argv[])
{
	init();

	IPaddress sIp = {0};
	TCPsocket sSock = {0};
	IPaddress *cIp = NULL;
	TCPsocket cSock = {0};

	if(SDLNet_ResolveHost(&sIp, NULL, PORT) == -1){
		printf(
			"SDLNet_ResolveHost error:\n\t%s\n",
			SDLNet_GetError()
		);
		exit(1);
	}
	printf("Port %d resolved into IPaddress type\n", PORT);
	if(!(sSock = SDLNet_TCP_Open(&sIp))){
		printf(
			"SDLNet_TCP_Open error:\n\t%s\n",
			SDLNet_GetError()
		);
		exit(1);
	}
	printf("Server socket (sSock) opened for listening\n");
	while(!(cSock = SDLNet_TCP_Accept(sSock))){
		SDL_Delay(100);
	}
	printf("Client connected\n");
	if(!(cIp = SDLNet_TCP_GetPeerAddress(cSock))){
		printf(
			"SDLNet_TCP_GetPeerAddress error:\n\t%s\n",
			SDLNet_GetError()
		);
		exit(1);
	}

	printf("Client info -\n\tIP: ");
	printIp(cIp->host);

	printf("\tPort: ");
	printPort(cIp->port);

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
