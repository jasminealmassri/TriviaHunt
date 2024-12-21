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

	// File paths 
	std::string rootpath = "../Files";

	state.questions_filepath =	rootpath + "/Questions.csv";
	state.clues_filepath =		rootpath + "/Clues.csv";

	state.questions_save_path = rootpath + "/QuestionsSave.csv";
	state.clues_save_path =		rootpath + "/CluesSave.csv";
	state.state_save_path =		rootpath + "/StateSave.csv";

	bool continue_from_savepoint{};

	// If save files exist, ask if user wants to continue from save and handle choice
	if (std::filesystem::exists(state.questions_save_path)) {

		continue_from_savepoint = continue_from_save();

		if (continue_from_savepoint) {
			state.load_state();
			state.questions_filepath = state.questions_save_path;
			state.clues_filepath = state.clues_save_path;
		}
	}
	cls();

	// get name
	if (!continue_from_savepoint) {
#ifdef TESTING
#else
		program_introduction();
#endif
		get_name(state.player_name);
	}
	cls();

	// Load questions and clues
	state.load_questions();
	state.shuffle_questions();
	state.load_clues();
	
	// Set initial numbers for max score and clues
	if (!continue_from_savepoint) {
		state.max_score = state.questions.size() * state.PTS_PER_Q;
		state.max_clues = state.clues.size();
	}

	// Process questions
	ask_questions(state);

	// Game finished, save no longer needed
	state.remove_save_files();

	// Victory
	display_victory(state.player_name);
	
}