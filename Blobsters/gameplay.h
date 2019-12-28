// gameplay.h
#pragma once

#ifndef _GAMEPLAY_h
#define _GAMEPLAY_h
#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#endif

#include <Arduino.h>
#include <Wire.h>
#include "math.h"
#include "bmm150.h"
#include "bmm150_defs.h"
#include <FS.h>
#include <SD.h>
#include <JPEGDecoder.h>
//#include <TFT_eSPI.h>
#include <M5Stack.h>
//#include <SPI.h>
#include "audio.h"
#include "minigameHelper.h"
#include <ArduinoTrace.h>
#include "food.h"
#include "Item.h"
#include "Inventory.h"
#define FOOD_QTY 6
#define FRIDGE_QTY 10
#define FRIDGE_PAGES 3 

struct Inventory; 

class gamePlay {
public:

	bool m_shouldContinue = true;
	void idleLoop(Inventory* curInventory);
	void setUp();
	void genShopItems();
	void showShop(Inventory* curInventory);
	void showStats(Inventory* curInventory);
	void showMap(Inventory* curInventory);
	int gameBoard();
	void showInventory(Inventory* curInventory);
	void showFridge(Inventory* curInventory);
	void clearButtons();
	void refloor(int xMin, int yMin, int xMax, int yMax, int xPosMod, int yPosMod, const short unsigned int* tile, int xMod, int yMod);
	void interruptTimer();
	void timerHandler(Inventory *curInventory);
	char* mapLocationNames[3] = { "Shop", "Play", "Meet" };
	char* invLocationNames[2] = { "Items", "Food" };
	char* gameNames[8] = { "HiLo", "Pong", "Treasure", "Game4", "Game5", "Game6", "Game7", "Game8", };
	bool btnAPress;
	bool btnBPress;
	bool btnCPress;
	void interruptAbtn();
	void interruptBbtn();
	void interruptCbtn();
	void saveGameData(Inventory* curInventory);
	void loadGameData(Inventory* curInventory);
	void removeChar(char* str, unsigned int index);
	char* findInFile(String toFind, String fString);
	int game_highlow();
	int game_pong();
	int game_treasure(); 
	void gameOverScreen(int winnings, bool didWin);
	int noInterrupts = 0; 
	int hungerInterrupts = 0;
	int happinessInterrupts = 0;
	int ageInterrupts = 0; 
	int saveInterrupts = 0; 
	bool checkInterrupts;
	bool BMM150CalDone = false; 
	bool BMM150InitDone = false; 


	struct curChar {
		char name[20]; 
		char colour[20];
		int happiness;
		int fullness;
		bool isAlive = true; 
		int age; 
	};

	curChar cChar; 

};
