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
		if (saveInter == true) {
			//saveGameData(curInventory);
			saveInter = false; 
		}
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
			showInventory(curInventory); 
			idleLoop(curInventory);
		}
	}
}

template <typename T>
bool IsInBounds(const T& value, const T& low, const T& high) {
	return !(value < low) && !(high < value);
}

void gamePlay::setUp() {
	//Only run this once!
	strcpy(cChar.colour, "Blue");
	strcpy(cChar.name, "Thingy");
	cChar.fullness = 10;
	cChar.happiness = 10;
}

void gamePlay::genShopItems() {
	foodItem thisFoodItem;
	food curFoods;
	for (int i = 0; i < FOOD_QTY; i++) {
		thisFoodItem = curFoods.genFoods(1, 0);
		foodListC[i] = thisFoodItem;
	}
}

void gamePlay::showShop(Inventory* curInventory) {
	food curFoods;
	int curSlot = 0; 
	bool updateStock = false; 
	m5.Lcd.drawPngFile(SD, "/bg/Shop.png", 0, 0);
	m5.Lcd.setTextSize(2);
	M5.Lcd.setTextColor(TFT_BLACK, 0x92A7);
	int curX = 98;
	int curY = 28; 
	
	char priceString[4];
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
			//	curInventory->foodIList[curInventory->numOfFoods + 1] = toAdd; 
				memcpy(&curInventory->foodIList[(curInventory->numOfFoods)], &toAdd, sizeof(toAdd));  
				curInventory->numOfFoods = curInventory->numOfFoods + 1;
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
			clearButtons();
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
	//@TO DO: actually add error to shop when fridge full 
	int textX = 137;
	int textY = 41;
	int curPos = 0; 
	M5.Lcd.setTextColor(BLACK);
	M5.Lcd.setTextSize(2);
	m5.Lcd.drawPngFile(SD, "/bg/inv_choice.png", 0, 0);
	M5.Lcd.drawString(invLocationNames[0], textX, textY);
	while (!btnCPress) {
		M5.update();
		if (btnAPress == true) {
			clearButtons();
			refloor(137, 41, 238, 71, textX, textY, inv_box_tile, 160, 32);
			curPos = curPos + 1;
			if (curPos > 1) {
				curPos = 0;
			}
			M5.Lcd.drawString(invLocationNames[curPos], textX, textY);
		}
		if (btnBPress == true) {
			clearButtons();
			if (strcmp(invLocationNames[curPos], "Food") == 0) {
				clearButtons();
				showFridge(curInventory);
			}
			else if (strcmp(invLocationNames[curPos], "Items") == 0) {
				clearButtons();
				//Show other
			}
		}
	}
	if (btnCPress == true) {
		clearButtons();
		return;
	}
}

