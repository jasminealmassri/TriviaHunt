#include <iostream>
#include "Utility.hpp"
#include "Trivia.hpp"

void MC::display() {

	output_colour(ConsoleColours::BrightCyan);
	print_slow(question_ + "\n", 35);
	print_slow(std::string(question_.size(), '-'), 2);
	wait(50);
	std::cout << "\n";
	output_colour(ConsoleColours::White);
	char c = 'A';

	for (int i = 0; i < responses_.size(); i++) {
		std::cout << c++ << ". " << responses_[i] << std::endl;
	}

}

/*
\ fn:		void add_question_from_csv(std::istream& is, std::vector<MC>& questions)
\ brief:	Add question from a csv formatted input
\ param:	std::istream& is, std::vector<MC>& questions
*/
MC add_question_from_csv(std::string& csv_line) {

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

/*
\ fn:		void load_hints(std::vector<std::string>& hints)
\ brief:	Loads the hints from hints.csv
\ param:	PriorityQueue<Patient> const& queue
*/
void load_hints(std::vector<std::string>& hints) {
	std::string file_path("../Hints.csv");

	std::ifstream file_stream;
	file_stream.open(file_path);

	// If file could not be opened, notify user and exit
	if (!file_stream) {
		std::cerr << "Error: could not open file path: \"" << file_path << "\".\n";
		file_stream.close();
		return;
	}
	std::string line;

	//get header (get rid of header line)
	getline(file_stream, line);
	// iterate over file, adding each line as a patient to the queue
	while (getline(file_stream, line)) {
		hints.push_back(line);
	}
}

/*
\ fn:		void load_queue(PriorityQueue<Patient>& queue)
\ brief:	Adds to the current patient queue by loading from a CSV file provided by user
\ param:	PriorityQueue<Patient> const& queue
*/
void load_questions(std::vector<MC>& questions) {

	// get filepath from user
	//std::string file_path;
	//std::cout << "Enter path to file: ";
	//getline(std::cin, file_path);

	std::string file_path("../Trivia.csv");

	std::ifstream file_stream;
	file_stream.open(file_path);

	// If file could not be opened, notify user and exit
	if (!file_stream) {
		std::cerr << "Error: could not open file path: \"" << file_path << "\".\n";
		file_stream.close();
		return;
	}
	std::string line;

	//get header (get rid of header line)
	getline(file_stream, line);
	// iterate over file, adding each line as a patient to the queue
	while (getline(file_stream, line)) {
		questions.push_back(add_question_from_csv(line));
	}
}


void ask_questions(std::vector<MC>& questions, int& score, std::vector<std::string> hints) {

	shuffle(questions);
	const int num_hints_max = hints.size();
	const int hints_received{};
	const int PTS_PER_Q = 10;

	for (MC question : questions) {
		display_score(score, questions.size() * PTS_PER_Q, hints_received, num_hints_max);
		char answer;
		question.display();
		do {
			std::cout << "\n";
			get_valid_input(std::cin, answer, "Enter your answer: ");
			answer = toupper(answer);

			if (question.invalid_answer(answer)) {
				std::cout << "Invalid response. Please try again.\n";
			}

		} while (question.invalid_answer(answer));
		// DEBUG
		int correct_answer = question.get_correct_r() + 'A';
		
		if (answer == correct_answer) {

			output_colour(ConsoleColours::BrightGreen);

			std::cout << "Correct!" << std::endl;

			output_colour(ConsoleColours::White);
			score += PTS_PER_Q;
		}
		else {
			output_colour(ConsoleColours::BrightRed);

			std::cout << "Incorrect!" << std::endl;

			output_colour(ConsoleColours::White);
		}
			wait(1500);
			cls();
	}

}
