/*
 * Message.cpp
 *
 *  Created on: Jun 15, 2014
 *      Author: Douglas Sackin, NYU CS6903, Summer 2014
 */
/*
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

std::string Message::getShiftedText(int shift) const {
	std::string shiftedText;

	int alphabetSize = getDistribution().getAlphabetSize();
	char alphabetBase = getDistribution().getAlphabet()[0];


	char shiftedSymbol;
	for (std::string::const_iterator it = text.begin(); it != text.end(); ++it) {
		//	old calculation not respecting alphabet
//		shiftedSymbol = ((*it - alphabetBase) + (alphabetSize + shift)) % alphabetSize + alphabetBase;

		// new calculation using specified alphabet. Does NOT check that character is IN the alphabet.
		shiftedSymbol = getDistribution().getAlphabet()[((*it - alphabetBase) + (alphabetSize + shift)) % alphabetSize];
		shiftedText += shiftedSymbol;
	}

	return shiftedText;
}

const SymbolDistribution& Message::getDistribution() const {
	return distribution;
}
*/
