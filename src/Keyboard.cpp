#include "Keyboard.h"
#include <string>
#include <stdexcept>

std::map<std::string, char> RegionNames = {
	{"left", 1},
	{"middle", 2},
	{"center", 2},
	{"centre", 2},
	{"right", 3},
	{"logo", 4},
	{"frontleft", 5},
	{"frontright", 6},
	{"touchpad", 7}
};

char parseRegion(const std::string& region) {
	// we first try converting to a number
	char* end = nullptr;
	char ret = std::strtol(region.c_str(), &end, 10);
	if(region.size() == (end - region.c_str())) return ret;

	// we then try to look up the name
	auto iter = RegionNames.find(region);
	if(iter != RegionNames.end()) {
		return iter->second;
	} else {
		throw std::runtime_error("Invalid region name '" + region + "'.");
	}
}

std::map<std::string, char> ModeNames = {
	{"normal", 1},
	{"gaming", 2},
	{"breathe", 3},
	{"demo", 4},
	{"wave", 5}
};

char parseMode(const std::string& mode) {
	// we first try converting to a number
	char* end = nullptr;
	char ret = std::strtol(mode.c_str(), &end, 10);
	if(mode.size() == (end - mode.c_str())) return ret;

	// we then try to look up the name
	auto iter = ModeNames.find(mode);
	if(iter != ModeNames.end()) {
		return iter->second;
	} else {
		throw std::runtime_error("Invalid region name '" + mode + "'.");
	}
}

void Keyboard::sendModeMsg(char mode) {
	size_t BUFSIZE = 8;
	unsigned char buf[8];

	buf[0] = 1;
	buf[1] = 2;
	buf[2] = 65;
	buf[3] = mode;
	buf[4] = 0;
	buf[5] = 0;
	buf[6] = 0;
	buf[7] = 255;

	hid_send_feature_report(_dev, buf, BUFSIZE);
}

void Keyboard::sendColorMsg(Color color) {
	size_t BUFSIZE = 8;
	unsigned char buf[8];

	buf[0] = 1;
	buf[1] = 2;
	buf[2] = 64;
	buf[3] = 0;
	buf[4] = color.r;
	buf[5] = color.g;
	buf[6] = color.b;
	buf[7] = 255;

	for(unsigned int region = 1; region <= 7; region++) {
		buf[3] = region;
		hid_send_feature_report(_dev, buf, BUFSIZE);
	}
}

void Keyboard::sendColorMsg(char region, Color color) {
	size_t BUFSIZE = 8;
	unsigned char buf[8];

	buf[0] = 1;
	buf[1] = 2;
	buf[2] = 64;
	buf[3] = region;
	buf[4] = color.r;
	buf[5] = color.g;
	buf[6] = color.b;
	buf[7] = 255;

	hid_send_feature_report(_dev, buf, BUFSIZE);
}

Keyboard::Keyboard() {
	_dev = hid_open(0x1770, 0xff00, 0);
	if(!_dev) throw std::runtime_error("Cannot connect to the keyboard.");
}

Keyboard::~Keyboard() {
	hid_close(_dev);
}