void gamePlay::showFridge(Inventory* curInventory) {
	int itemSize = curInventory->numOfFoods;
	foodItem curFoodItem;
	food curFoods;
	int curX = 50;
	int curY = 30;
	int maxSize;
	char fillString[3];
	m5.Lcd.drawPngFile(SD, "/bg/Fridge.png", 0, 0);
	int fridgePage = 0;
	int foodSlot = 0;
	if (itemSize < 10) {
		maxSize = itemSize;
	}
	else {
		maxSize = 10;
	}
	m5.Lcd.setTextSize(1);
	m5.Lcd.drawString("0", 45, 205);
	m5.Lcd.setTextSize(2);
	M5.Lcd.setTextColor(TFT_BLACK, 0x4B8F);
	for (int i = 0; i < maxSize + 1; i++) {
		curFoodItem = curInventory->foodIList[i];
		const char* filePath = curFoodItem.filepath;
		m5.Lcd.drawPngFile(SD, filePath, curX, curY, 40, 40);
		curX = curX + 52;
		if (i == 4) {
			curY = curY + 48;
			curX = 50;
		}
	}
	while (!btnCPress) {
		M5.update();
		m5.Lcd.drawString(curInventory->foodIList[foodSlot].foodName, 80, 120);
		itoa(curInventory->foodIList[foodSlot].fill, fillString, 10);
		if (btnAPress == true) {
			curFoodItem = curInventory->foodIList[foodSlot];
			clearButtons();
			m5.Lcd.drawString("  ", 150, 155);
			m5.Lcd.drawString(fillString, 150, 155);
			if (foodSlot == itemSize - 1) {
				foodSlot = 0;
			}
			else {
				foodSlot = foodSlot + 1;
			}
		}
		if (btnBPress == true) {
			if (curInventory->foodIList[foodSlot].price > 0) {
				clearButtons();
				int curX = 98;
				int curY = 28;
				curInventory->numOfFoods = curInventory->numOfFoods - 1;
				curInventory->foodIList[foodSlot] = curFoods.giveOOS();
				cChar.fullness = cChar.fullness + curInventory->foodIList[foodSlot].fill;
				for (int i = 0; i < FOOD_QTY; i++) {
					const char* filePath = curInventory->foodIList[i].filepath;
					for (int i = 0; i < maxSize + 1; i++) {
						curFoodItem = curInventory->foodIList[i];
						const char* filePath = curFoodItem.filepath;
						if (strcmp(filePath, "/food/OOS.png") == 0) {
							m5.Lcd.drawPngFile(SD, filePath, curX - 5, curY - 5, 40, 40);
						}
						else {
							m5.Lcd.drawPngFile(SD, filePath, curX, curY, 40, 40);
						}
						curX = curX + 52;
						if (i == 4) {
							curY = curY + 48;
							curX = 50;
						}
					}
				}
			}
			else {
				//can't eat what doesn't exist
			}
			if (btnCPress == true) {
				clearButtons();
				return;
			}
		}
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
	//This will do for now, may want more complicated food thingy eventually, esp as we need to use this timer
	//For other times like aging and shop reset n stuff
	cChar.fullness = cChar.fullness - 1; 
	noInterrupts++; 
	saveInter = true; 
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

void gamePlay::saveGameData(Inventory* curInventory) {
	File sfile = SD.open("/save.txt", FILE_WRITE);
	if (SD.exists("/save.txt")) {   // If the file is available, write to it
		Serial.write("WROTE TO FILE \n"); 
		sfile.printf("Nam:%s*", cChar.name);
		sfile.printf("\n Col:%s*", cChar.colour);
		sfile.printf("\n Ful:%d*", cChar.fullness);
		sfile.printf("\n Hap:%d*", cChar.happiness);
		sfile.printf("\n Alv:%d*", cChar.isAlive);
		//Inventory 
		sfile.printf("\n NoF:%d", curInventory->numOfFoods);
		if (curInventory->numOfFoods > 0) {
			sfile.printf("\n Foo:( ");
		}
		for (int i = 0; i < curInventory->numOfFoods; i++) {
			if (i == (curInventory->numOfFoods - 1)) {
				sfile.printf("%d )", curInventory->foodIList[i].fdID);
			}
			else {
				sfile.printf("%d,", curInventory->foodIList[i].fdID);
			}
		}
		sfile.printf(")*");
		sfile.printf("\n Mon:%d*", curInventory->currentMoney);
		sfile.close(); 
	}
	else {
		Serial.write("CANT WRITE TO FILE \n"); 
	}
 }

void gamePlay::loadGameData(Inventory* curInventory) {
	//TO DO:
	//Change "FOO" to "FIL" to prevent it reading food! 
	//Check why "FUL" is registering as food 
	String sFileString;
	char* resStr; 
	food curFoods; 
	File sfile = SD.open("/save.txt", FILE_READ);
	if (SD.exists("/save.txt")) {   // If the file is available, read from it
		sFileString = sfile.readString();
		DUMP(sFileString);
		Serial.write("/n"); 
	}
	else {
		Serial.write("No save found \n");
		return;
	}
	//Name
	resStr = findInFile("Nam:", sFileString);
	DUMP(resStr); 
	if (strlen(resStr) > 0) {
		Serial.printf("Char name is %s \n", resStr); 
		strcpy(cChar.name, resStr);
	}
	//Colour
	resStr = findInFile("Col:", sFileString);
	resStr = ""; 
	if (strlen(resStr) > 0) {
		Serial.printf("Char col is %s \n", resStr);
		strcpy(cChar.colour, resStr);
	}
	//Hunger
	resStr = findInFile("Ful:", sFileString);
	if (strlen(resStr) > 0) {
		Serial.printf("Char full is %s \n", resStr);
		cChar.fullness = atoi(resStr);
	}
	//Happy
	resStr = findInFile("Hap:", sFileString);
	if (strlen(resStr) > 0) {
		Serial.printf("Char hap is %s \n", resStr);
		cChar.happiness = atoi(resStr);
	}
	//Alive??
	resStr = findInFile("Alv:", sFileString);
	if (strlen(resStr) > 0) {
		Serial.printf("Char is alive?  %s \n", resStr);
		cChar.isAlive = atoi(resStr);
	}
	//Food no
	resStr = findInFile("NoF:", sFileString);
	if (strlen(resStr) > 0) {
		Serial.printf("Food qty is %s \n", resStr);
		curInventory->numOfFoods = atoi(resStr); 
	}
	//Foods
	//Split strings on the delemter, and add them into an array of numbers. Then read the array. If the next item is not space, append it to a temp string.
	//If the next item is space, then that's all the numbers in that ID and a food is generated based off of that ID, and added to the current slot
	//of the food array 
	resStr = findInFile("Fli:", sFileString);
	char allNumbers[200];
	char delim[] = ",";
	int curSlot = 0; 
	if (strlen(resStr) > 0) {
			removeChar(resStr, 0);
			removeChar(resStr, (strlen(resStr)-1));
			Serial.write("REMOVED BRACKETS \n");
			DUMP(resStr); 
			strcpy(allNumbers, resStr);
			char* ptr = strtok(allNumbers, delim);
			while (ptr != NULL) {
				if (strlen(ptr) > 0) {
					ptr = strtok(NULL, delim);
					DUMP(ptr);
					if (ptr == NULL) {
						break;
					}
					int fdID = atoi(ptr);
					Serial.write("Genning food \n");
					curInventory->foodIList[curSlot] = curFoods.genFoods(0, fdID);
					curSlot++;
				}
			}
		}
	}

void gamePlay::removeChar(char* str, unsigned int index) {
	char* src;
	for (src = str + index; *src != '\0'; *src = *(src + 1), ++src);
	*src = '\0';
}


char* gamePlay::findInFile(String toFind, String fString) {
	// If string not empty Find where the required string starts For all chars in string If the cur char is not *
	// Add it to temp string, increment strI so next valid char goes in next slot 
	char tempStr[50] = "";
	char* ch = new char[50];
	/*String tempStr;*/
	/*int strI = 0;*/

	if (!fString.isEmpty()) {				
		int i = fString.indexOf(toFind);	
		i = i + 4;
		Serial.printf("Found index of %s at %d", toFind, i);
		if (i > -1)
		{
			for (i; i < fString.length(); i++) 
			{
				if (fString[i] != '*') {			
					char c = fString.charAt(i);
					strncat(tempStr, &c, 1);
				}
				else {
					break;
				}
			}
		}
	}
	strcpy(ch, tempStr);
	DUMP(ch);
	return ch;
}
