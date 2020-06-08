#include <winsock2.h>

int main()
{	
	/*
		note and y are often flipped because i cant be bothered to fix it
	*/
	
	//set window stuff and start input event handler
	setupWindow("Server");
	
	//server list
	mkSubWindowiii(1,1,68,10,"servers:");
	//text display
	mkSubWindowiii(1,11,62,68,"");
	//text input
	mkSubWindowiii(63,11,68,68,"");
	drawBorder();
	printf("waiting for connection");

	WSACleanup();
	eventHandler();
	return 0;
}

