// 
// 
// 

#include "minigameHelper.h"
#include "gameplay.h"

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


//void game_Pong::drawField(int &score1, int &score2, int &paddlePositionPlayer, int &paddlePositionAI, TFT_eSPI &display, bool ppMoveDown, bool ppMoveUp) {
//	if (ppMoveDown) {
//		Serial.write("PP MOVE DOWN"); 
//		display.fillRect(0, round(paddlePositionPlayer) + 10, 5, 10, BLACK);
//		display.fillRect(0, round(paddlePositionPlayer) - 10, 5, 10, WHITE);
//	}
//	//display.fillRect(0, round(paddlePositionPlayer), 5, 100, WHITE);
//	//display.fillRect(310, round(paddlePositionAI), 5, 100, WHITE);
//
//	display.setTextSize(1); 
//	display.setTextColor(WHITE);
//	display.setCursor(55, 0);
//	display.print(score1);
//	display.print(":");
//	display.print(score2);
//
//	display.fillRect(180, 12, 1, 10, WHITE);
//	display.fillRect(180, 32, 1, 10, WHITE);
//	display.fillRect(180, 52, 1, 10, WHITE);
//	display.fillRect(180, 72, 1, 10, WHITE);
//	display.fillRect(180, 82, 1, 10, WHITE);
//	display.fillRect(180, 102, 1, 10, WHITE);
//	display.fillRect(180, 122, 1, 10, WHITE);
//	display.fillRect(180, 142, 1, 10, WHITE);
//	display.fillRect(180, 162, 1, 10, WHITE);
//	display.fillRect(180, 182, 1, 10, WHITE);
//	display.fillRect(180, 202, 1, 10, WHITE);
//	display.fillRect(180, 222, 1, 10, WHITE);
//	display.fillRect(180, 242, 1, 10, WHITE);
//	display.fillRect(180, 182, 1, 10, WHITE);
//}
//
//void game_Pong::collisionControl(int &ballY, int &ballSpeedY, int &ballX, int &ballSpeedX, int &scorePlayer, int &scoreAI, int &paddlePositionPlayer, int &paddlePositionAI) {
//	int screenW = 360;
//	int screenH = 240;
//	//bounce from top and bottom
//	if (ballY >= screenH - 2 || ballY <= 0) {
//		ballSpeedY *= -1;
//	}
//
//	//score points if ball hits wall behind player
//	if (ballX >= screenW - 2 || ballX <= 0) {
//		if (ballSpeedX > 0) {
//			scorePlayer++;
//			ballX = screenW / 4;
//		}
//		if (ballSpeedX < 0) {
//			scoreAI++;
//			ballX = screenW / 4 * 3;
//		}
//		//if (scorePlayer == 2 || scoreAI == 2) {
//		//	//Fin
//		//}
//	}
//
//	//bounce from player1
//	if (ballX >= 0 && ballX <= 2 && ballSpeedX < 0) {
//		if (ballY > round(paddlePositionPlayer) - 2 && ballY < round(paddlePositionPlayer) + 18) {
//			ballSpeedX *= -1;
//		}
//	}
//	//bounce from player2
//	if (ballX >= screenW - 2 - 2 && ballX <= screenW - 2 && ballSpeedX > 0) {
//		if (ballY > round(paddlePositionAI) - 2 && ballY < round(paddlePositionAI) + 18) {
//			ballSpeedX *= -1;
//		}
//
//	}
//}
//
//void game_Pong::drawBall(TFT_eSPI &display, int &ballX, int &ballY, int &ballSpeedX, int &ballSpeedY, bool clear) {
//
//	if (clear == false) {
//		display.fillRect(ballX, ballY, 5, 5, WHITE);
//
//		ballX += ballSpeedX;
//		ballY += ballSpeedY;
//	}
//	else {
//		display.fillRect(ballX, ballY, 5, 5, BLACK);
//	}
//
//}
