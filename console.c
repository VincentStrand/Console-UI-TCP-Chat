#include "console.h"
#define NI_MAXHOST 400
#define NI_MAXSERV 400
#include <string.h>
//#include "main.c"

void drawBorder()
{
	for (int xpos = 0; xpos < WIDTH; xpos++)
	{
		writeChar((unsigned char)219, 0, xpos);
		writeChar((unsigned char)219, HEIGHT - 1, xpos);
	}
	for (int ypos = 0; ypos < HEIGHT ; ypos++)
	{
		writeChar((unsigned char)219, ypos, 0);
		writeChar((unsigned char)219, ypos, WIDTH -1);
	}
}



void mkSubWindow(int x, int y, int size)
{
	int pos = y + WIDTH * x;
	int endPos = pos + (WIDTH * size);
	for (int i = pos; i < endPos; i++)
	{
		for (int k = 0; k < size; k++)
		{
			if (i + k == x)
			consoleBuffer[i + k].Char.AsciiChar = (unsigned char)444;
			consoleBuffer[i + k].Attributes = BACKGROUND_BLUE |
							BACKGROUND_GREEN |
							BACKGROUND_RED |
							BACKGROUND_INTENSITY;
		}
		i = i + WIDTH - 1;
	}
	
}

void mkSubWindowii(int x, int y, int size, char text[])
{
	int level = 0;
	int pos = 0;
    int endx = x + size;
	//CHAR_INFO windowBuffer[size * size];

    int endy = y + size;
    //left to right
    for (int i = x; i < endx; i++)
    {
        writeChar((unsigned char)186, i, y);
        writeChar((unsigned char)186, i, endy);
    }
    //up and down
    for (int j = y; j < endy; j++)
    {
        writeChar((unsigned char)205, x, j);
        writeChar((unsigned char)205, endx, j);
    }
    writeChar((unsigned char)201, x, y);
    writeChar((unsigned char)187, x, endy);
    writeChar((unsigned char)200, endx, y);
    writeChar((unsigned char)188, endx, endy);
	for (int k = 0; k < strlen(text); k++)
	{
		
		writeChar(text[k], x + 1 + level, y + 1 + pos);
		pos++;
		if (pos == size - 2)
		{ 
			level++; 
			pos = 0;
		}
		
		
	}
	
}

void mkSubWindowiii(int x, int y, int xoff, int yoff, char text[])
{
	int level = 0;
	int pos = 0;
   
    //left to right
    for (int i = x; i < xoff; i++)
    {
        writeChar((unsigned char)186, i, y);
        writeChar((unsigned char)186, i, yoff);
    }
    //up and down
    for (int j = y; j < yoff; j++)
    {
        writeChar((unsigned char)205, x, j);
        writeChar((unsigned char)205, xoff, j);
    }
	
	//corners
    writeChar((unsigned char)201, x, y);
    writeChar((unsigned char)187, x, yoff);
    writeChar((unsigned char)200, xoff, y);
    writeChar((unsigned char)188, xoff, yoff);
	
	//poot text een bocks
	for (int k = 0; k < strlen(text); k++)
	{
		
		writeChar(text[k], x + 1 + level, y + 1 + pos);
		pos++;
		if (pos == xoff)
		{ 
			level++; 
			pos = 0;
		}
		
		
	}
	
}

void clrWindow(int x, int y, int xoff, int yoff)
{
	for (int i = 0; i < 56; i++)
	{
		for (int j= 0; j < 4;j++)
			writeChar(' ', (x +1) +j, (y+1) + i);
	}
}


void writeChar(char a, int x, int y)
{
	int pos = y + WIDTH * x;
	consoleBuffer[pos].Char.AsciiChar = a;
	consoleBuffer[pos].Attributes = BACKGROUND_BLUE |
							BACKGROUND_GREEN |
							BACKGROUND_RED |
							BACKGROUND_INTENSITY;
}

void clearScrn()
{
	for (j = 0; j < WIDTH * HEIGHT; j++)
						{
							consoleBuffer[j].Char.AsciiChar = ' ';
							consoleBuffer[j].Attributes =
							BACKGROUND_BLUE |
							BACKGROUND_GREEN |
							BACKGROUND_RED |
							BACKGROUND_INTENSITY;
						}
					Write = YES;
}

void setupWindow(char name[])
{
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	rHnd = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleTitle(name);
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
	SetConsoleScreenBufferSize(wHnd, bufferSize);
	
	clearScrn();
	
}

//read input buffer return malloc'd array
DWORD getInput(INPUT_RECORD **eventBuffer)
{
	
	DWORD numEvents = 0;
	DWORD numEventsRead = 0;
	
	//put num con input events in numEvents
	GetNumberOfConsoleInputEvents(rHnd, &numEvents);
	
	if (numEvents)
	{
		//allocate mem to store events
		*eventBuffer = malloc(sizeof(INPUT_RECORD) * numEvents);
		ReadConsoleInput(rHnd, *eventBuffer, numEvents, &numEventsRead);
	}
	return numEventsRead;
}

