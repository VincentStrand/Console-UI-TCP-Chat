#include <stdio.h>

#include <stdlib.h>
#include <windows.h>
#include "redRectangle.h"
#include <time.h>

#define WIDTH 70
#define HEIGHT 70
#define YES 1
#define NO 0
#define VK_C 0x43 //virtual key c def
#define VK_Q 0x51 // virtual q def

//write and read handlers
HANDLE wHnd;
HANDLE rHnd;

//variables or smth
/************************************************************************/

int x,y;
int j, offsetx, offsety;
int Write = NO;
	

DWORD i;	
SMALL_RECT windowSize = {0, 0, WIDTH - 1, HEIGHT - 1};
COORD bufferSize = {WIDTH, HEIGHT};
	
//variables to pass to WriteConsoleOutput
COORD characterBufferSize = {WIDTH, HEIGHT};
COORD characterPosition = {0, 0};
SMALL_RECT consoleWriteArea = {0, 0, WIDTH - 1, HEIGHT - 1};
	
//char_info blabla data characters
CHAR_INFO consoleBuffer[WIDTH * HEIGHT];


//smthpointer to input record
INPUT_RECORD *eventBuffer;

DWORD numEventsRead = 0;

//function declarations
/******************************************************************/
void clearScrn();
void setupWindow(char name[]);
void writeImageToBuffer(CHAR_INFO buffer[], int chars[], int colors[], int imageWidth, int imageHeight, int xoffset, int yoffset);
int eventHandler();
void writeChar(char a, int x, int y);
