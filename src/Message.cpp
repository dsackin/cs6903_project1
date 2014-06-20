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

void Message::setDistribution(const SymbolDistribution& distribution) {
	this->distribution = distribution;
}

std::string Message::getShiftedText(int shift) const {
	std::string shiftedText;

	int alphabetSize = getDistribution().getAlphabetSize();
	char alphabetBase = getDistribution().getAlphabet()[0];


	char shiftedSymbol;
	for (std::string::const_iterator it = text.begin(); it != text.end(); ++it) {
		shiftedSymbol = ((*it - alphabetBase) + (alphabetSize + shift)) % alphabetSize + alphabetBase;
		shiftedText += shiftedSymbol;
	}

	return shiftedText;
}

const SymbolDistribution& Message::getDistribution() const {
	return distribution;
}
