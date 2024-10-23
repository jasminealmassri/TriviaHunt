#include <iostream>

#include "Trivia.hpp"
#include "Utility.hpp"

using namespace std;

int main() {
	display_header();
	vector<MC> questions;

	vector<string> responses = { "True", "False", "Maybe" };
	questions.push_back(MC("True or false? ", responses, 0));


	for(MC question : questions) {
		char answer;
		question.display();
		do {
			get_valid_input(cin, answer, "Enter your answer: ");
			answer = toupper(answer);
			if (answer < 'A' || answer > 'A' + question.get_reponses().size() - 1) {
				std::cout << "Invalid response. Please try again.\n";
			}

		} while (answer < 'A' || answer > 'A' + question.get_reponses().size() - 1);
		// DEBUG
		std::cout << "You chose " << answer << std::endl;
	}
}