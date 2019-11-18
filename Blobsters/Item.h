#pragma once
#include "gameplay.h"

struct itemStruct {
	const char* itemName;
	const char* description;
	int price;
	const char* filepath;
};

class item {
public:
	Vector<itemStruct> itemVList;
	item genItem();
};