boundCheck(int *x, int *y)
{
  if (*x < 0)
  {
    *x = 0;
  }
  if (*x > WIDTH - 3)
  {
    *x = WIDTH - 3;
  }
  
  if (*y < 0)
  {
    *y = 0;
  }
  if (*y > HEIGHT - 3)
  {
    *y = HEIGHT - 3;
  }
}

void writeImageToBuffer(CHAR_INFO buffer[], int chars[], int colors[], int imageWidth, int imageHeight, int xoffset, int yoffset)
{
	int x, y;
	
	boundCheck(&xoffset, &yoffset);
	
	for(y = 0; y < imageHeight; y++)
	{
		for (x = 0; x < imageWidth; x++)
		{
			buffer[(x + xoffset) + WIDTH * (y + yoffset)].Char.AsciiChar = chars[x + imageWidth];
			buffer[(x + xoffset) + WIDTH * (y + yoffset)].Attributes = colors[x + imageWidth * y];
		}
	}
	return;
}

writeCircleToBuffer(CHAR_INFO buf[], int xoffset, int yoffset)
{
	boundCheck(&xoffset, &yoffset);
	
	buf[xoffset + (WIDTH * yoffset)].Char.AsciiChar = (unsigned char)7;
	buf[xoffset + (WIDTH * yoffset)].Attributes = BACKGROUND_BLUE |
	BACKGROUND_RED |
	BACKGROUND_GREEN |
	BACKGROUND_INTENSITY |
	BACKGROUND_RED;
}


WSADATA wsaData;
SOCKET listening;
struct sockaddr_in hint;
int eventHandler()
{
	if (WSAStartup(MAKEWORD(2,2),&wsaData) != 0)
	{
		mkSubWindowiii(10,20,12,32,"winsock no");
	}
	
	listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		mkSubWindowiii(20,20,22,38,"socket fail");
	}
	
	
	//listening port stuff
	
	hint.sin_family = AF_INET;
	hint.sin_addr.s_addr = inet_addr("127.0.0.1");
	hint.sin_port = htons(3333);
	bind(listening, (SOCKADDR*)&hint, sizeof(hint));
	listen(listening, 1);
	int pos = 0;
	int pos2 = 0;
	int level = 0;
	int level2 = 0;
	char input[4096];
	struct sockaddr_in client;
	int clientSize = sizeof(client);
	
	SOCKET clientSocket = accept(listening, (SOCKADDR*)&client, &clientSize);
	char host[NI_MAXHOST];
	char service[NI_MAXSERV];
	
	memset(host, 0, NI_MAXHOST);
	memset(service, 0, NI_MAXSERV);
	mkSubWindowiii(20,20,22,37,"client connected");
	
	if (getnameinfo((SOCKADDR*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
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
	while(1)
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
			mkSubWindowiii(10,20,12,36,"client was yeeted");
			break;
		}
		sprintf(input, "%d", bytesRecieved);
		
		//get input and number of events obtained
		numEventsRead = getInput(&eventBuffer);
		if (numEventsRead)
		{
			for (i = 0; i < numEventsRead; i++)
			{
				//check each event
				switch (eventBuffer[i].EventType)
				{
				
				case KEY_EVENT:
				switch (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode)
				{
					//if escape key is pressed
					case VK_ESCAPE:
						return 0;
					case VK_RETURN:
						if (eventBuffer[i].Event.KeyEvent.bKeyDown == 1)
						{
							for (int p = 0; p < strlen(input); p++)
							{
								if (p == 56)
								{
									level2++;
									pos2 = 0;
								}
								writeChar(input[p],2 + level2 ,12 + pos2);
								pos2++;
							}
							for (int d = 0; d < strlen(input); d++)
							{
								input[d] = "";
							}
							clrWindow(63,11,68,68);
							level2++;
							pos = 0;
							pos2 = 0;
							level = 0;
							Write = YES;
							break;
						}
						else
						break;
						
					break;
				}
				if (eventBuffer[i].Event.KeyEvent.bKeyDown == 1)
				{
					if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_RETURN)
						break;
					else
					{
						writeChar(eventBuffer[i].Event.KeyEvent.wVirtualKeyCode, 64 + level, 12 + pos);
						input[pos] = eventBuffer[i].Event.KeyEvent.wVirtualKeyCode;
						pos++;
						if (pos == 56)
						{
							level++;
							pos = 0;
						}
						Write = YES;
					}
				}
				break;
				
				//mouse events
				case MOUSE_EVENT:
					offsetx = eventBuffer[i].Event.MouseEvent.dwMousePosition.X;
					offsety = eventBuffer[i].Event.MouseEvent.dwMousePosition.Y;
					if (eventBuffer[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						writeImageToBuffer(consoleBuffer, REDRECTANGLE.chars, REDRECTANGLE.colors, REDRECTANGLE.width, REDRECTANGLE.height, offsetx -1, offsety - 1);
						Write = YES;
					}
					else if (eventBuffer[i].Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
					{
						writeCircleToBuffer(consoleBuffer, offsetx, offsety);
						Write = YES;
					}
					break;
				}
			}
			free(eventBuffer);
		}
		if (Write)
		{
			WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
			drawBorder();
			Write = NO;
		}
		send(clientSocket, buf, bytesRecieved + 1, 0);
	}
}