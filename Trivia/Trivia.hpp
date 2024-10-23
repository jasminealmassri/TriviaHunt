#pragma once

#include <vector>
#include <string>

class MC {
	std::string question_;
	std::vector<std::string> responses_;
	unsigned correct_response_;
public:
	MC(
		  std::string question = ""
		, std::vector<std::string> responses = {"True", "False"}
		, unsigned correct_response = 1
	) 
		: question_(question)
		, responses_(responses)
		, correct_response_(correct_response) 
	{}

	unsigned get_correct_r() const { return correct_response_; }
	std::vector<std::string> get_reponses() const { return responses_; }

	void display();
};


void display_header();
