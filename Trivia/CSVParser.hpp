#pragma once

#include <sstream>
#include <fstream>
#include "Utility.hpp"
#include "Trivia.hpp"


enum ConsoleColours {
	Black = 30
,	Red 
,	Green 
,	Yellow 
,	Blue
,	Magenta
,	Cyan
,	White
,	BrightBlack = 90
,	BrightRed 
,	BrightGreen 
,	BrightYellow
,	BrightBlue
,	BrightMagenta
,	BrightCyan
,	BrightWhite
};
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


inline void output_colour(int color) {
	std::cout << "\33[" << color << "m";
}


void ask_questions(std::vector<MC>& questions);


