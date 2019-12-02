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

#include <M5Stack.h>
#include <Vector.h>
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
	void showInventory(Inventory* curInventory);
	void showFridge(Inventory* curInventory);
	void clearButtons();
	void refloor(int xMin, int yMin, int xMax, int yMax, int xPosMod, int yPosMod, const short unsigned int* tile, int xMod, int yMod);
	void interruptTimer();
	char* mapLocationNames[3] = { "Shop", "Work", "Meet" };
	char* invLocationNames[2] = { "Items", "Food" };
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
	int noInterrupts = 0; 
	bool saveInter = false; 

	struct curChar {
		char name[20]; 
		char colour[20];
		int happiness;
		int fullness;
		bool isAlive = true; 
	};

	curChar cChar; 

};
