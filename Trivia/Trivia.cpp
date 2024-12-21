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


//void load_clues(std::queue<Clue_t>& clues, std::string file_path) {
//
//	std::ifstream file_stream;
//	file_stream.open(file_path);
//
//	// If file could not be opened, notify user and exit
//	if (!file_stream) {
//		std::cerr << "Error: could not open file path: \"" << file_path << "\".\n";
//		file_stream.close();
//		return;
//	}
//	std::string line;
//
//	//get header (get rid of header line)
//	getline(file_stream, line);
//	// iterate over file, adding each line as a patient to the queue
//	while (getline(file_stream, line)) {
//		clues.push(line);
//	}
//}


void ask_questions(GameState& state) {


	while(!state.questions.empty() || !state.clues.empty()) {

		display_score(state.current_score, state.max_score, state.clues_received, state.max_clues);
		
		MC current_question = state.questions[0];

		char answer = ask_question(current_question);

		char correct_answer = current_question.correct_response_char();
		
		answer == correct_answer ? 
			handle_correct_response(current_question, state)
		:	handle_incorrect_response(state);
		
		wait(1500);
		cls();
	}

}
