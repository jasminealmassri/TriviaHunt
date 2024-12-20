#include <iostream>
#include <queue>

#include "Trivia.hpp"
#include "Utility.hpp"
#include "CSVParser.hpp"

using namespace std;

#define TESTING

int main() {
	

	const string questions_filepath("../Trivia.csv");
	const string clues_filepath("../Clues.csv");

	const string savepoint_questions_filepath("../TriviaSavepoint.csv");
	const string clues_filepath("../CluesSavepoint.csv");

#ifdef TESTING
#else
	program_introduction();
#endif

	 // get name
	std::string name;
	get_name(name);
	cls();

	// Parsing trivia questions
	vector<MC> questions;
	load_questions(questions, questions_filepath);
	shuffle(questions);

	// Parsing clues
	queue<string> clues;
	load_clues(clues, clues_filepath);
	
	// Process questions
	int score{};
	ask_questions(questions, score, clues);

	display_victory(name);
	
}