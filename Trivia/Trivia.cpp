#include <iostream>

#include "Trivia.hpp"



void MC::display() {

	std::cout << question_ << std::endl;
	char c = 'A';

	for (int i = 0; i < responses_.size(); i++) {
		std::cout << c++ << ". " << responses_[i] << std::endl;
	}
}

void ask_questions(std::vector<MC>& questions) {
	for (MC question : questions) {
		char answer;
		question.display();
		do {
			std::cout << "\n";
			get_valid_input(std::cin, answer, "Enter your answer: ");
			answer = toupper(answer);
			if (answer < 'A' || answer > 'A' + question.get_reponses().size() - 1) {
				std::cout << "Invalid response. Please try again.\n";
			}

		} while (answer < 'A' || answer > 'A' + question.get_reponses().size() - 1);
		// DEBUG
		int correct_answer = question.get_correct_r() + 'A';
		if (answer == correct_answer) {

			output_colour(ConsoleColours::BrightGreen);

			std::cout << "Correct!" << std::endl;

			output_colour(ConsoleColours::White);
		}
		else {
			output_colour(ConsoleColours::BrightRed);

			std::cout << "Incorrect!" << std::endl;

			output_colour(ConsoleColours::White);

		}

		std::cout << "\n\n";
	}
}