#include <iostream>
#include <queue>

#include "Trivia.hpp"
#include "Utility.hpp"
#include "CSVParser.hpp"

using namespace std;

int main() {
	

	const string questions_filepath("../Trivia.csv");
	const string clues_filepath("../Clues.csv");

	program_introduction();

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
	
	int score{};
	// Process questions
	ask_questions(questions, score, clues);

	display_victory(name);
	
}