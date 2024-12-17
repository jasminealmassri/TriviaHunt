#pragma once

#include <vector>
#include <string>



#include "Utility.hpp"
#include "CSVParser.hpp"



class MC {
	std::string question_;
	std::vector<std::string> responses_;
	unsigned correct_response_;
public:
	MC(
		  std::string question = ""
		, std::vector<std::string> responses = {"True", "False"}
		, unsigned correct_response = 1
	) 
		: question_(question)
		, responses_(responses)
		, correct_response_(correct_response) 
	{}

	unsigned get_correct_r() const { return correct_response_; }
	std::vector<std::string> get_reponses() const { return responses_; }

	void display();

	bool invalid_answer(char answer) {
		return answer < 'A' || answer > 'A' + responses_.size() - 1;
	}
};



inline void display_header() {
	output_colour(ConsoleColours::Yellow);
	print_slow("*****************************************************************************************************************\n\n", 5);
	output_colour(ConsoleColours::BrightYellow);
	wait(500);
	//std::cout << "                                          Welcome to TRIVIA HUNT!\n\n";
	std::cout << "                                          ";
	print_slow("Welcome to TRIVIA HUNT!\n\n");
	output_colour(ConsoleColours::Yellow);
	print_slow("*****************************************************************************************************************\n\n", 5);
}

inline void display_instructions() {
	output_colour(ConsoleColours::Yellow);
	std::cout << "    ";
	output_colour(ConsoleColours::BrightYellow);
	print_slow("This game will ask trivia questions and display treasure hunt hints based on the number of right answers.\n\n");
	wait(500);
	std::cout << "                      ";
	print_slow("Once enough correct answers are given, a new hint is dropped!\n\n");
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
	
}

inline void program_introduction() {
	display_header();
	wait(1500);
	display_instructions();
	wait(100);
}




/*
\ fn:		MC add_question_from_csv(std::string& csv_line)
\ brief:	Add question from a csv formatted string
\ param:	std::string& csv_line
*/
MC add_question_from_csv(std::string& csv_line);


/*
\ fn:		void load_queue(PriorityQueue<Patient>& queue)
\ brief:	Adds to the current patient queue by loading from a CSV file provided by user
\ param:	PriorityQueue<Patient> const& queue
*/
void load_questions(std::vector<MC>& questions);



void ask_questions(std::vector<MC>& questions);



