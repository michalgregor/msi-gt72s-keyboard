#include "Color.h"
#include <exception>
#include <map>
#include <sstream>
#include <iomanip>

std::map<std::string, Color> Color::NamedColors = {
	{"red", Color(255, 0, 0)},
	{"green", Color(0, 255, 0)},
	{"blue", Color(0, 0, 255)},
	{"yellow", Color(255, 255, 0)},
	{"orange", Color(255, 165, 0)},
	{"purple", Color(128, 0, 128)},
	{"pink", Color(255, 192, 203)},
	{"gray", Color(128, 128, 128)},
	{"brown", Color(165, 42, 42)},
	{"black", Color(0, 0, 0)},
	{"white", Color(255, 255, 255)}
};

void Color::fromStr(const std::string& color) {
	// If it is one of the named colors, we can look it up.
	auto iter = NamedColors.find(color);
	if(iter != NamedColors.end()) {
		*this = iter->second;
	} else {
	// Otherwise it a hexadecimal RGB code.
		if(color.size() < 6) throw std::runtime_error("Invalid color '" + color + "'.");

		bool ok = true;
		char* end = nullptr;
		char red, green, blue;
		std::string sub;
		
		sub = color.substr(0, 2);
		red = std::strtol(sub.c_str(), &end, 16);
		if((end - sub.c_str()) != sub.size()) ok = false;

		sub = color.substr(2, 2);
		green = std::strtol(sub.c_str(), &end, 16);
		if((end - sub.c_str()) != sub.size()) ok = false;

		sub = color.substr(4, 2);
		blue = std::strtol(sub.c_str(), &end, 16);
		if((end - sub.c_str()) != sub.size()) ok = false;

		if(ok) {
			r = red;
			g = green;
			b = blue;
		} else {
			throw std::runtime_error("Invalid color '" + color + "'.");
		}
	}	
}

std::string Color::toHexStr() {
	std::stringstream hexStream;
	hexStream << "#" << std::hex;
	hexStream.fill('0');
	hexStream << std::setw(2) << (short) r
	<< std::setw(2) << (short) g
	<< std::setw(2) << (short) b;
	return hexStream.str();
}

Color::Color(char r_, char g_, char b_):
	r(r_), g(g_), b(b_) {}

Color::Color(const std::string& color):
	r(0), g(0), b(0) 
{
	fromStr(color);
}
