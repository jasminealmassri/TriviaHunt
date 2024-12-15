#include "CSVParser.hpp"
#include <algorithm>

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





