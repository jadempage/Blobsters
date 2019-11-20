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
	char* foodName = " FOOD NAME "; 
	char* description = " DESC "; 
	int fill = 0;
	bool healthy = false;
	int price = 0;
	char* filepath = " NULL ";
};

class food {
public:
	foodItem genFoods();
	foodItem giveOOS();
}
;
