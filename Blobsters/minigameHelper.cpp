// 
// 
// 

#include "minigameHelper.h"

singleCard* game_HiLo::generateDeck() {
	static singleCard thisDeck[52];
	int deckCount = 0; 
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			singleCard thisCard; 
			thisCard.theSuit = cardSuits(i);
			thisCard.theVal = cardVals(j);
			//memcpy(&thisDeck[deckCount], &thisCard, sizeof(thisCard));
			thisDeck[deckCount] = thisCard;
			deckCount++;
			//DUMP(deckCount);
		}
	}
	return thisDeck; 
}

bool game_HiLo::isHigher(singleCard* cardNow, singleCard* cardNext) {
	int val1 = 0;
	int val2 = 0;

	switch (cardNow->theVal) {
	case cvJack: val1 = 11; break;
	case cvQueen: val1 = 12; break;
	case cvKing: val1 = 13; break;
	case cvAce: val1 = 100; break;
	default: val1 = cardNow->theVal + 1; break;
	}
	switch (cardNext->theVal) {
	case cvJack: val2 = 11; break;
	case cvQueen: val2 = 12; break;
	case cvKing: val2 = 13; break;
	case cvAce: val2 = 100; break;
	default: val2 = cardNext->theVal + 1; break;
	}

	DUMP(val1);
	DUMP(val2);

	if (val1 == 100) {
		return true;
	}
	else if (val2 == 100) {
		return true;
	}
	else if (val2 > val1) {
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
