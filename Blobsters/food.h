// food.h

#ifndef _FOOD_h
#define _FOOD_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif

struct foodItem {
	const char* name; 
	const char* description;
	int fill;
	bool healthy;
	int price;
	const char* filepath; 
};

class food {
public:
	foodItem* foodList[10];
	void genFoods(int amount);
}
;