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

class game_HiLo {
public:
	int roundsPlayed;
	int curWinnings = 0;
	singleCard* generateDeck();
	char* cardRankNames[14] = { "A", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
	bool isHigher(singleCard* card1, singleCard* card2);
	singleCard* removeCard(int index, singleCard* theArr, int cardsLeft);
};
