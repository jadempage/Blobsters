
/*
 Name:		Blobsters.ino
 Created:	9/29/2019 10:17:18 PM
 Author:	Jade
*/

// the setup function runs once when you press reset or power the board

#ifndef bool
#include "gameplay.h"
#define bool        int8_t
#endif


void setup() { 
	m5.begin();
	if (!SD.begin()) {
		M5.Lcd.println("Card failed, or not present");
	}
}


// the loop function runs over and over again until power down or reset
void loop() {
	gamePlay theGame;
	theGame.idleLoop();
}
