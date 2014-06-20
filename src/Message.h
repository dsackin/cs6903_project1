/*
 * Message.h
 *
 *  Created on: Jun 15, 2014
 *      Author: doug
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <string>
#include <map>

#include "SymbolDistribution.h"

class Message {
public:
	Message(std::string text, std::string &alphabet = defaultAlphabet);
	virtual ~Message();

	const std::string& getText() const;
	void setText(const std::string &text, std::string &alphabet = defaultAlphabet);
	void setDistribution(const SymbolDistribution& distribution);
	std::string getShiftedText(int shift) const;
	const SymbolDistribution& getDistribution() const;

protected:
	std::string text;
	SymbolDistribution distribution;
};

#endif /* MESSAGE_H_ */
