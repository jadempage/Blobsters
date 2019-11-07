#pragma once

#ifndef _LOG_h
#define _LOG_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif

class SDUtils {
public:
	void logThis(char* text); 
	char* readFile(char* filePath); 
};
