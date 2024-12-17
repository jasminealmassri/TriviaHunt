#include <iostream>

#include "Trivia.hpp"
#include "Utility.hpp"
#include "CSVParser.hpp"

using namespace std;

int main() {
	

	// Uncomment when ready
	//program_introduction();

	/*std::string name;
	get_name(name);
	cls();*/

	vector<MC> questions;

	// Parsing questions
	load_questions(questions);
	
	// Process questions
	ask_questions(questions);
	
}