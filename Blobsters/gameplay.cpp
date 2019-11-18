  // 
// 
// 

#include "gameplay.h"
#include "sprites.h"


#define ZERO 1e-10
#define isBetween(A, B, C) ( ((A-B) > - ZERO) && ((A-C) < ZERO) )



foodItem foodListC[FOOD_QTY];

void gamePlay::idleLoop(Inventory* curInventory)
{
	strcpy(cChar.colour, "Blue");
	strcpy(cChar.name, "Thingy");
	cChar.fullness = 10;
	cChar.happiness = 10; 
	m_shouldContinue = true;
	int screensizex = 320;
	int screensizey = 240;
	int16_t xPosMod = 200;
	int16_t yPosMod = 180;
	uint16_t transparent = 0xFFFF;
	m5.Lcd.setSwapBytes(true);

	for (int x = 0; x < 320; x = x + 16) {
		for (int y = 175; y < 260; y = y + 16) {
			m5.Lcd.pushImage(x, y, 16, 16, floor_tile);
		}
	}
	m5.Lcd.drawPngFile(SD, "/bg/main_fancy.png", 0, 0);
	while (true) {
		int rando = (rand() % 10) + 1;
		if (rando < 5) {
			if (xPosMod - 5 > 60) {
				xPosMod = xPosMod - 16; //Go backwards
			}
		}
		else if (rando >= 5) {
			if (xPosMod + 5 < (screensizex - 64)) {
				xPosMod = xPosMod + 16; //Go forward
			}
		}
		m5.Lcd.pushImage(xPosMod, yPosMod, 64, 64, blue_front, transparent);
		delay(1000);
		refloor(0, 176, 320, 260, xPosMod, yPosMod, floor_tile, 64, 64);
		M5.update();
		if (btnAPress == true) {
			clearButtons();
			showStats(curInventory);
			idleLoop(curInventory);
		}
		if (btnBPress == true) {
			clearButtons();
			showMap(curInventory);
			idleLoop(curInventory);
		}
		if (btnCPress == true) {
			clearButtons();
		}
	}
}

template <typename T>
bool IsInBounds(const T& value, const T& low, const T& high) {
	return !(value < low) && !(high < value);
}

void gamePlay::genShopItems() {
	foodItem thisFoodItem;
	food curFoods;
	for (int i = 0; i < FOOD_QTY; i++) {
		thisFoodItem = curFoods.genFoods();
		foodListC[i] = thisFoodItem;
	}
}

void gamePlay::showShop(Inventory* curInventory) {
	food curFoods;
	int curSlot = 0; 
	bool updateStock = false; 
	Vector<foodItem> foodList; 
	m5.Lcd.drawPngFile(SD, "/bg/Shop.png", 0, 0);
	m5.Lcd.setTextSize(2);
	M5.Lcd.setTextColor(TFT_BLACK, 0x92A7);
	int curX = 98;
	int curY = 28; 
	
	char priceString[33];
	for (int i = 0; i < FOOD_QTY; i++) {
		const char* filePath = foodListC[i].filepath;
		if (strcmp(filePath, "/food/OOS.png") == 0) {
			m5.Lcd.drawPngFile(SD, filePath, curX - 5, curY - 5, 40, 40);
		}
		else {
			m5.Lcd.drawPngFile(SD, filePath, curX, curY, 40, 40);
		}
		curX = curX + 52;
		if (i == 2) {
			curY = curY + 48; 
			curX = 98; 
		}
	}
	while (!btnCPress) {
		M5.update();
		m5.Lcd.drawString(foodListC[curSlot].foodName, 80, 165);
		itoa(foodListC[curSlot].price, priceString, 10);
		m5.Lcd.drawString(priceString, 150, 195);
		if (btnAPress == true) {
			clearButtons();
			m5.Lcd.drawString("---", 150, 195);
			if (curSlot == FOOD_QTY - 1){
				curSlot = 0; 
			}
			else{
				curSlot = curSlot + 1;
			}
		}
		if (btnBPress == true) {
			clearButtons();
			if (foodListC[curSlot].price > 0) {
				int curX = 98;
				int curY = 28; 
				foodItem toAdd = foodListC[curSlot];
				curInventory->foodIList.push_back(toAdd);
				curInventory->numOfFoods = curInventory->numOfFoods + 1;
				DUMP(curInventory->numOfFoods);
				foodListC[curSlot] = curFoods.giveOOS();
				for (int i = 0; i < FOOD_QTY; i++) {
					const char* filePath = foodListC[i].filepath;
					if (strcmp(filePath, "/food/OOS.png") == 0) {
						m5.Lcd.drawPngFile(SD, filePath, curX - 5, curY - 5, 40, 40);
					}
					else {
						m5.Lcd.drawPngFile(SD, filePath, curX, curY, 40, 40);
					}
					curX = curX + 52;
					if (i == 2) {
						curY = curY + 48;
						curX = 98;
					}
				}
			}
			else {
				//You can't buy an out of stock item. Link in sound sys to play a uh-uh sound 
			}

		}
	}
	if (btnCPress == true) {
		clearButtons();
		return;
	}
}


