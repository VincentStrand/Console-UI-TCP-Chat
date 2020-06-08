#include <winsock2.h>
#include <stdio.h>

int initNet()
{
	WSADATA wsa;
	SOCKET s;
	
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		mkSubWindowiii(10,20,12,32,"winsock no");
	}
	mkSubWindowiii(10,20,12,32,"winsock yes");
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		mkSubWindowiii(20,20,22,36,"socket fail");
	}
	mkSubWindowiii(20,20,22,36,"socket not fail");
	
	return 0;
}


int initNetii()
{
	WSADATA wsData;
	WORD ver = MAKEWORD(2,2);
	
	//init winsock
	int wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0)
	{
		mkSubWindowiii(10,20,12,32,"winsock no");
	}
	
	//create listening socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		mkSubWindowiii(20,20,22,36,"socket fail");
	}
	
	//ip addr and port | will be moved later
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(3333);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;
	
	bind(listening, (sockaddr*)&hint, sizeof(hint));
	
	listen(listening, SOMAXCONN);
	
	//client stuff
	sockaddr_in client;
	int clientSize = sizeof(client);
	
	SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
	char host[NI_MAXHOST];
	char service[NI_MAXSERV];
	
	memset(host, 0, NI_MAXHOST);
	memset(service, 0, NI_MAXSERV);
	
	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	{
		mkSubWindowiii(10,20,12,32,"client connected");
	}
	else
	{
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		mkSubWindowiii(10,20,12,32,"client connected");
	}
	
	closesocket(listening);
	
	char buf[4096];
	
	while (1)
	{
		memset(buf, 0, 4096);
		
		int bytesRecieved = recv(clientSocket, buf, 4096, 0);
		if (bytesRecieved == SOCKET_ERROR)
		{
			mkSubWindowiii(10,20,12,32,"recv() did a fucky wucky");
			break;
		}
		
	if (bytesRecieved == 0)
	{
		mkSubWindowiii(10,20,12,32,"client was yeeted");
		break;
	}
	
	send(clientSocket, buf, bytesRecieved + 1, 0);
	}
	closesocket(clientSocket);
	WSACleanup();
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}