#include <iostream>
#include <queue>
#include <filesystem>

#include <fstream>

#include "Trivia.hpp"
#include "Utility.hpp"
#include "CSVParser.hpp"

using namespace std;

#define TESTING

int main() {
	
	GameState state{};

	const string questions_original_filepath("../Trivia.csv");
	const string questions_savepoint_filepath("../TriviaSavepoint.csv");

	const string clues_original_filepath("../Clues.csv");
	const string clues_savepoint_filepath("../CluesSavepoint.csv");
	const string state_savepoint_filepath("../StateSavepoint.csv");

	string questions_filepath{ questions_original_filepath};
	string clues_filepath{ clues_original_filepath };

	bool continue_from_savepoint{};

#ifdef TESTING
#else
	program_introduction();
#endif

	if (std::filesystem::exists(questions_savepoint_filepath)) {
		continue_from_savepoint = continue_savepoint();
		if (continue_from_savepoint) {
			load_state(state_savepoint_filepath, state);
			questions_filepath = questions_savepoint_filepath;
			clues_filepath = clues_savepoint_filepath;
		}
	}

	// get name
	if (!continue_from_savepoint) {
		get_name(state.player_name);
		cls();
	}

	// Parsing trivia questions
	vector<MC> questions;
	load_questions(questions, questions_filepath);
	shuffle(questions);

	// Parsing clues
	queue<string> clues;
	load_clues(clues, clues_filepath);
	
	if (!continue_from_savepoint) {
		state.max_score = questions.size() * state.PTS_PER_Q;
		state.max_clues = clues.size();
	}
	// Process questions
	ask_questions(questions, clues, state, questions_savepoint_filepath, clues_savepoint_filepath, state_savepoint_filepath);

	display_victory(state.player_name);
	
}