/*
 * Message.cpp
 *
 *  Created on: Jun 15, 2014
 *      Author: doug
 */

#include "Message.h"

Message::Message() {
	// TODO Auto-generated constructor stub

}

Message::Message(std::string s) {
	text = s;
	distribution = CalculateDistribution(text);
}

Message::~Message() {
	// TODO Auto-generated destructor stub
}

std::map<char, int> Message::CalculateDistribution(std::string s) {

	std::map<char, int> distribution;

	for (std::string::iterator it = s.begin(); it != s.end(); it++) {

		int current = distribution[*it];
		distribution[*it] = current + 1;
	}

	return distribution;
}

const std::map<char, int>& Message::getDistribution() const {
	return distribution;
}

void Message::setDistribution(const std::map<char, int>& distribution) {
	this->distribution = distribution;
}

const std::string& Message::getText() const {
	return text;
}

void Message::setText(const std::string& text) {
	this->text = text;
}
