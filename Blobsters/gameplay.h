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

struct Inventory; 

class gamePlay {
public:

	bool m_shouldContinue = true;
	void idleLoop(Inventory* curInventory);
	void genShopItems();
	void showShop(Inventory* curInventory);
	void showStats(Inventory* curInventory);
	void showMap(Inventory* curInventory);
	void showInventory(Inventory* curInventory);
	void clearButtons();
	void refloor(int xMin, int yMin, int xMax, int yMax, int xPosMod, int yPosMod, const short unsigned int* tile, int xMod, int yMod);
	void interruptTimer();
	char* mapLocationNames[3] = { "Shop", "Work", "Meet" };
	bool btnAPress;
	bool btnBPress;
	bool btnCPress;
	void interruptAbtn();
	void interruptBbtn();
	void interruptCbtn(); 

	struct curChar {
		char name[20]; 
		char colour[20];
		int happiness;
		int fullness;
	};

	curChar cChar; 

};
