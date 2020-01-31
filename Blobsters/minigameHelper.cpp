// 
// 
// 

#include "minigameHelper.h"
#include "gameplay.h"

#define SAME_SIGNS( a, b )	\
		(((long) ((unsigned long) a ^ (unsigned long) b)) >= 0 )

#define SCREEN_WIDTH 320	//window height
#define SCREEN_HEIGHT 240	//window width

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

int game_Treasure::lines_intersect(/* First line segment */  long x1, long y1, long x2, long y2, /* Second line segment */ long x3, long y3, long x4, long y4)
//AUTHOR: Mukesh Prasad
	{
	long a1, a2, b1, b2, c1, c2; /* Coefficients of line eqns. */
	long r1, r2, r3, r4;         /* 'Sign' values */
	long denom, offset, num;     /* Intermediate values */

	/* Compute a1, b1, c1, where line joining points 1 and 2
	 * is "a1 x  +  b1 y  +  c1  =  0".
	 */
	int toRet = 0; 
	long x = 0;
	long y = 0; 
	a1 = y2 - y1;
	b1 = x1 - x2;
	c1 = x2 * y1 - x1 * y2;

	/* Compute r3 and r4.
	 */


	r3 = a1 * x3 + b1 * y3 + c1;
	r4 = a1 * x4 + b1 * y4 + c1;

	/* Check signs of r3 and r4.  If both point 3 and point 4 lie on
	 * same side of line 1, the line segments do not intersect.
	 */

	if (r3 != 0 &&
		r4 != 0 &&
		SAME_SIGNS(r3, r4)) {
		Serial.println("RET AT 1");
		return (0);
	}

	
	/* Compute a2, b2, c2 */

	a2 = y4 - y3;
	b2 = x3 - x4;
	c2 = x4 * y3 - x3 * y4;

	/* Compute r1 and r2 */

	r1 = a2 * x1 + b2 * y1 + c2;
	r2 = a2 * x2 + b2 * y2 + c2;

	/* Check signs of r1 and r2.  If both point 1 and point 2 lie
	 * on same side of second line segment, the line segments do
	 * not intersect.
	 */

	if (r1 != 0 &&
		r2 != 0 &&
		SAME_SIGNS(r1, r2)) {
		Serial.println("RET AT 2");
		return (0);
	}


	/* Line segments intersect: compute intersection point.
	 */

	denom = a1 * b2 - a2 * b1;
	if (denom == 0){
		Serial.println("RET AT 3");
		return (0); }
	offset = denom < 0 ? -denom / 2 : denom / 2;

	/* The denom/2 is to get rounding instead of truncating.  It
	 * is added or subtracted to the numerator, depending upon the
	 * sign of the numerator.
	 */

	num = b1 * c2 - b2 * c1;
	x = (num < 0 ? num - offset : num + offset) / denom;

	num = a2 * c1 - a1 * c2;
	y = (num < 0 ? num - offset : num + offset) / denom;

	if (!y > 0) {
		Serial.printf(" NO Y ");
		return 0;
	}
	if (!x > 0) {
		Serial.printf(" NO X ");
		return 0; 
	}
	DUMP(y);
	DUMP(x); 
	Serial.printf(" X INTER %d", x); 
	Serial.printf(" Y INTER %d", y);

	return (1);
} /* lines_intersect */

boundingBox game_Treasure::getBoundingBox(int x, int y)
{
	boundingBox theBox;
	rLine line1;
	rLine line2;
	rLine line3;
	rLine line4;
	line1.x0 = x;
	line1.x1 = x + 20;
	line1.y0 = y;
	line1.y1 = y;
	line2.x0 = x + 20;
	line2.x1 = x + 20;
	line2.y0 = y;
	line2.y1 = y + 20;
	line3.x0 = x + 20;
	line3.x1 = x;
	line3.y1 = x + 20;
	line3.y0 = x + 20;
	line4.x0 = x;
	line4.x1 = x;
	line4.y0 = y + 20;
	line4.y1 = y;

	theBox.rLine1 = line1;
	theBox.rLine2 = line2;
	theBox.rLine3 = line3;
	theBox.rLine4 = line4; 
	return theBox;
}

