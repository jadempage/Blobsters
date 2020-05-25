/*
 Name:		Blobsters.ino
 Created:	9/29/2019 10:17:18 PM
 Author:	Jade
*/

#ifndef bool
#include <HTTPClient.h>
#include "WiFi.h"
#include <Arduino.h>
#include <Wire.h>
#include "Preferences.h"
#include <sd_diskio.h>
#include <sd_defines.h>
#include <vfs_api.h>
#include <FSImpl.h>
#include <M5Stack.h>
#include <FS.h>
#include <SD.h>
#include <ArduinoTrace.h>
#include "minigameHelper.h"
#include <AudioStatus.h>
#include <AudioOutputSerialWAV.h>
#include <AudioOutputI2SNoDAC.h>
#include <AudioOutputI2S.h>
#include <AudioOutput.h>
#include <AudioLogger.h>
#include <AudioGeneratorWAV.h>
#include <AudioGenerator.h>
#include <AudioFileSourcePROGMEM.h>
#include <AudioFileSourceFS.h>
#include <AudioFileSourceBuffer.h>
#include <AudioFileSource.h>
#include "gameplay.h"
#include "sprites.h"
#define bool        int8_t
#endif

gamePlay theGame;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 250;
//Debounce times for making sure only one button press is registered

//Interrupt for "A" button (left)
void IRAM_ATTR isra() {
	if ((millis() - lastDebounceTime) > debounceDelay) {
		theGame.interruptAbtn();
		lastDebounceTime = millis();
	}
}

//Interrupt for "B" button (middle)
void IRAM_ATTR isrb() {
	if ((millis() - lastDebounceTime) > debounceDelay) {
		theGame.interruptBbtn();
		lastDebounceTime = millis();
	}
}

//Interrupt for "C" button (right) 
void IRAM_ATTR isrc() {
	if ((millis() - lastDebounceTime) > debounceDelay) {
		theGame.interruptCbtn();
		lastDebounceTime = millis();
	}
}

//General interrupt timer
void IRAM_ATTR onInterTimer() {
	theGame.interruptTimer();
}


void setup() {
	TFT_eSPI tft = TFT_eSPI();
	m5.begin(); 
	tft.begin();
	Serial.begin(9600);
	Wire.begin(21, 22, 400000);
	//Set up TFT, M5, Serial and wire
	attachInterrupt(37, isrc, FALLING);
	attachInterrupt(38, isrb, FALLING);
	attachInterrupt(39, isra, FALLING);
	// Set all chip selects high to avoid bus contention during initialisation of each peripheral
	if (!SD.begin()) {
		Serial.println("Card Mount Failed");
		return;
	}
	//Check SD is mounted
	hw_timer_t* theTimer = timerBegin(0, 80, true);
	timerAttachInterrupt(theTimer, onInterTimer, true);
	timerAlarmWrite(theTimer, 600000000, true);
	timerAlarmEnable(theTimer);
	/* 1 tick take 1/(80MHZ/80) = 1us so we set divider 80 and count up */
	//timer = timerBegin(0, 240, true);
	//timerAttachInterrupt(timer, &onTimer, true);
	//timerAlarmWrite(timer, 7200000000, true);
}

// the loop function runs over and over again until power down or reset
void loop() {
	Inventory* curInventory = new Inventory;
	curInventory->currentMoney = 0;
	curInventory->foodIList = {};
	curInventory->numOfFoods = 0;
	curInventory->numOfOthers = 0;  
	foodItem foodIList[30];
	curInventory->foodIList = foodIList;
	theGame.genShopItems(); 
	theGame.setUp();
	theGame.loadGameData(curInventory); 
	//Set up all game vars
	theGame.idleLoop(curInventory);
	//Main game loop! 
}
