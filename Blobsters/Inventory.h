#pragma once
#include "gameplay.h"
#include "food.h"
struct foodItem; 
struct itemStruct; 


struct Inventory {
	foodItem * foodIList[30];
	Vector<itemStruct> itemIList; 
	int numOfFoods;
	int numOfOthers;
	int currentMoney;
};

class thisInventory {
public:
	void useFoodItem(foodItem theItem);
};
