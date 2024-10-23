#include <iostream>

#include "Trivia.hpp"

void display_header() {
	std::cout << "Welcome to Trivia Hunt!\n";
	std::cout << "***********************\n\n";
}


void MC::display() {

	char c = 'A';

	for (int i = 0; i < responses_.size(); i++) {
		std::cout << c++ << ". " << responses_[i] << std::endl;
	}
}