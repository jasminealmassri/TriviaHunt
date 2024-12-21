/*
*	File:		main.cpp
*	Purpose:	This is a console game which is a combination of a trivia quiz and a
				treasure hunt. It will ask trivia questions and periodically drop 
				treasure hunt clues based on the number of correct responses given. 
				The user would asnwer questions, receive a hint, use it to search for
				hidden treasure in the surrounding area, come back to answer more questions
				to get more clues.
*	Author:		Jasmine Al Massri
*	Date:		Dec 21 2024
*/

#include <iostream>
#include <queue>
#include <filesystem>

#include <fstream>

#include "Trivia.hpp"
#include "Utility.hpp"
#include "CSVParser.hpp"

using namespace std;

//#define TESTING

int main() {
	
	// This object holds state such as player name, score, clues left 
	// Points per question and clue thresholds can be modified within this object
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
		state.max_score = static_cast<int>(state.questions.size() * state.pts_per_q);
		state.max_clues = static_cast<int>(state.clues.size());
	}

	// Process questions
	ask_questions(state);

	// Game finished, save no longer needed
	state.remove_save_files();

	// Victory
	display_victory(state.player_name);
	
}