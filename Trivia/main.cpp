#include <iostream>

#include "Trivia.hpp"
#include "Utility.hpp"
#include "CSVParser.hpp"

using namespace std;

int main() {
	display_header();
	vector<MC> questions;

	//vector<string> responses = { "True", "False", "Maybe" };
	//questions.push_back(MC("True or false? ", responses, 0));

	// Parsing questions
	load_questions(questions);
	
	// Process questions
	ask_questions(questions);
	
}