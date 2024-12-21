/*
*	File:		Utility.hpp
*	Purpose:	General purpose functions 
*	Author:		Jasmine Al Massri
*	Date:		Dec 21 2024
*/

#pragma once

#include <iostream>
#include <algorithm>
#include <random>
#include <thread>


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

template<typename T>
void shuffle(T& v) {
	std::random_device rd;
	std::mt19937 rng(rd());
	std::shuffle(v.begin(), v.end(), rng);
}

inline void output_colour(int color) {
	std::cout << "\33[" << color << "m";
}

inline void cls() {
	std::cout << "\033[2J\033[H";
}

inline void wait(int milliseconds) {
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

inline void print_slow(std::string string, int milliseconds = 40) {
	for (char c : string) {
		std::cout << c;
		wait(milliseconds);
	}
}
