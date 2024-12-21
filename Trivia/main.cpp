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

	//const string questions_original_filepath("../Trivia.csv");
	state.clues_filepath = "../Clues.csv";
	state.questions_filepath = "../Trivia.csv";
	state.questions_save_path = "../QuestionsSave.csv";
	state.clues_save_path = "../CluesSave.csv";
	state.state_save_path = "../StateSave.csv";

	//string questions_filepath{ questions_original_filepath};
	//string clues_filepath{ clues_original_filepath };

	bool continue_from_savepoint{};

#ifdef TESTING
#else
	program_introduction();
#endif

	if (std::filesystem::exists(state.questions_save_path)) {

		continue_from_savepoint = continue_from_save();
		
		if (continue_from_savepoint) {
			state.load_state();
			state.questions_filepath = state.questions_save_path;
			state.clues_filepath = state.clues_save_path;
		}
	}

	// get name
	if (!continue_from_savepoint) {
		get_name(state.player_name);
	}
	cls();

	// Parsing trivia questions
	//vector<MC> questions;
	state.load_questions();
	shuffle(state.questions);

	// Parsing clues
	//queue<string> clues;
	state.load_clues();
	
	if (!continue_from_savepoint) {
		state.max_score = state.questions.size() * state.PTS_PER_Q;
		state.max_clues = state.clues.size();
	}
	// Process questions
	ask_questions(state);

	display_victory(state.player_name);
	
}