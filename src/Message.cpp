/*
 * Message.cpp
 *
 *  Created on: Jun 15, 2014
 *      Author: doug
 */

#include "Message.h"


Message::Message(std::string text, std::string &alphabet) {
	this->text = text;
	distribution = SymbolDistribution(text, alphabet);
}

Message::~Message() {
}


const std::string& Message::getText() const {
	return text;
}

void Message::setText(const std::string &text, std::string &alphabet) {
	this->text = text;
	distribution = SymbolDistribution(text, alphabet);
}

const SymbolDistribution& Message::getDistribution() const {
	return distribution;
}

void Message::setDistribution(const SymbolDistribution& distribution) {
	this->distribution = distribution;
}
