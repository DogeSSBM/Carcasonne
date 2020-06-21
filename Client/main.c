#define SERVER	"localhost"
#define PORT	8421
#define BUFFERLEN	1024
#include "Includes.h"

int main(int argc, char const *argv[])
{
	init();

	IPaddress sIp = {0};
	TCPsocket sSock = {0};

	if(SDLNet_ResolveHost(&sIp, SERVER, PORT) == -1){
		printf(
			"SDLNet_ResolveHost error:\n\t%s\n",
			SDLNet_GetError()
		);
		exit(1);
	}
	printf(
		"Server hostname %s resolved into IPaddress type over port %d\n",
		SERVER,
		PORT
	);
	if(!(sSock = SDLNet_TCP_Open(&sIp))){
		printf(
			"SDLNet_TCP_Open error:\n\t%s\n",
			SDLNet_GetError()
		);
		exit(1);
	}
	printf("Established connection with server\n");

	while(1){
		char buffer[BUFFERLEN] = {0};
		printf("Enter message, or \"!Q\" (without quotes) to quit\n");
		fgets(buffer,1024,stdin);
		buffer[BUFFERLEN-1]='\0';
		uint len = strlen(buffer);
		buffer[len-1] = '\0';
		if((SDLNet_TCP_Send(sSock, buffer, BUFFERLEN)) < len){
			printf(
				"SDLNet_TCP_Send error:\n\t%s\n",
				SDLNet_GetError()
			);
			exit(1);
		}
		if(buffer[0] == '!' && buffer[1] == 'Q'){
			printf("Exiting :3\n");
			SDLNet_TCP_Close(sSock);
			exit(0);
		}
	}

	printf("WOOOO\n");
	exit(0);
	return 0;
}
