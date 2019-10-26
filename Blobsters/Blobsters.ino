
/*
 Name:		Blobsters.ino
 Created:	9/29/2019 10:17:18 PM
 Author:	Jade
*/

// the setup function runs once when you press reset or power the board

#ifndef bool
#include "gameplay.h"
#include "sprites.h"
#define bool        int8_t
#endif

gamePlay theGame;

void IRAM_ATTR isra() {
	theGame.interruptAbtn(); 
	//m5.Lcd.print("A INTERRUPT ");
}

void IRAM_ATTR isrb() {
	theGame.interruptBbtn();
	//m5.Lcd.print("B INTERRUPT ");
}

void IRAM_ATTR isrc() {
	theGame.interruptCbtn();
	//m5.Lcd.print("C INTERRUPT ");
}


void setup() { 
	m5.begin();
	attachInterrupt(37, isrc, FALLING);
	attachInterrupt(38, isrb, FALLING);
	attachInterrupt(39, isra, FALLING);
	if (!SD.begin()) {
		M5.Lcd.println("Card failed, or not present");
	}
}

// the loop function runs over and over again until power down or reset
void loop() {
	theGame.idleLoop();
}


