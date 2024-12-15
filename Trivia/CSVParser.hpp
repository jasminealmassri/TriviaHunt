#pragma once

#include <sstream>
#include <fstream>
#include "Utility.hpp"
#include "Trivia.hpp"

/*
\ fn:		MC add_question_from_csv(std::string& csv_line) 
\ brief:	Add question from a csv formatted string
\ param:	std::string& csv_line
*/
MC add_question_from_csv(std::string& csv_line);


/*
\ fn:		void load_queue(PriorityQueue<Patient>& queue)
\ brief:	Adds to the current patient queue by loading from a CSV file provided by user
\ param:	PriorityQueue<Patient> const& queue
*/
void load_questions(std::vector<MC>& questions);


