// CLIENT
#define PORT	8421
#define BUFFERLEN	1024
#include "Includes.h"

int main(int argc, char const *argv[])
{
	init(1800, 1000);
	const uint qs = gfx.xlen/4;
	deckInit();
	// TCPsocket sSock = tcpStartClient("localhost", PORT);
	// for(uint i = 0; i < 4; i++){
	// 	drawTileVariants(i*320, 0, 100);
	// 	for(uint i = 0; i < TILE_VARIANTS; i++){
	// 		tileVarients[i] = tileRotate(tileVarients[i], DIR_R);
	// 	}
	// }
	while(1){
		// char buffer[BUFFERLEN] = {0};
		// printf("Enter message, or \"!Q\" (without quotes) to quit\n");
		// fgets(buffer,1024,stdin);
		// uint len = strlen(buffer);
		// buffer[len-1] = '\0';
		// if((SDLNet_TCP_Send(sSock, buffer, BUFFERLEN)) < len){
		// 	printf(
		// 		"SDLNet_TCP_Send error:\n\t%s\n",
		// 		SDLNet_GetError()
		// 	);
		// 	exit(1);
		// }
		// if(buffer[0] == '!' && buffer[1] == 'Q'){
		// 	printf("Exiting :3\n");
		// 	SDLNet_TCP_Close(sSock);
		// 	exit(0);
		// }
		static bool thing = true;
		Ticks frameStart = getTicks();
		if(thing){
			clear();
			for(uint i = 0; i < 4; i++){
				deckShuffle();
				drawDeck(qs*i,0,72, TILE_TOTAL);
			}
			draw();
			thing = false;
		}
		events(frameStart + TPF, &thing);
	}
	return 0;
}
