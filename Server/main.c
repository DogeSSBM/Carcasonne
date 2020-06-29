// SERVER
#define PLAYERMAX	5
#define PORT	8421
#define BUFFERLEN	1024
#include "Includes.h"

typedef enum{CMD_QUIT, CMD_START, CMD_NUMCMD, CMD_NOTCMD}CmdId;
const char *CmdTextArr[CMD_NUMCMD] = {"/quit", "/start"};

CmdId parseCmd(const char* text)
{
	if(text[0] != '/')
		return CMD_NOTCMD;
	const uint len = strlen(text);
	for(uint i = 0; i < CMD_NUMCMD; i++){
		if(len != strlen(CmdTextArr[i]))
			continue;
		if(!strncmp(text, CmdTextArr[i], len))
			return i;
	}
	return CMD_NOTCMD;
}

CmdId readCmd(TCPsocket player)
{
	char buffer[BUFFERLEN] = {0};
	tcpReadData(player, buffer, BUFFERLEN);
	char *nl = &(buffer[BUFFERLEN-1]);
	do{
		*nl = '\0';
	}while(nl = strchr(buffer, '\n'));
	CmdId cmd = parseCmd(buffer);
	if(cmd == CMD_NOTCMD)
		printf("Message -\n%s\n", buffer);
	return cmd;
}

uint connectPlayers(TCPsocket sSock, SocketSet playerSet, TCPsocket *playerArr)
{
	uint playerCount = 0;
	while(playerCount < PLAYERMAX){
		if(playerArr[playerCount] = tcpCheckForClient(sSock)){
			playerCount = tcpAddToSet(playerSet, playerArr[playerCount]);
			IPaddress playerIp = tcpGetClientIp(playerArr[playerCount]);
			playerCount++;
			printf("Player %u connected!\n", playerCount);
			printf("\tIP: ");
			printIp(playerIp.host);
			printf("\tPort: ");
			printIp(playerIp.host);
		}
		TCPsocket clientDataSock = tcpGetSetDataTimeout(
			playerSet,
			playerArr,
			100
		);
		if(clientDataSock){
			switch(readCmd(clientDataSock)) {
				case CMD_QUIT:
					printf("Exiting :3\n");
					tcpFreeSet(playerSet);
					tcpFreeSetArr(playerArr, playerCount);
					exit(0);
					break;
				case CMD_START:
					printf("Starting game!\n");
					return playerCount;
					break;
				default:

					break;
			}
		}
	}
	return playerCount;
}

int main(int argc, char const *argv[])
{
	init();

	TCPsocket sSock = tcpStartServer(PORT);
	SocketSet playerSet = tcpNewSet(PLAYERMAX);
	TCPsocket playerArr[PLAYERMAX] = {0};
	uint playerCount = connectPlayers(sSock, playerSet, playerArr);

	while(1){
		char buffer[BUFFERLEN] = {0};
		TCPsocket clientDataSock = NULL;
		while(!clientDataSock){
			clientDataSock = tcpGetSetDataTimeout(
				playerSet,
				playerArr,
				100
			);
		}
		tcpReadData(clientDataSock, buffer, BUFFERLEN);
		char *nl = &(buffer[BUFFERLEN-1]);
		do{
			*nl = '\0';
		}while(nl = strchr(buffer, '\n'));
		switch(parseCmd(buffer)) {
			case CMD_QUIT:
				printf("Exiting :3\n");
				tcpFreeSet(playerSet);
				tcpFreeSetArr(playerArr, playerCount);
				exit(0);
				break;
			case CMD_START:
				printf("Starting game!\n");
				break;
			case CMD_NOTCMD:
				printf("Message -\n%s\n", buffer);
				break;
		}
	}
	return 0;
}
