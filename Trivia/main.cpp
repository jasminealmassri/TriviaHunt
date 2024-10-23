#include <iostream>

#include "Trivia.hpp"

using namespace std;

int main() {
	display_header();
	vector<MC> questions;

	vector<string> responses = { "True, False" };
	questions.push_back(MC("True or false? ", 2));
}