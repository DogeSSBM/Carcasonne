#pragma once

uint getPort(void)
{
	int port = 0;
	do{
		printf("Enter port:\n(or press enter for port 8421)\n");
		port = getInt();
	}while(port < 0 || port > 99999);
	return port?port:8421;
}

u32 getIp(void)
{
	char buffer[100] = {0};
	printf("Enter server hos t:\n(or press enter for localhost)");
	fgets(buffer, 99, stdin);
	if(buffer[strlen(buffer)-1] != '\n'){
		printf("Host too long!\n");
		exit(1);
	}
	buffer[strlen(buffer)-1] = '\0';
	IPaddress ip;
	if(SDLNet_ResolveHost(&ip, buffer, 0) == -1){
		printf(
			"Failed resolve! Error: %s\n",
			SDLNet_GetError()
		);
		exit(1);
	}
	return ip.host;
}
