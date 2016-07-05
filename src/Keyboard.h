#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <map>
#include <hidapi/hidapi.h>
#include "Color.h"

extern std::map<std::string, char> RegionNames;
extern std::map<std::string, char> ModeNames;

char parseRegion(const std::string& region);
char parseMode(const std::string& mode);

class Keyboard {
private:
	hid_device* _dev = nullptr;

public:
	//! Sends a mode setting message to the keyboard.
	void sendModeMsg(char mode);

	//! Sends a color setting message to the keyboard, coloring all regions
	//! (1-7) using the specified color.
	void sendColorMsg(Color color);

	//! Sends a color setting message to the keyboard, coloring the specified
	//! region using the specified color.
	void sendColorMsg(char region, Color color);

public:
	Keyboard();
	~Keyboard();
};

#endif // KEYBOARD_H
