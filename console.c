#include "console.h"

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
		if (pos == xoff - 2)
		{ 
			level++; 
			pos = 0;
		}
		
		
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

int eventHandler()
{
	while(1)
	{
		//get input and number of events obtained
		numEventsRead = getInput(&eventBuffer);
		
		//if more thant 0 are read
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
					case VK_C:
						if (eventBuffer[i].Event.KeyEvent.bKeyDown == 0)
						{
							clearScrn();
							drawBorder();
							mkSubWindowiii(1,1,68,10,"servers");
							//text display
							mkSubWindowiii(1,11,62,68,"test test test oooooooooooooooo");
							//text input
							mkSubWindowiii(63,11,68,68,"test");
						}
					/*case VK_Q:
						offsetx = eventBuffer[i].Event.MouseEvent.dwMousePosition.X;
						offsety = eventBuffer[i].Event.MouseEvent.dwMousePosition.Y;
						mkSubWindowii(offsetx,offsety,10);*/
					break;
				}
				break;
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
						//writeCircleToBuffer(consoleBuffer, offsetx, offsety);
						mkSubWindow(offsety,offsetx,10);
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
			//WriteConsoleOutputA(wHnd, windowBuffer, wcharacterBufferSize, wcharacterPosition, &windowWriteArea);
			drawBorder();
			Write = NO;
		}
	}
}