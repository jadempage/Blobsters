// gameplay.h
#include <M5Stack.h>

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
	void refloor(int xPosMod, int yPosMod);

};
