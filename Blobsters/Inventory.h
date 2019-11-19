#pragma once
#include "gameplay.h"

struct foodItem; 
struct itemStruct; 


struct Inventory {
	foodItem* foodIList;
	//Vector<foodItem> foodIList;
	Vector<itemStruct> itemIList; 
	int numOfFoods;
	int numOfOthers;
	int currentMoney;
};

class thisInventory {
public:
	int currentMoney; 
	void useFoodItem(foodItem theItem);
};
