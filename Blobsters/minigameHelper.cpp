// 
// 
// 

#include "minigameHelper.h"

std::vector<singleCard> game_HiLo::generateVDeck() {
	static std::vector<singleCard> newDeck;
	int deckCount = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			singleCard thisCard;
			thisCard.theSuit = cardSuits(i);
			thisCard.theVal = cardVals(j);
			//memcpy(&thisDeck[deckCount], &thisCard, sizeof(thisCard));
			newDeck.push_back(thisCard);
			deckCount++;
			//DUMP(deckCount);
		}
	}
	return newDeck;
}

bool game_HiLo::isHigher(singleCard* cardNow, singleCard* cardNext) {
	int val1 = 0;
	int val2 = 0;

	if (cardNow->theVal == cvAce) {
		return true;
	}
	if (cardNext->theVal == cvAce) {
		return true;
	}

	switch (cardNow->theVal) {
	case cvJack: val1 = 11; break;
	case cvQueen: val1 = 12; break;
	case cvKing: val1 = 13; break;
	default: val1 = cardNow->theVal + 1; break;
	}
	switch (cardNext->theVal) {
	case cvJack: val2 = 11; break;
	case cvQueen: val2 = 12; break;
	case cvKing: val2 = 13; break;
	default: val2 = cardNext->theVal + 1; break;
	}

	DUMP(val1);
	DUMP(val2);

	if (val2 > val1) {
		return  true;
	}
	else {
		return false;
	}
}

singleCard* game_HiLo::removeCard(int index, singleCard* theArr, int cardsLeft) {
	for (int i = index; i <= cardsLeft - 1; i++)
	{
		theArr[i] = theArr[i + 1];
	}
	theArr[cardsLeft - 1] = {};
	return theArr; 
}

int game_Pong::check_collision(ball a, paddle b)
{
	//Adapted from https://github.com/flightcrank/pong/blob/master/pong.c
	int left_a, left_b;
	int right_a, right_b;
	int top_a, top_b;
	int bottom_a, bottom_b;

	left_a = a.x;
	right_a = a.x + a.w;
	top_a = a.y;
	bottom_a = a.y + a.h;

	left_b = b.x;
	right_b = b.x + b.w;
	top_b = b.y;
	bottom_b = b.y + b.h;


	if (left_a > right_b) {
		return 0;
	}

	if (right_a < left_b) {
		return 0;
	}

	if (top_a > bottom_b) {
		return 0;
	}

	if (bottom_a < top_b) {
		return 0;
	}

	return 1;
}
