// CLIENT

#define PORT	8421
#define BUFFERLEN	1024
#include "Includes.h"

int main(int argc, char const *argv[])
{
	init(800, 600);

	TCPsocket sSock = tcpStartClient("localhost", PORT);

	while(1){
		char buffer[BUFFERLEN] = {0};
		printf("Enter message, or \"!Q\" (without quotes) to quit\n");
		fgets(buffer,1024,stdin);
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
