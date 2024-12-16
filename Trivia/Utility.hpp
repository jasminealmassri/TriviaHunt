#pragma once

#include <iostream>
#include <algorithm>
#include <random>


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

template<typename T>
void shuffle(T& v) {
	std::random_device rd;
	std::mt19937 rng(rd());
	std::shuffle(v.begin(), v.end(), rng);
}
