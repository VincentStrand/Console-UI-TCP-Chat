int main()
{	
	/*
		note and y are often flipped because i cant be bothered to fix it
	*/
	
	//set window stuff and start input event handler
	setupWindow("cia killed terry");
	char oof[100];
	//scanf("%s", &oof);
	//oof[10] = stime();
	
	//server list
	mkSubWindowiii(1,1,68,10,"servers");
	//text display
	mkSubWindowiii(1,11,62,68,"test test test oooooooooooooooo");
	//text input
	mkSubWindowiii(63,11,68,68,"test");
	
	drawBorder();
	eventHandler();
	return 0;
}