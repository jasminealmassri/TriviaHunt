#include <iostream>

#include "Trivia.hpp"

void MC::display() {

	char c = 'A';

	for (int i = 0; i < responses_.size(); i++) {
		std::cout << c++ << ". " << responses_[i] << std::endl;
	}
}