void gamePlay::showStats(Inventory* curInventory) {
	m5.Lcd.drawPngFile(SD, "/bg/summ.png", 0, 0);
	char str[2];
	int x = 82;
	int y = 115;
	for (int i = 0; i < cChar.fullness; i++) {
		m5.Lcd.fillRect(x, y, 16, 12, RED);
		x = x + 16; 
	}
	x = 82;
	y = 80;
	for (int i = 0; i < cChar.happiness; i++) {
		m5.Lcd.fillRect(x, y, 16, 12, RED);
		x = x + 16;
	}
	/*itoa((cChar.fullness), str, 10);*/
	m5.Lcd.setTextSize(6);
	M5.Lcd.setTextColor(TFT_BLACK, TFT_WHITE);
	m5.Lcd.drawString(cChar.name, 90, 25); 
	//m5.Lcd.drawString(str, 85, 120); 
	while (!btnCPress) {
		M5.update();
		if (btnAPress == true) {
			clearButtons();
		}
		if (btnBPress == true) {
			Serial.write("Button B Pressed");
			clearButtons();
			showInventory(curInventory);
		}
	}
	if (btnCPress == true) {
		clearButtons();
		return;
	}
}

void gamePlay::showMap(Inventory* curInventory) {
int curPos = 0;
   int textX = 16;
   int textY = 192;
   M5.Lcd.setTextColor(BLACK);
   M5.Lcd.setTextSize(4);
   m5.Lcd.drawPngFile(SD, "/bg/menu.png", 0, 0);
   M5.Lcd.drawString(mapLocationNames[0], textX , textY);
	while (!btnCPress) {
		M5.update();
		if (btnAPress == true) {
			clearButtons();
			delay(2000);
			refloor(12, 192, 112, 224, textX, textY, map_box_tile, 160, 32);
			curPos = curPos + 1;
			if (curPos > 2) {
				curPos = 0;
			}
			M5.Lcd.drawString(mapLocationNames[curPos], textX, textY);
		}
		if (btnBPress == true) {
			clearButtons();
			if (strcmp(mapLocationNames[curPos], "Shop") == 0){
				clearButtons();
				showShop(curInventory);
			}
			else if (strcmp(mapLocationNames[curPos], "Work") == 0) {
				//Do the work
			}
			else if (strcmp(mapLocationNames[curPos], "Meet") == 0) {
				//Do the meet
			}
		}
	}
	if (btnCPress == true) {
		clearButtons();
		return;
	}
}

void gamePlay::showInventory(Inventory* curInventory)
{
	//@TO DO: Add handler for when so many items they won't fit on the screen
	Serial.write("In inventory... "); 
	int curX = 10;
	int curY = 50;
	m5.Lcd.clear(WHITE);
	m5.Lcd.drawPngFile(SD, "/bg/inv.png", 0, 0);
	int itemsSize = curInventory->numOfFoods;
	 DUMP(itemsSize);
	 Serial.write("\n");
	if (itemsSize < 1) {
		m5.Lcd.drawString("Empty :( ", curX, curY);
	}
	else {
		for (int i = 0; i < itemsSize - 1; i++) {
			Serial.write("Cycling: ");
			DUMP(i); 
			foodItem testItem = curInventory->foodIList.at(i);
			Serial.write("GOT TEST ITEM");
			DUMP(testItem.foodName); 
			const char* filePath = testItem.filepath;
			Serial.write("GOT FILE PATH: \n");
			DUMP(filePath); 
			m5.Lcd.drawPngFile(SD, filePath, curX, 10, 96, 96);
			m5.Lcd.drawString(curInventory->foodIList[i].foodName, curX, curY);
			curX = curX + 20;
		}
	}
	while (!btnCPress) {
		m5.update();
	}
	if (btnCPress == true) {
		clearButtons();
		return; 
	}
}

void gamePlay::clearButtons() {
	btnAPress = false;
	btnBPress = false;
	btnCPress = false; 
}





//Params: x/yMin = minimum x/y, x/yMax = max x/y Pos, tile = tile sprite, x/ypos mod = x/y of where sprite is, x/yMod = how big the thing to cover is 
void gamePlay::refloor(int xMin, int yMin, int xMax, int yMax, int xPosMod, int yPosMod, const short unsigned int* tile, int xMod, int yMod) {
	for (int x = xMin; x < xMax; x = x + 16) {
		for (int y = yMin; y < yMax; y = y + 16) {
			if (IsInBounds(x, xPosMod - xMod, xPosMod + xMod)) { // Does this X pos need updating
				m5.Lcd.pushImage(x, y, 16, 16, tile);
			}
			if (IsInBounds(y, yPosMod - yMod, yPosMod + yMod)) { // Does this Y pos need updating 
				m5.Lcd.pushImage(x, y, 16, 16, tile);
			}

		}
	}
}

void gamePlay::interruptTimer()
{
	Serial.write("Char fullness down"); 
	cChar.fullness = cChar.fullness - 1; 
}

void gamePlay::interruptAbtn()
{
	btnAPress = true;
}

void gamePlay::interruptBbtn()
{
	btnBPress = true; 
}

void gamePlay::interruptCbtn()
{
	btnCPress = true; 
}
