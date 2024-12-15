#pragma once

#include <vector>
#include <string>
#include <algorithm>

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
	std::cout << "Welcome to Trivia Hunt!\n";
	std::cout << "***********************\n\n";
}

inline void display_instructions() {

	std::cout << "This game will ask questions and display hints based on the number of correct answers given.\n";
	std::cout << "Incorrect questions are shuffled and re-entered into the loop.\n";
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



template<typename T>
void shuffle(T& v) {
	std::random_shuffle(v.begin(), v.end());
}
