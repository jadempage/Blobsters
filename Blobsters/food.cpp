// 
// Data from https://arduinojson.org/v6/assistant/
 
#include "food.h"
#include "gameplay.h"


//Pad each item upto 13 to fill the box completely
//@ Todo make a less hacky way than padding with spaces 
const int foodItems = 19; 
foodItem food::genFoods(int isRand, int fID){
	food curFoods;   
	foodItem thisItem;
	int retID; 
	if (isRand == 1) {
		retID = (rand() % 10) + 1;
	}
	else {
		retID = fID;
	}
    //Serial.write("Got random number \n");
    //DUMP(rando);
		switch (retID) {
		case 1:
			thisItem.foodName = "Burrito      ";
			thisItem.filepath = "/food/burrito.png";
			thisItem.price = 100;
			thisItem.fill = 3;
			thisItem.fdID = 0; 
			break;
		case 2:
			thisItem.foodName = "Cheese Burger";
			thisItem.filepath = "/food/burger_cheese.png";
			thisItem.price = 150;
			thisItem.fill = 6;
			thisItem.fdID = 1;
			break;
		case 3:
			thisItem.foodName = "Cornbread    ";
			thisItem.filepath = "/food/cornbread.png";
			thisItem.price = 110;
			thisItem.fill = 3;
			thisItem.fdID = 2;
			break;
		case 4:
			thisItem.foodName = "Double Burger";
			thisItem.filepath = "/food/burger_double.png";
			thisItem.price = 210;
			thisItem.fill = 8;
			thisItem.fdID = 3;
			break;
		case 5:
			thisItem.foodName = "Donut        ";
			thisItem.filepath = "/food/donut.png";
			thisItem.price = 65;
			thisItem.fill = 2;
			thisItem.fdID = 4;
			break;
		case 6:
			thisItem.foodName = "Coffee       ";
			thisItem.filepath = "/food/drink_coffee.png";
			thisItem.price = 35;
			thisItem.fill = 1;
			thisItem.fdID = 5;
			break;
		case 7:
			thisItem.foodName = "Chicken Drum ";
			thisItem.filepath = "/food/drumstick.png";
			thisItem.price = 65;
			thisItem.fill = 2;
			thisItem.fdID = 6;
			break;
		case 8:
			thisItem.foodName = "Fries        ";
			thisItem.filepath = "/food/frenchfries.png";
			thisItem.price = 65;
			thisItem.fill = 2;
			thisItem.fdID = 7;
			break;
		case 9:
			thisItem.foodName = "Chicken Box  ";
			thisItem.filepath = "/food/friedchicken.png";
			thisItem.price = 180;
			thisItem.fill = 7;
			thisItem.fdID = 8;
			break;
		case 10:
			thisItem.foodName = "Fried Rice   ";
			thisItem.filepath = "/food/friedrice.png";
			thisItem.price = 125;
			thisItem.fill = 4;
			thisItem.fdID = 9;
			break;
		}
		return thisItem; 
	}

foodItem food::giveOOS() {
	foodItem thisItem;
	thisItem.description = "Out of stock ";
	 thisItem.filepath = "/food/OOS.png";
	thisItem.foodName = "Out of stock ";
	thisItem.price = 0;
	thisItem.fill = 0; 
	return thisItem; 
}
