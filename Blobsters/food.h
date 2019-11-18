// food.h
#pragma once

#ifndef _FOOD_h
#define _FOOD_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif

#include "gameplay.h"

struct foodItem {
	const char* foodName; 
	const char* description;
	int fill;
	bool healthy;
	int price;
	const char* filepath; 
};

class food {
public:
	/*foodItem* foodList[10];*/
	Vector<foodItem> foodVList;
	foodItem genFoods();
	foodItem giveOOS();
}
;
