// gameplay.h
#include <M5Stack.h>
#include <atlstr.h>
#ifndef _GAMEPLAY_h
#define _GAMEPLAY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#endif

class gamePlay {
public:
	
	bool m_shouldContinue = true;
	void idleLoop();
	void showStats();
	void showMap();
	void refloor(int xMin, int yMin, int xMax, int yMax, int xPosMod, int yPosMod, const short unsigned int* tile, int xMod, int yMod);
	void interruptTimer();
	//void spriteTest();
	//enum mapLocation { Shop, Work, Meet };
	char* mapLocationNames[3] = { "Shop", "Work", "Meet" };
	bool btnAPress;
	bool btnBPress;
	bool btnCPress;
	void interruptAbtn();
	void interruptBbtn();
	void interruptCbtn(); 

	struct curChar {
		CString name; 
		CString colour;
		int happiness;
		int fullness;
	};

	curChar cChar; 

};
