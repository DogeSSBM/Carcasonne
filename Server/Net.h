#pragma once

#define nativeI32(NUM)	SDL_SwapBE32(NUM)
#define nativeI16(NUM)	SDL_SwapBE16(NUM)

void printIp(const u32 ip)
{
	const u32 reordered = nativeI32(ip);
	printf(
		"%d.%d.%d.%d\n",
		(reordered>>(8*3))&0xff,
		(reordered>>(8*2))&0xff,
		(reordered>>(8*1))&0xff,
		(reordered>>(8*0))&0xff
	);
}

void printPort(const u16 port)
{
	printf("%d\n", nativeI16(port));
}

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
