#include <iostream>

#include "Trivia.hpp"
#include "Utility.hpp"
#include "CSVParser.hpp"

using namespace std;

int main() {
	display_header();
	vector<MC> questions;

	//vector<string> responses = { "True", "False", "Maybe" };
	//questions.push_back(MC("True or false? ", responses, 0));

	// Parsing questions
	load_questions(questions);

	for(MC question : questions) {
		char answer;
		question.display();
		do {
			std::cout << "\n";
			get_valid_input(cin, answer, "Enter your answer: ");
			answer = toupper(answer);
			if (answer < 'A' || answer > 'A' + question.get_reponses().size() - 1) {
				std::cout << "Invalid response. Please try again.\n";
			}

		} while (answer < 'A' || answer > 'A' + question.get_reponses().size() - 1);
		// DEBUG
		int correct_answer = question.get_correct_r() + 'A';
		if (answer == correct_answer) {
			std::cout << "\33[92m" << "Correct!" << std::endl;
			std::cout << "\33[37m";
		}
		else {
			std::cout << "\33[31m" << "Incorrect" << std::endl;
			std::cout << "\33[37m";
		}
		std::cout << "\n\n";
	}
}