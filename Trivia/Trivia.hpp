#pragma once

#include <vector>
#include <string>
#include <queue>
#include <fstream>
#include <filesystem>

#include "Utility.hpp"
#include "CSVParser.hpp"

using Clue_t = std::string;

/*
*	class:		MC
*	purpose:	Represents a multiple choice trivia question
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
	char correct_response_char() const { return correct_response_ + 'A'; }
	std::vector<std::string> options() const { return options_; }

	void display();

	bool invalid_answer(char answer) {
		return answer < 'A' || answer > 'A' + options_.size() - 1;
	}

	bool operator == (MC const& other) {
		return question_ == other.question_;
	}
};

/*
*   fn:			MC add_question_from_csv(std::string& csv_line)
*   purpose:	Add question from a csv formatted string
*/
MC get_question_from_csv(std::string& csv_line);

/*
*	struct:		GameState
*	purpose:	Holds state, saving, loading methods
*/
struct GameState {

	std::string player_name{};
	int current_score{};
	int PTS_PER_Q{ 10 };
	int CLUE_THRESHOLD{ 5 * PTS_PER_Q };
	int max_score{};
	int max_clues{};
	int clues_received{};
	int next_clue_threshold{ CLUE_THRESHOLD };

	std::string questions_filepath{};
	std::string clues_filepath{};

	std::string questions_save_path{};
	std::string clues_save_path{};
	std::string state_save_path{};

	std::vector<MC> questions{};
	std::queue<Clue_t> clues{};

	void display_score() {
		output_colour(ConsoleColours::BrightYellow);
		std::cout << "  --------------------------------";
		std::cout << "\n  |    Your score is: " << current_score << " / " << max_score << "    |\n";
		std::cout << "  --------------------------------\n\n";

		std::cout << "  Number of clues left to get: " << max_clues - clues_received << "\n\n";
	}

	void save_state() const {

		std::ofstream file(state_save_path);

		if (!file.is_open()) {
			std::cout << "Error: Could not save questions to file.\n";
			return;
		}

		file << "Player Name,Current Score,Points Per Question,Clue Threshold,Max Score,Max Clues,Num Clues Received,Next Clue Threshold\n";

		file
			<< player_name << ","
			<< current_score << ","
			<< PTS_PER_Q << ","
			<< CLUE_THRESHOLD << ","
			<< max_score << ","
			<< max_clues << ","
			<< clues_received << ","
			<< next_clue_threshold << ","
			<< "\n";
	}
	void load_state() {

		if (!std::filesystem::exists(state_save_path)) {
			return;
		}

		std::ifstream file(state_save_path);

		if (!file.is_open()) {
			std::cout << "Error: Could not open state save file.\n";
			return;
		}

		std::string line;
		// header
		getline(file, line);

		getline(file, line);
		std::istringstream ss(line);


		getline(ss, player_name, ',');
		get_valid_input(ss, current_score, "", ',');
		get_valid_input(ss, PTS_PER_Q, "", ',');
		get_valid_input(ss, CLUE_THRESHOLD, "", ',');
		get_valid_input(ss, max_score, "", ',');
		get_valid_input(ss, max_clues, "", ',');
		get_valid_input(ss, clues_received, "", ',');
		get_valid_input(ss, next_clue_threshold, "", ',');
	}
	
	void load_questions() {
		std::ifstream file_stream;
		file_stream.open(questions_filepath);

		// If file could not be opened, notify user and exit
		if (!file_stream) {
			std::cerr << "Error: could not open file path: \"" << questions_filepath << "\".\n";
			file_stream.close();
			return;
		}
		std::string line;

		//get header (get rid of header line)
		getline(file_stream, line);
		// iterate over file, adding each line as a patient to the queue
		while (getline(file_stream, line)) {
			questions.push_back(get_question_from_csv(line));
		}
	}

	void shuffle_questions() {
		shuffle(questions);
	}

	void save_questions() {

		std::ofstream file(questions_save_path);

		if (!file.is_open()) {
			std::cout << "Error: Could not save questions to file.\n";
			return;
		}

		file << "Trivia Questions,Correct Answer,Num Responses,Responses\n";

		for (MC const& question : questions) {

			auto options = question.options();

			file
				<< question.question() << ","
				<< question.correct_response() + 1 << ","
				<< options.size() << ",";

			for (auto option : options) {
				file << option << ",";
			}
			file << "\n";
		}
	}

	void load_clues() {
		std::ifstream file_stream;
		file_stream.open(clues_filepath);

		// If file could not be opened, notify user and exit
		if (!file_stream) {
			std::cerr << "Error: could not open file path: \"" << clues_filepath << "\".\n";
			file_stream.close();
			return;
		}
		std::string line;

		//get header (get rid of header line)
		getline(file_stream, line);
		// iterate over file, adding each line as a patient to the queue
		while (getline(file_stream, line)) {
			clues.push(line);
		}
	}
	void save_clues() {

		std::ofstream file(clues_save_path);

		if (!file.is_open()) {
			std::cout << "Error: Could not save clues to file.\n";
			return;
		}

		file << "Clue\n";
		std::queue<Clue_t> clues_copy(clues);
		while (!clues_copy.empty()) {

			file << clues_copy.front() << "\n";
			clues_copy.pop();
		}
	}
	
	void remove_save_files() {
		std::filesystem::remove(questions_save_path);
		std::filesystem::remove(clues_save_path);
		std::filesystem::remove(state_save_path);
	}
};

inline bool continue_from_save() {
	
	char answer{};

	do {
		get_valid_input(std::cin, answer, "\nResume previous progress? (y/n): ");
		answer = toupper(answer);
	} while (answer != 'Y' && answer != 'N');

	std::cout << "\n\n";
	
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

inline int ask_question(MC question) {
	
	char answer;
	question.display();

	// get valid answer from user
	do {
		get_valid_input(std::cin, answer, "\nEnter your answer: ");
		answer = toupper(answer);

		if (question.invalid_answer(answer)) {
			std::cout << "Invalid response. Please try again.\n";
		}

	} while (question.invalid_answer(answer));

	return answer;
}

inline void handle_correct_response(MC current_question, GameState& state) {

	output_colour(ConsoleColours::BrightGreen);
	std::cout << "\nCorrect!" << std::endl;
	output_colour(ConsoleColours::White);

	state.current_score += state.PTS_PER_Q;

	state.questions.erase(std::find(state.questions.begin(), state.questions.end(), current_question));

	state.save_questions();
	state.save_clues();

	if (state.current_score == state.next_clue_threshold) {

		display_clue(state.clues.front());
		state.clues.pop();

		state.save_clues();
		state.clues_received++;
		state.next_clue_threshold += state.CLUE_THRESHOLD;
	}

	state.save_state();
}

inline void handle_incorrect_response(GameState& state) {
	
	output_colour(ConsoleColours::BrightRed);

	std::cout << "\nIncorrect!" << std::endl;

	output_colour(ConsoleColours::White);

	state.shuffle_questions();
}

void ask_questions(GameState& state);






