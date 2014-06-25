/**
 * Message.h
 *
 * The Message class is a basic container to hold a string of symbols in a
 * message alphabet and the frequency distribution calculated over that string
 * of symbols. Both a plain text and a cipher text can be represented by the
 * same Message type.
 *
 *  Created on: Jun 15, 2014
 *      Author: Douglas Sackin, NYU CS6903, Summer 2014
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <string>
#include <map>

#include "SymbolDistribution.h"

/**
 * Message
 *
 * The Message class is a basic container to hold a string of symbols in a
 * message alphabet and the frequency distribution calculated over that string
 * of symbols. Both a plain text and a cipher text can be represented by the
 * same Message type.
 *
 */
class Message {
public:
	/**
	 * Constructor to build a new message given a string of symbols and an optional
	 * alphabet prescribing the range of the symbols. The separate
	 * SymbolDistribution type is used to represent and operate on the distribution
	 * of symbols. If no alphabet is provided, the default alphabet is assumed.
	 * The default alphabet is defined in SymbolDistribution as [a..z].
	 *
	 * @param text - string representing the content of a message
	 * @param alphabet - optional string defining the alphabet or symbol space of
	 * the message
	 */
	Message(std::string text, std::string &alphabet = defaultAlphabet) {
		this->text = text;
		distribution = SymbolDistribution(text, alphabet);
	}

	/**
	 * Default deconstructor
	 */
	virtual ~Message() {};

	/**
	 * Return the text underlying this Message
	 * @return std::string - string underlying the message
	 */
	const std::string& getText() const {
		return text;
	}

	/**
	 * Set the text underlying this Message. If the text is set, recalculate the
	 * frequency distribution of the symbols.
	 *
	 * @param text - string representing the content of a message
	 * @param alphabet - optional string defining the alphabet or symbol space of
	 * the message
	 */
	void setText(const std::string &text, std::string &alphabet = defaultAlphabet) {
		this->text = text;
		distribution = SymbolDistribution(text, alphabet);
	}

	/**
	 * Return the symbol frequency distribution object for the current Message content.
	 *
	 * @return SymbolDistribution - symbol frequency distribution object for the
	 * current Message content
	 */
	const SymbolDistribution& getDistribution() const {
		return distribution;
	}


	/**
	 * Return the text of the message with each symbol shifted to the right or left
	 * by some integer amount. This does not alter the content of the message. It
	 * simulates the shift on a copy of the message.
	 *
	 * @param shift - integer shift amount. Positive shifts symbol to the right in
	 * the alphabet. Negative shifts to the left.
	 * @return std::string - copy of the message text with each symbol shifted by
	 * the indicated amount
	 */
	std::string getShiftedText(int shift) const {
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

protected:
	/**
	 * Text of the message as a string of symbols in the alphabet.
	 */
	std::string text;

	/**
	 * Frequency distribution of the symbols as contained in the message text
	 */
	SymbolDistribution distribution;
};

#endif /* MESSAGE_H_ */
