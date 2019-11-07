  // 
// 
// 

#include "gameplay.h"
#include "sprites.h"


#define ZERO 1e-10
#define isBetween(A, B, C) ( ((A-B) > - ZERO) && ((A-C) < ZERO) )
SDUtils SDHandler;

void gamePlay::idleLoop()
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
      btnAPress = false; 
			showStats();
		}
		if (btnBPress == true) {
			btnBPress = false; 
			showMap(); 
		}
		if (btnCPress == true) {
			btnCPress = false;
		}
	}
}

template <typename T>
bool IsInBounds(const T& value, const T& low, const T& high) {
	return !(value < low) && !(high < value);
}

void gamePlay::showShop() {
	int curSlot = 1; 
	m5.Lcd.drawPngFile(SD, "/bg/Shop.png", 0, 0);
	m5.Lcd.setTextSize(3);
	M5.Lcd.setTextColor(TFT_BLACK, TFT_WHITE);
	int curX = 88;
	int curY = 23; 
	food curFoods;
	char * priceString;
	curFoods.genFoods(3);
	for (int i = 0; i < 3; i++) {
		const char* filePath = curFoods.foodList[i]->filepath;
		m5.Lcd.drawPngFile(SD, filePath, curX, curY); 
		curX = curX + 52;
	}
    m5.Lcd.drawString(curFoods.foodList[curSlot]->name, 115, 160);
    itoa(curFoods.foodList[curSlot]->price, priceString, 10);
	while (!btnCPress) {
		M5.update();
		m5.Lcd.drawString(curFoods.foodList[curSlot]->name, 115, 160);
		itoa(curFoods.foodList[curSlot]->price, priceString, 10);
		m5.Lcd.drawString(priceString, 150, 200);
		if (btnAPress == true) {
			btnAPress = false;
			curSlot = curSlot + 1;
		}
	}
	if (btnCPress == true) {
		btnCPress = false;
		showMap();
	}
}


void gamePlay::showStats() {
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
	}
	if (btnCPress == true) {
		btnCPress = false;
		idleLoop();
	}
}

void gamePlay::showMap() {
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
			delay(2000);
			refloor(12, 192, 112, 224, textX, textY, map_box_tile, 160, 32);
			curPos = curPos + 1;
			if (curPos > 2) {
				curPos = 0;
			}
			btnAPress = false;
			M5.Lcd.drawString(mapLocationNames[curPos], textX, textY);
		}
		if (btnBPress == true) {
			if (mapLocationNames[curPos] == "Shop") {
				showShop(); 
			}
			else if (mapLocationNames[curPos] == "Work") {
				//Do the work
			}
			else if (mapLocationNames[curPos] == "Meet") {
				//Do the meet
			}
		}
	}
	if (btnCPress == true) {
		btnCPress = false;
		idleLoop(); 
	}
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
