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

class Message {
public:
	Message();
	Message(std::string s);
	virtual ~Message();

	static std::map<char, int> CalculateDistribution(std::string s);

	const std::map<char, int>& getDistribution() const;
	void setDistribution(const std::map<char, int>& distribution);

	const std::string& getText() const;
	void setText(const std::string& text);

protected:
	std::string text;
	std::map<char, int> distribution;

};

#endif /* MESSAGE_H_ */
