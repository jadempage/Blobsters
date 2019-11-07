#include "gameplay.h"

void SDUtils::logThis(char* text)
{
	File f = SD.open("/data/log.txt", FILE_APPEND);
	if (!f) {
		return;
		M5.Lcd.println("Can't open file");

	}
	if (f.print(text)) {
		//Continue
		M5.Lcd.println("opened file");
	}
	else {
		M5.Lcd.println("Can't open file");
	}
	f.close();
}

char* SDUtils::readFile(char* filePath)
{
	char* retString; 
	File file = SD.open(filePath);
	static uint8_t buf[5120];
	char * finStr;
	size_t len = 0;
	int i = 0;
	uint32_t start = millis();
	uint32_t end = start;
	if (file) {
		len = file.size();
		size_t flen = len;
		start = millis();
		while (len) {
			size_t toRead = len;
			//if (toRead > 512) {
			//	toRead = 512;
			//}
			/*finStr[i] = file.read();*/
			memcpy(finStr, file.read(), 5120);
			i++; 
			file.read(buf, toRead);
			len -= toRead;
		}
		end = millis() - start;
		//Serial.printf("%u bytes read for %u ms\n", flen, end);
		file.close();
	}
	else {
		M5.Lcd.println("Can't open file");
		SDUtils::logThis("Can't open file! \n");
		return nullptr; 
	}
	memcpy(retString, buf, 5120);
	SDUtils::logThis("Read file result: \n");
	SDUtils::logThis(retString); 
	return finStr;
}
