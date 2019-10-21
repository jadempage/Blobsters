  // 
// 
// 

#include "gameplay.h"
#include "sprites.h"

#define ZERO 1e-10
#define isBetween(A, B, C) ( ((A-B) > - ZERO) && ((A-C) < ZERO) )


void gamePlay::idleLoop()
{
	m_shouldContinue = true;
	int16_t charWidth = 64;
	int16_t charHeight = 64;
	int screensizex = 320;
	int screensizey = 240;
	int16_t xPosMod = 200;
	int16_t yPosMod = 180;
	void* frameBuffer(int16_t f);
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
		delay(2000);
		refloor(xPosMod, yPosMod);
	}
}

template <typename T>
bool IsInBounds(const T& value, const T& low, const T& high) {
	return !(value < low) && !(high < value);
}

void gamePlay::refloor(int xPosMod, int yPosMod) {
	for (int x = 0; x < 320; x = x + 16) {
		for (int y = 175; y < 260; y = y + 16) {
			if (IsInBounds(x, xPosMod - 64, xPosMod + 64)) { // Is 5 Between 0 and 10
				m5.Lcd.pushImage(x, y, 16, 16, floor_tile);
			}
			if (IsInBounds(y, yPosMod - 60, yPosMod + 60)) { // Is 5 Between 0 and 10
				m5.Lcd.pushImage(x, y, 16, 16, floor_tile);
			}

		}
	}
}
