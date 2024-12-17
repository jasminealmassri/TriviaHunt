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


void ask_questions(std::vector<MC>& questions, int& score) {

	shuffle(questions);


	for (MC question : questions) {
		output_score(score);
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
			score += 10;
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