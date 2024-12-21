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

void load_state(std::string state_save_filepath, GameState& state) {

	if (!std::filesystem::exists(state_save_filepath)) {
		return;
	}

	std::ifstream file(state_save_filepath);

	if (!file.is_open()) {
		std::cout << "Error: Could not open state file.\n";
		return;
	}

	std::string line;
	// header
	getline(file, line);

	getline(file, line);
	std::istringstream ss(line);


	getline(ss, state.player_name, ',');
	get_valid_input(ss, state.current_score, "", ',');
	get_valid_input(ss, state.PTS_PER_Q, "", ',');
	get_valid_input(ss, state.CLUE_THRESHOLD, "", ',');
	get_valid_input(ss, state.max_score, "", ',');
	get_valid_input(ss, state.max_clues, "", ',');
	get_valid_input(ss, state.clues_received, "", ',');
	get_valid_input(ss, state.next_clue_threshold, "", ',');

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
void load_questions(std::vector<MC>& questions, std::string file_path) {

	// get filepath from user
	//std::string file_path;
	//std::cout << "Enter path to file: ";
	//getline(std::cin, file_path);

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


void ask_questions(std::vector<MC>& questions, std::queue<Clue_t>& clues, GameState& state, std::string questions_savepoint_filepath, std::string clues_savepoint_filepath, std::string state_save_filepath) {

	//const int NUM_QUESTIONS = questions.size();
	//const int NUM_CLUES = clues.size();
	
	//load_state(state_save_filepath, state);
	//const int PTS_PER_Q = 10;
	//const int CLUE_THRESHOLD{ 5 * PTS_PER_Q };
	//int clues_received{};
	//int next_clue_threshold{ CLUE_THRESHOLD };

	//std::ofstream questions_save_file;
	std::ofstream clues_save_file;

	while(!questions.empty()) {

		display_score(state.current_score, state.max_score, state.clues_received, state.max_clues);
		
		char answer;
		questions[0].display();
		
		// get valid answer from user
		do {
			get_valid_input(std::cin, answer, "\nEnter your answer: ");
			answer = toupper(answer);

			if (questions[0].invalid_answer(answer)) {
				std::cout << "Invalid response. Please try again.\n";
			}

		} while (questions[0].invalid_answer(answer));

		int correct_answer = questions[0].correct_response() + 'A';
		
		if (answer == correct_answer) {

			output_colour(ConsoleColours::BrightGreen);
			std::cout << "\nCorrect!" << std::endl;
			output_colour(ConsoleColours::White);

			state.current_score += state.PTS_PER_Q;

			questions.erase(std::find(questions.begin(), questions.end(), questions[0]));

			save_questions(questions_savepoint_filepath, questions);

			save_clues(clues_savepoint_filepath, clues);

			if (state.current_score == state.next_clue_threshold) {

				display_clue(clues.front());
				clues.pop();
				
				// quit if all clues are received
				if (clues.empty()) {
					break;
				}

				save_clues(clues_savepoint_filepath, clues);
				state.clues_received++;
				state.next_clue_threshold += state.CLUE_THRESHOLD;
			}
		
			save_state(state_save_filepath, state);
			
		}
		else {

			output_colour(ConsoleColours::BrightRed);

			std::cout << "\nIncorrect!" << std::endl;

			output_colour(ConsoleColours::White);

			shuffle(questions);
		}

		wait(1500);
		cls();
	}

	std::filesystem::remove(clues_savepoint_filepath);
	std::filesystem::remove(state_save_filepath);
	std::filesystem::remove(questions_savepoint_filepath);

}