bool game_Treasure::checkIntersection(int goalX, int goalY, boundingBox box)
{
	bool isInter = false;

	if ((lines_intersect(goalX, goalY, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, box.rLine1.x0, box.rLine1.y0, box.rLine1.x1, box.rLine1.y1)) == 1) {
		isInter = true;
	}
	if ((lines_intersect(goalX, goalY, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, box.rLine2.x0, box.rLine2.y0, box.rLine2.x1, box.rLine2.y1)) == 1) {
		isInter = true;
	}
	if ((lines_intersect(goalX, goalY, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, box.rLine3.x0, box.rLine3.y0, box.rLine3.x1, box.rLine3.y1)) == 1) {
		isInter = true;
	}
	if ((lines_intersect(goalX, goalY, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, box.rLine4.x0, box.rLine4.y0, box.rLine4.x1, box.rLine4.y1)) == 1) {
		isInter = true;
	}

	return isInter;
}

coords game_Treasure::getBomb(int tresX, int tresY) {
	bool coordsOk = false;
	coords curBomb;
	coords curTreasure;
	coords curCompBomb;
	int width = 20;
	int height = 20;
	int radius = 100;
	int curX;
	int curY;
	curTreasure.x = tresX;
	curTreasure.y = tresY;
	while (!coordsOk) {
		curX = (rand() % 100) + 1;// +radius;
		curY = (rand() % 100) + 1;// +radius;
		curBomb.x = curX + radius;
		curBomb.y = curY + radius;
		if (!rectOverlap(curTreasure, curBomb)) {
			coordsOk = true;
			for (int i = 0; i < internalBombs.size(); i++) {
				curCompBomb.x = internalBombs[i].x;
				Serial.printf("Getting overlap for bomb %d \n", i);
				curCompBomb.y = internalBombs[i].y;
				if (rectOverlap(curBomb, curCompBomb)) {
					coordsOk = false;
				}
			}
		}
		if (coordsOk) {
			internalBombs.push_back(curBomb); 
			Serial.printf("Generated %d bomb at %d , %d \n", internalBombs.size(), curBomb.x, curBomb.y);
		}
	}
}

std::vector<coords> game_Treasure::getBombHeadings(int noBombs, int tresX, int tresY)
{
	coords printBomb;
	internalBombs.clear();
	internalBombs.reserve(5);
	for (int i = 0; i < noBombs; i++) {
		printBomb = getBomb(tresX, tresY);
		Serial.printf("printBomb %d bomb at %d , %d \n", i, printBomb.x, printBomb.y);
	}
	for (int i = 0; i < internalBombs.size(); i++) {
		Serial.write("Bomb cycle \n"); 
	}
	return internalBombs;
}

//bool game_Treasure::inRange(int low, int high, int x)
//{
//	return ((x - high) * (x - low) <= 0);
//}

bool game_Treasure::valueInRange(int value, int min, int max)
{
	return (value >= min) && (value <= max);
}

bool game_Treasure::rectOverlap(coords A, coords B)
{
	int width = 20;
	int height = 20; 
	bool xOverlap = valueInRange(A.x, B.x, B.x + width) ||
		valueInRange(B.x, A.x, A.x + width);

	bool yOverlap = valueInRange(A.y, B.y, B.y + height) ||
		valueInRange(B.y, A.y, A.y + height);

	DUMP(xOverlap);
	DUMP(yOverlap); 
	return xOverlap && yOverlap;
}

apple game_Fruit::generateApple()
{
	//Generate random Y between 0 and YMAX
	//Decide if golden (1/10 chance)
	int goldChance = (rand() % 10) + 1;
	int yPos = (rand() % SCREEN_WIDTH) + 1;
	apple newApple;
	if (goldChance == 1) {
		newApple.isGold = true;
	}
	else {
		newApple.isGold = false;
	}
	newApple.y = yPos;
	newApple.x = 0; 
	newApple.onScreen = true;
	return newApple;
}
