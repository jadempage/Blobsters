// 
// Data from https://arduinojson.org/v6/assistant/
 
#include "food.h"
#include "gameplay.h"

const int foodItems = 19; 
foodItem food::genFoods(){
	food curFoods; 
	foodItem thisItem;
		int rando = (rand() % 10) + 1;
    Serial.write("Got random number \n");
    DUMP(rando);
		switch (rando) {
		case 1:
			thisItem.foodName = "Burrito";
			thisItem.filepath = "/food/burrito.png";
			thisItem.price = 100;
			thisItem.fill = 3;
			break;
		case 2:
			thisItem.foodName = "Cheese Burger";
			thisItem.filepath = "/food/burger_cheese.png";
			thisItem.price = 150;
			thisItem.fill = 6;
			break;
		case 3:
			thisItem.foodName = "Cornbread";
			thisItem.filepath = "/food/cornbread.png";
			thisItem.price = 110;
			thisItem.fill = 3;
			break;
		case 4:
			thisItem.foodName = "Double Burger";
			thisItem.filepath = "/food/burger_double.png";
			thisItem.price = 210;
			thisItem.fill = 8;
			break;
		case 5:
			thisItem.foodName = "Donut";
			thisItem.filepath = "/food/donut.png";
			thisItem.price = 65;
			thisItem.fill = 2;
			break;
		case 6:
			thisItem.foodName = "Coffee";
			thisItem.filepath = "/food/drink_coffee.png";
			thisItem.price = 35;
			thisItem.fill = 1;
			break;
		case 7:
			thisItem.foodName = "Chicken Drumstick";
			thisItem.filepath = "/food/drumstick.png";
			thisItem.price = 65;
			thisItem.fill = 2;
			break;
		case 8:
			thisItem.foodName = "Fries";
			thisItem.filepath = "/food/frenchfries.png";
			thisItem.price = 65;
			thisItem.fill = 2;
			break;
		case 9:
			thisItem.foodName = "Chicken Bucket";
			thisItem.filepath = "/food/friedchicken.png";
			thisItem.price = 180;
			thisItem.fill = 7;
			break;
		case 10:
			thisItem.foodName = "Fried Rice";
			thisItem.filepath = "/food/friedrice.png";
			thisItem.price = 125;
			thisItem.fill = 4;
			break;
		}
   Serial.write("Picked item\n");
   DUMP(thisItem.foodName); 
		return thisItem; 
	}
