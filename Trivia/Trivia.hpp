#pragma once

#include <vector>
#include <string>
#include <queue>
#include <fstream>
#include <filesystem>

#include "Utility.hpp"
#include "CSVParser.hpp"

using Clue_t = std::string;

struct GameState {
	std::string player_name{};
	int current_score{};
	int PTS_PER_Q{ 10 };
	int CLUE_THRESHOLD{ 5 * PTS_PER_Q };
	int max_score{};
	int clues_received{};
	int next_clue_threshold{ CLUE_THRESHOLD };
};
/*
*	class:		MC
*	purpose:	Represents a multiple choice question
*/
class MC {
	std::string question_;
	std::vector<std::string> options_;
	unsigned correct_response_;
public:
	MC(
		  std::string question = ""
		, std::vector<std::string> options = {"True", "False"}
		, unsigned correct_response = 1
	) 
		: question_(question)
		, options_(options)
		, correct_response_(correct_response) 
	{}

	std::string question() const { return question_;  }
	unsigned correct_response() const { return correct_response_; }
	std::vector<std::string> options() const { return options_; }

	void display();

	bool invalid_answer(char answer) {
		return answer < 'A' || answer > 'A' + options_.size() - 1;
	}

	bool operator == (MC const& other) {
		return question_ == other.question_;
	}
};

inline bool continue_savepoint() {
	
	char answer{};

	do {
		get_valid_input(std::cin, answer, "Resume previous progress? (y/n): ");
		answer = toupper(answer);
	} while (answer != 'Y' && answer != 'N');

	return answer == 'Y';
}



inline void display_header() {
	output_colour(ConsoleColours::Yellow);
	print_slow("*****************************************************************************************************************\n\n", 5);
	output_colour(ConsoleColours::BrightYellow);
	wait(500);
	std::cout << "                                          ";
	print_slow("Welcome to TRIVIA HUNT!\n\n");
	output_colour(ConsoleColours::Yellow);
	print_slow("*****************************************************************************************************************\n\n", 5);
}

inline void display_instructions() {
	output_colour(ConsoleColours::Yellow);
	std::cout << "    ";
	output_colour(ConsoleColours::BrightYellow);
	print_slow("This game will ask trivia questions and display treasure hunt clues based on the number of right answers.\n\n");
	wait(500);
	std::cout << "                      ";
	print_slow("Once enough correct answers are given, a new clue is displayed!\n\n");
	wait(500);
	std::cout << "                 ";
	print_slow("When you get a clue, use it to search for treasure then come back to get more clues!\n\n");
	wait(500);
	std::cout << "             ";
	print_slow("Questions that receive an incorrect answer are shuffled and re-entered into the loop.\n\n");
	std::cout << "                                          ";
	wait(500);
	print_slow("Have fun and good luck!\n\n");
	output_colour(ConsoleColours::Yellow);
	print_slow("*****************************************************************************************************************\n\n\n\n\n", 5);
}

inline void get_name(std::string& name) {
	output_colour(ConsoleColours::BrightYellow);
	print_slow("Enter your name to continue....\n\n");
	output_colour(ConsoleColours::BrightBlue);
	std::cin >> name;
	output_colour(ConsoleColours::BrightYellow);
	
}

inline void program_introduction() {
	display_header();
	wait(1500);
	display_instructions();
	wait(100);
}

/*
\ fn:		inline void display_score(int score, int max_score, int clues_received, int max_clues) 
\ brief:	Displays the current score
\ param:	int score, int max_score, int clues_received, int max_clues
*/
inline void display_score(int score, int max_score, int clues_received, int max_clues) {
	output_colour(ConsoleColours::BrightYellow);
	std::cout << "  --------------------------------";
	std::cout << "\n  |    Your score is: " << score << " / " << max_score << "    |\n";
	std::cout << "  --------------------------------\n\n";

	std::cout << "  Number of clues left to get: " << max_clues - clues_received <<"\n\n";

}

inline void display_clue(Clue_t clue) {
	output_colour(ConsoleColours::BrightGreen);
	std::cout << "\nNew treasure clue unlocked!!\n";
	wait(1000);
	
	wait(1000);
	print_slow("\nYour clue is: \"" + clue + "\"", 60);
	wait(1000);
	std::cout << "\n";
	output_colour(ConsoleColours::BrightYellow);
	char c = 'z';
	while (toupper(c) != 'Y') {
		std::cout << "Enter Y to continue when you're done with this clue: ";
		std::cin >> c;
	}
}

/*
\ fn:		MC add_question_from_csv(std::string& csv_line)
\ brief:	Add question from a csv formatted string
\ param:	std::string& csv_line
*/
MC add_question_from_csv(std::string& csv_line);



/*
\ fn:		void load_questions(std::vector<MC>& questions, std::string file_path);
\ brief:	Loads questions from given filepath
\ param:	std::vector<MC>& questions, std::string file_path
*/
void load_questions(std::vector<MC>& questions, std::string file_path);

/*
\ fn:		void load_clues(std::queue<Clue_t>& clues, std::string file_path);
\ brief:	Loads treasure hunt clues from given filepath
\ param:	std::queue<Clue_t>& clues, std::string file_path
*/
void load_clues(std::queue<Clue_t>& clues, std::string file_path);

void ask_questions(std::vector<MC>& questions, std::queue<Clue_t>& clues, GameState& state, std::string questions_savepoint_filepath, std::string clues_savepoint_filepath, std::string state_save_filepath);

inline void display_victory(std::string name) {
	cls();
	std::cout << "\n\n";
	output_colour(ConsoleColours::Red);
	print_slow("   *******************************************************\n", 5);
	output_colour(ConsoleColours::Yellow);
	print_slow("   *******************************************************\n", 5);
	output_colour(ConsoleColours::BrightGreen);
	print_slow("   *******************************************************\n\n", 5);
	output_colour(ConsoleColours::BrightBlue);
	print_slow("            Congratulations " + name + "!!! You win!!!!\n\n");
	output_colour(ConsoleColours::BrightGreen);
	print_slow("   *******************************************************\n", 5);
	output_colour(ConsoleColours::Yellow);
	print_slow("   *******************************************************\n", 5);
	output_colour(ConsoleColours::Red);
	print_slow("   *******************************************************\n", 5);
	output_colour(ConsoleColours::Black);
}

void load_state(std::string state_save_filepath, GameState& state);

inline void save_state(std::string state_save_filepath, GameState const& state) {

	std::ofstream file(state_save_filepath);

	if (!file.is_open()) {
		std::cout << "Error: Could not save questions to file.\n";
		return;
	}

	file << "Player Name,Current Score,Points Per Question,Clue Threshold,Max Score,Num Clues Received,Next Clue Threshold\n";

	file
		<< state.player_name << ","
		<< state.current_score << ","
		<< state.PTS_PER_Q << ","
		<< state.CLUE_THRESHOLD << ","
		<< state.max_score << ","
		<< state.clues_received << ","
		<< state.next_clue_threshold << ","
		<< "\n";
}

inline void save_questions(std::string questions_savepoint_filepath, std::vector<MC> const& questions) {

	std::ofstream file(questions_savepoint_filepath);

	if (!file.is_open()) {
		std::cout << "Error: Could not save questions to file.\n";
		return;
	}

	file << "Trivia Questions,Correct Answer,Num Responses,Responses\n";

	for (MC const& question : questions) {

		auto options = question.options();

		file
			<< question.question() << ","
			<< question.correct_response() << ","
			<< options.size() << ",";

		for (auto option : options) {
			file << option << ",";
		}
		file << "\n";
	}
}






