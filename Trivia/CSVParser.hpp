/*
*	File:		CSVParser.hpp
*	Purpose:	Generic functions for parsing CSV
*	Author:		Jasmine Al Massri
*	Date:		Dec 21 2024
*/

#pragma once

#include <sstream>
#include <fstream>
#include "Utility.hpp"


/*
\ fn:		void get_valid_input(std::istream& is, T& input_var, std::string prompt, char delimiter)
\ brief:	Gets valid input from user - re-prompts if user input is incompatible with input variable
\ param:	std::istream& is, T& input_var, std::string prompt, char delimiter
*/
template<typename T>
void get_valid_input(std::istream& is, T& input_var, std::string prompt, char delimiter = '\n') {
	std::cout << prompt;
	is >> input_var;

	while (!is) {
		std::cout << "Invalid input. Please try again." << std::endl;
		is.clear();
		is.ignore(std::numeric_limits<std::streamsize>::max(), delimiter);
	}

	// return stream to good state, flush buffer
	is.clear();
	is.ignore(std::numeric_limits<std::streamsize>::max(), delimiter);
}




