#include <iostream>
#include <sstream>
#include <string>
#include "Color.h"
#include "Keyboard.h"

using namespace std::literals::string_literals;

void handleColorOption(const std::string& option, Keyboard& keyboard) {
	auto pos = option.find(",");

	// if there is a separator, we have a region and a color
	if(pos != std::string::npos) {
		char region = parseRegion(option.substr(0, pos));
		Color color = option.substr(pos+1);
		keyboard.sendColorMsg(region, color);
	// if there is no separator, we have only a color
	} else {	
		keyboard.sendColorMsg(option);
	}
}

void handleModeOption(const std::string& option, Keyboard& keyboard) {
	char mode = parseMode(option);
	keyboard.sendModeMsg(mode);
}

void printNamedColors() {
	std::cout << "Named colors:\n";
	for(auto& pair: Color::NamedColors) {
		std::cout << "\t" << pair.first << ":\t\t" << pair.second.toHexStr() << "\n";
	}
}

void printUsage() {
	std::stringstream regionOptions;
	for(auto& pair: RegionNames) {
		regionOptions << pair.first << " (" << (short) pair.second << "), ";
	}

	std::string regionStr = regionOptions.str();
	regionStr.pop_back();
	regionStr.pop_back();

	std::cout << 
R"(Usage:
	-h: Displays this help.
	-c [<region>,]<color>: Sets color for a region (may be used multiple times to set color for multiple regions). If a region is not specified, all regions are colored.
	-m <mode>: Sets the mode (either an integer, or one of )" << regionStr << R"()
	-cl: Lists all predefined named colors.
)";
}

int main(int argc, char* argv[]) {
	if(argc <= 1) {
		printUsage();
		return 1;
	}

	for(int i = 1; i < argc; i++) {
		if(argv[i] == "-h"s) {
			printUsage();
			return 0;
		} else if(argv[i] == "-cl"s) {
			printNamedColors();
			return 0;
		}

		Keyboard keyboard;

		if(argv[i] == "-c"s) {
			if(i + 1 >= argc) {
				std::cerr << "A color specification is expected after -c." << std::endl;
				return 1;
			}

			handleColorOption(argv[++i], keyboard);
		} else if(argv[i] == "-m"s) {
			if(i + 1 >= argc) {
				std::cerr << "A mode specification is expected after -c." << std::endl;
				return 1;
			}

			handleModeOption(argv[++i], keyboard);
		} else {
			// if the argument is not recognized at all
			std::cerr << "Unrecognized argument '" << argv[i] << "'." << std::endl;
			return 1;
		}
	}

	return 0;
}
