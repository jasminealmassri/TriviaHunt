#include <iostream>
#include "Utility.hpp"
#include "Trivia.hpp"

void MC::display() {

	output_colour(ConsoleColours::BrightCyan);
	
#ifdef TESTING
	print_slow(question_ + "\n", 35);
	print_slow(std::string(question_.size(), '-'), 2);
#else
	std::cout << question_ << std::endl << std::endl;
#endif

	wait(50);
	std::cout << "\n";
	output_colour(ConsoleColours::White);
	char c = 'A';

	for (int i = 0; i < options_.size(); i++) {
		std::cout << c++ << ". " << options_[i] << std::endl;
	}

}

 
/*
\ fn:		void add_question_from_csv(std::istream& is, std::vector<MC>& questions)
\ brief:	Gets question from a csv formatted input
\ param:	std::istream& is, std::vector<MC>& questions
*/
MC get_question_from_csv(std::string& csv_line) {

	std::istringstream ss(csv_line);

	// Variables for current question
	std::string question;
	int correct_response;
	int num_responses;
	std::vector<std::string> responses;

	// Get question
	getline(ss, question, ',');

	// Get correct response
	get_valid_input(ss, correct_response, "", ',');

	// get the number of responses
	get_valid_input(ss, num_responses, "", ',');

	// Iterate over each response and add it to the responses
	for (int i = 0; i < num_responses; i++) {

		std::string response;

		getline(ss, response, ',');

		// Add response to responses
		responses.push_back(response);

	}
	// Add question (correct response - 1 because they are 1-based in csv)
	return MC(question, responses, correct_response - 1);

}


void ask_questions(GameState& state) {

	while(!state.questions.empty() || !state.clues.empty()) {

		state.display_score();
		
		MC current_question = state.questions[0];

		char answer = ask_question(current_question);

		char correct_answer = current_question.correct_response_char();
		
		answer == correct_answer ? handle_correct_response(current_question, state) : handle_incorrect_response(state);
		
		wait(1500);
		cls();
	}

}
