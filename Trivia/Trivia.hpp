#pragma once

#include <vector>
#include <string>

class MC {
	unsigned num_responses_;
	std::vector<std::string> responses_;
	unsigned correct_response_;
	MC(unsigned num_responses = 2, std::vector<std::string> responses = { "True", "False" }, unsigned correct_response = 1) : num_responses_(num_responses), responses_(responses), correct_response_(correct_response) {}

	unsigned get_num_r() const { return num_responses_; }
	unsigned get_correct_r() const { return correct_response_; }
	std::vector<std::string> get_reponses() const { return responses_; }

	void display();
};
