#pragma once

#include <vector>
#include <string>
#include <thread>


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
};

inline void display_header() {
	output_colour(ConsoleColours::Yellow);
	std::cout << "*****************************************************************************************************************\n\n";
	std::cout << "                                          Welcome to TRIVIA HUNT!\n\n";
	std::cout << "*****************************************************************************************************************\n\n\n";
}

inline void display_instructions() {
	output_colour(ConsoleColours::BrightYellow);
	std::cout << "*****************************************************************************************************************\n\n";
	std::cout << "This game will ask trivia questions and display treasure hunt hints based on the number of correct answers given.\n";
	std::cout << "             Questions that receive an incorrect answer are shuffled and re-entered into the loop.\n\n";
	std::cout << "                      Once enough correct answers are given, a new hint is dropped!\n";
	std::cout << "                                          Have fun and good luck!\n\n";
	std::cout << "*****************************************************************************************************************\n\n\n\n\n";
}

inline void get_name(std::string& name) {
	std::cout << "Enter your name to continue....\n\n";
	output_colour(ConsoleColours::BrightBlue);
	std::cin >> name;
	
}

inline void cls() {
	std::cout << "\033[2J\033[H";
	std::cout << "\n";
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



