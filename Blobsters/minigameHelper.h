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

struct ball {
	int x, y;
	int w, h;
	int dx, dy;
};

struct paddle {
	int x, y;
	int w, h;
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
