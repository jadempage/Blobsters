/*
 Name:		Blobsters.ino
 Created:	9/29/2019 10:17:18 PM
 Author:	Jade
*/

// the setup function runs once when you press reset or power the board

#ifndef bool


//#include <Game_Audio.h>
//#include "audio.h"

#include <sd_diskio.h>
#include <sd_defines.h>
#include <vfs_api.h>
#include <FSImpl.h>
#include <JPEGDecoder.h>
#include <M5Stack.h>
#include <FS.h>
#include <SD.h>
#include <ArduinoTrace.h>
#include "minigameHelper.h"
#include <AudioStatus.h>
#include <AudioOutputSTDIO.h>
#include <AudioOutputSerialWAV.h>
#include <AudioOutputNull.h>
#include <AudioOutputMixer.h>
#include <AudioOutputI2SNoDAC.h>
#include <AudioOutputI2S.h>
#include <AudioOutputFilterDecimate.h>
#include <AudioOutputBuffer.h>
#include <AudioOutput.h>
#include <AudioLogger.h>
#include <AudioGeneratorWAV.h>
#include <AudioGeneratorRTTTL.h>
#include <AudioGeneratorMP3a.h>
#include <AudioGeneratorMP3.h>
#include <AudioGeneratorMOD.h>
#include <AudioGeneratorMIDI.h>
#include <AudioGeneratorFLAC.h>
#include <AudioGeneratorAAC.h>
#include <AudioGenerator.h>
#include <AudioFileStream.h>
#include <AudioFileSourceSTDIO.h>
#include <AudioFileSourceSD.h>
#include <AudioFileSourcePROGMEM.h>
#include <AudioFileSourceID3.h>
#include <AudioFileSourceICYStream.h>
#include <AudioFileSourceHTTPStream.h>
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

void IRAM_ATTR isra() {
	if ((millis() - lastDebounceTime) > debounceDelay) {
		theGame.interruptAbtn();
		lastDebounceTime = millis();
	}
}

void IRAM_ATTR isrb() {
	if ((millis() - lastDebounceTime) > debounceDelay) {
		theGame.interruptBbtn();
		lastDebounceTime = millis();
	}
}

void IRAM_ATTR isrc() {
	if ((millis() - lastDebounceTime) > debounceDelay) {
		theGame.interruptCbtn();
		lastDebounceTime = millis();
	}
}

void IRAM_ATTR onInterTimer() {
	theGame.interruptTimer();
}


void setup() {
	TFT_eSPI tft = TFT_eSPI();
	m5.begin(); 
	tft.begin();
	Serial.begin(9600);
	attachInterrupt(37, isrc, FALLING);
	attachInterrupt(38, isrb, FALLING);
	attachInterrupt(39, isra, FALLING);
	// Set all chip selects high to avoid bus contention during initialisation of each peripheral


	if (!SD.begin()) {
		Serial.println("Card Mount Failed");
		return;
	}
	hw_timer_t* theTimer = timerBegin(0, 80, true);
	timerAttachInterrupt(theTimer, onInterTimer, true);
	timerAlarmWrite(theTimer, 600000000, true);
	timerAlarmEnable(theTimer);
	//2000000 = 2 seconds, We want like an hour IG so 3600000000, 600000000 = 10 min for testing 

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
//	curInventory->itemIList = {};
	curInventory->numOfFoods = 0;
	curInventory->numOfOthers = 0;  
	foodItem foodIList[30];
	curInventory->foodIList = foodIList;
	theGame.genShopItems(); 
	theGame.setUp();
	theGame.loadGameData(curInventory); 
	theGame.idleLoop(curInventory);
}
