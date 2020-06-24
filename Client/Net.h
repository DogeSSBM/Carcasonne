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

IPaddress tcpResolveHost(const char *hostname, const u16 port)
{
	IPaddress ip = {0};
	if(SDLNet_ResolveHost(&ip, hostname, port) == -1){
		printf(
			"SDLNet_ResolveHost error:\n\t%s\n",
			SDLNet_GetError()
		);
		exit(1);
	}
	printf(
		"Server hostname %s resolved into IPaddress type over port %d\n",
		hostname,
		port
	);
	return ip;
}

IPaddress tcpGetLocalIp(const u16 port)
{
	IPaddress addr = {0};
	if(SDLNet_ResolveHost(&addr, NULL, port) == -1){
		printf("Could not resolve server hostname\n");
		printf(
			"SDLNet_ResolveHost error:\n\t%s\n",
			SDLNet_GetError()
		);
		exit(1);
	}
	printf("Got servers ip\n");

	return addr;
}

TCPsocket tcpOpen(IPaddress addr)
{
	TCPsocket socket = {0};
	if(!(socket = SDLNet_TCP_Open(&addr))){
		printf(
			"SDLNet_TCP_Open error:\n\t%s\n",
			SDLNet_GetError()
		);
		exit(1);
	}
	printf("Server socket (sSock) opened for listening\n");
	return socket;
}

TCPsocket tcpStartServer(const uint port)
{
	return tcpOpen(tcpGetLocalIp(port));
	printf("Server started\n");
}

TCPsocket tcpWaitForClient(const TCPsocket server)
{
	TCPsocket client;
	while(!(client = SDLNet_TCP_Accept(server))){
		SDL_Delay(100);
	}
	printf("Client connected\n");
	return client;
}

IPaddress tcpGetClientIp(const TCPsocket client)
{
	IPaddress clientIp = {0};
	IPaddress *clientIpPtr = NULL;
	if(!(clientIpPtr = SDLNet_TCP_GetPeerAddress(client))){
		printf(
			"SDLNet_TCP_GetPeerAddress error:\n\t%s\n",
			SDLNet_GetError()
		);
		exit(1);
	}
	clientIp.host = clientIpPtr->host;
	clientIp.port = clientIpPtr->port;
	printf("\tIP: ");
	printIp(clientIp.host);
	printf("\tPort: ");
	printPort(clientIp.port);
	return clientIp;
}
