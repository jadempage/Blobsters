
/*
 Name:		Blobsters.ino
 Created:	9/29/2019 10:17:18 PM
 Author:	Jade
*/

// the setup function runs once when you press reset or power the board

#ifndef bool

#include <Vector.h>
#include <M5Stack.h>
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

void IRAM_ATTR onTimer() {
	theGame.interruptTimer();
}


void setup() {
	m5.begin();
	Serial.begin(9600);
	hw_timer_t* timer = NULL;
	attachInterrupt(37, isrc, FALLING);
	attachInterrupt(38, isrb, FALLING);
	attachInterrupt(39, isra, FALLING);
	if (!SD.begin()) {
		M5.Lcd.println("Card failed, or not present");
	}
	/* 1 tick take 1/(80MHZ/80) = 1us so we set divider 80 and count up */
	timer = timerBegin(0, 240, true);
	timerAttachInterrupt(timer, &onTimer, true);
	timerAlarmWrite(timer, 7200000000, true);
}

// the loop function runs over and over again until power down or reset
void loop() {
	Inventory* curInventory = new Inventory;
	curInventory->currentMoney = 0;
	curInventory->foodIList = {};
	curInventory->itemIList = {};
	curInventory->numOfFoods = 0;
	curInventory->numOfOthers = 0;  
	foodItem foodIList[30];
	curInventory->foodIList = foodIList;
	theGame.genShopItems(); 
	theGame.idleLoop(curInventory);
}
