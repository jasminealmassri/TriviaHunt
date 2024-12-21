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


void load_clues(std::queue<Clue_t>& clues, std::string file_path) {

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
		clues.push(line);
	}
}

/*
\ fn:		void load_queue(PriorityQueue<Patient>& queue)
\ brief:	Adds to the current patient queue by loading from a CSV file provided by user
\ param:	PriorityQueue<Patient> const& queue
*/
//void load_questions(std::vector<MC>& questions, std::string file_path) {
//
//	// get filepath from user
//	//std::string file_path;
//	//std::cout << "Enter path to file: ";
//	//getline(std::cin, file_path);
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
//		questions.push_back(add_question_from_csv(line));
//	}
//}


void ask_questions(std::queue<Clue_t>& clues, GameState& state) {


	while(!state.questions.empty()) {

		display_score(state.current_score, state.max_score, state.clues_received, state.max_clues);
		
		char answer;
		state.questions[0].display();
		
		// get valid answer from user
		do {
			get_valid_input(std::cin, answer, "\nEnter your answer: ");
			answer = toupper(answer);

			if (state.questions[0].invalid_answer(answer)) {
				std::cout << "Invalid response. Please try again.\n";
			}

		} while (state.questions[0].invalid_answer(answer));

		int correct_answer = state.questions[0].correct_response() + 'A';
		
		if (answer == correct_answer) {

			output_colour(ConsoleColours::BrightGreen);
			std::cout << "\nCorrect!" << std::endl;
			output_colour(ConsoleColours::White);

			state.current_score += state.PTS_PER_Q;

			state.questions.erase(std::find(state.questions.begin(), state.questions.end(), state.questions[0]));

			state.save_questions();

			save_clues(state.clues_save_path, clues);

			if (state.current_score == state.next_clue_threshold) {

				display_clue(clues.front());
				clues.pop();
				
				// quit if all clues are received
				if (clues.empty()) {
					break;
				}

				save_clues(state.clues_save_path, clues);
				state.clues_received++;
				state.next_clue_threshold += state.CLUE_THRESHOLD;
			}
		
			state.save_state();
			
		}
		else {

			output_colour(ConsoleColours::BrightRed);

			std::cout << "\nIncorrect!" << std::endl;

			output_colour(ConsoleColours::White);

			shuffle(state.questions);
		}

		wait(1500);
		cls();
	}

	state.remove_save_files();

}
