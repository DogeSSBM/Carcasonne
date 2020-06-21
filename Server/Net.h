#pragma once

#define nativeI32(NUM)	SDL_SwapBE32(NUM)
#define nativeI16(NUM)	SDL_SwapBE16(NUM)

void net_init(void)
{
	printf("Initializing SDL_net\n");
	if(SDLNet_Init()==-1) {
		printf(
			"SDLNet_Init borked! Error: %s\n",
			SDLNet_GetError()
		);
		exit(2);
	}
	printf("Adding SDLNet_Quit to atexit()\n");
	atexit(SDLNet_Quit);
}
