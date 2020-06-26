#pragma once

#define nativeI32(NUM)	SDL_SwapBE32(NUM)
#define nativeI16(NUM)	SDL_SwapBE16(NUM)

typedef SDLNet_SocketSet SocketSet;

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

TCPsocket tcpConnectToServer(IPaddress addr)
{
	TCPsocket server = {0};
	if(!(server = SDLNet_TCP_Open(&addr))){
		printf(
			"SDLNet_TCP_Open error:\n\t%s\n",
			SDLNet_GetError()
		);
		exit(1);
	}
	printf("Established connection with server\n");
	return server;
}

TCPsocket tcpStartClient(const char *serverHostname, const u16 serverPort)
{
	return tcpConnectToServer(tcpResolveHost(serverHostname, serverPort));
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

TCPsocket tcpCheckForClient(const TCPsocket server)
{
	return SDLNet_TCP_Accept(server);
}

TCPsocket tcpWaitForClient(const TCPsocket server)
{
	TCPsocket client;
	while(!(client = SDLNet_TCP_Accept(server))){
		SDL_Delay(100);
	}
	// printf("Client connected\n");
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
	// printf("\tIP: ");
	// printIp(clientIp.host);
	// printf("\tPort: ");
	// printPort(clientIp.port);
	return clientIp;
}

SocketSet tcpNewSet(const uint size)
{
	SocketSet set = SDLNet_AllocSocketSet(size);
	if(!set){
		printf("SDLNet_AllocSocketSet: %s\n", SDLNet_GetError());
		exit(1);
	}
	return set;
}

void tcpFreeSet(SocketSet set)
{
	SDLNet_FreeSocketSet(set);
}

void tcpFreeSetArr(TCPsocket *setArr, uint count)
{
	for(uint i = 0; i < count; i++){
		SDLNet_TCP_Close(setArr[i]);
		setArr[i] = NULL;
	}
}

uint tcpAddToSet(SocketSet set, const TCPsocket socket)
{
	const int setSize = SDLNet_TCP_AddSocket(set, socket);
	if(setSize==-1){
		printf("SDLNet_AddSocket: %s\n", SDLNet_GetError());
		exit(1);
	}
	return setSize;
}

TCPsocket tcpGetSetData(const SocketSet set, TCPsocket *setArr)
{
	if(SDLNet_CheckSockets(set, 0)){
		uint i = 0;
		while(!SDLNet_SocketReady(setArr[i])){
			i++;
		}
		return setArr[i];
	}
	return NULL;
}

TCPsocket tcpGetSetDataTimeout(const SocketSet set, TCPsocket *setArr, const uint ms)
{
	if(SDLNet_CheckSockets(set, ms)){
		uint i = 0;
		while(!SDLNet_SocketReady(setArr[i])){
			i++;
		}
		return setArr[i];
	}
	return NULL;
}

uint tcpReadData(TCPsocket socket, const char *buffer, uint len)
{
	if(!socket)
		return 0;

}
