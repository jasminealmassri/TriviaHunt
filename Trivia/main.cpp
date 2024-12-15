#include <iostream>

#include "Trivia.hpp"
#include "Utility.hpp"
#include "CSVParser.hpp"

using namespace std;

int main() {
	
	display_header();
	display_instructions();
	// display menu


	vector<MC> questions;

	// Parsing questions
	load_questions(questions);
	
	// Process questions
	ask_questions(questions);
	
}