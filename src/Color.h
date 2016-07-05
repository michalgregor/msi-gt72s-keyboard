#ifndef COLOR_H
#define COLOR_H

#include <string>
#include <map>

class Color {
public:
	//! The map mapping color names to Color objects.
	static std::map<std::string, Color> NamedColors;

public:
	//! red
	unsigned char r;
	//! green
	unsigned char g;
	//! blue
	unsigned char b;

public:
	//! Constructs the color from a string -- either a predefined named color,
	//! or a hexadecimal RGB string prefixed.
	void fromStr(const std::string& color);

	//! Converts the color to a hexadecimal RGB string.
	std::string toHexStr();

public:
	Color(char r, char g, char b);
	//! Uses fromStr to construct the Color from string.
	Color(const std::string& color);
};

#endif // COLOR_H
