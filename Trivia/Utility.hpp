#pragma once

#include <iostream>


enum ConsoleColours {
	Black = 30
	, Red
	, Green
	, Yellow
	, Blue
	, Magenta
	, Cyan
	, White
	, BrightBlack = 90
	, BrightRed
	, BrightGreen
	, BrightYellow
	, BrightBlue
	, BrightMagenta
	, BrightCyan
	, BrightWhite
};

inline void output_colour(int color) {
	std::cout << "\33[" << color << "m";
}

