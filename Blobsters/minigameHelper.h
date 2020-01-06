// minigameHelper.h
#pragma once 
#ifndef _MINIGAMEHELPER_h
#define _MINIGAMEHELPER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif

#include "gameplay.h"

enum cardSuits {
	csHearts,
	csClubs,
	csSpades,
	csDiamonds
};

enum cardVals {
	cvAce,
	cv2,
	cv3,
	cv4,
	cv5,
	cv6,
	cv7,
	cv8,
	cv9,
	cv10,
	cvJack,
	cvQueen,
	cvKing
};

struct singleCard {
	cardSuits theSuit;
	cardVals theVal;
};

struct coords {
	int x;
	int y;
};

struct ball {
	int x, y;
	int w, h;
	int dx, dy;
};

struct paddle {
	int x, y;
	int w, h;
};

struct rLine {
	int x0, y0, x1, y1; 
};

struct boundingBox {
	rLine rLine1, rLine2, rLine3, rLine4; 
};


class game_HiLo {
public:
	int roundsPlayed;
	int curWinnings = 0;
	std::vector<singleCard> generateVDeck();
	char* cardRankNames[14] = { "A", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
	bool isHigher(singleCard* card1, singleCard* card2);
	singleCard* removeCard(int index, singleCard* theArr, int cardsLeft);
};

class game_Pong {
public:
	int check_collision(ball a, paddle b);
};

class game_Treasure {
public:
	int lines_intersect(long x1, long y1,   /* First line segment */
		long x2, long y2,
		long x3, long y3,   /* Second line segment */
		long x4, long y4
	);
	boundingBox getBoundingBox(int x, int y);
	bool checkIntersection(int goalX, int goalY, boundingBox box);
	coords * getBombHeadings(int noBombs, int tresX, int tresY);
	bool valueInRange(int value, int min, int max);
	bool rectOverlap(coords A, coords B);
	bool inRange(int low, int high, int x);
};
