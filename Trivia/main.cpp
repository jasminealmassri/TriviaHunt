#include <iostream>

#include "Trivia.hpp"
#include "Utility.hpp"
#include "CSVParser.hpp"

using namespace std;

int main() {
	

	// Parsing questions
	vector<MC> questions;
	load_questions(questions);
	shuffle(questions);

	// Parsing hints
	vector<string> hints;
	load_hints(hints);
	shuffle(hints);
	
	int score{};
	// Process questions
	ask_questions(questions, score, hints);
	
}