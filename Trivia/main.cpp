#include <iostream>

#include "Trivia.hpp"

using namespace std;

int main() {
	display_header();
	vector<MC> questions;

	vector<string> responses = { "True", "False", "Maybe" };
	questions.push_back(MC("True or false? ", responses, 0));

	for(MC question : questions) {
		question.display();
	}
}