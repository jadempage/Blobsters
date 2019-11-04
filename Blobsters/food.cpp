// 
// Data from https://arduinojson.org/v6/assistant/
const size_t capacity = JSON_ARRAY_SIZE(19) + JSON_OBJECT_SIZE(1) + 19 * JSON_OBJECT_SIZE(7) + 2190;
DynamicJsonDocument doc(capacity);
const int foodItems = 19; 

#include "food.h"
#include "gameplay.h"


void food::genFoods(int amount) {
	food curFoods; 
	File f = SD.open("foodlist.json", FILE_READ);
	const char* json = f.read(); 
	deserializeJson(doc, json);
	JsonArray items = doc["items"];
	for (int i = 0; i < amount; i++) {
		int rando = (rand() % 19) + 1;
		foodItem thisItem; 
		JsonObject jsonItem = items[rando];
		thisItem.description = jsonItem["description"];
		thisItem.filepath = jsonItem["filepath"];
		thisItem.fill = jsonItem["fill"];
		thisItem.healthy = jsonItem["healthy"];
		thisItem.name = jsonItem["name"];
		thisItem.price = jsonItem["price"];
		foodList[i] = &thisItem;
	}

}