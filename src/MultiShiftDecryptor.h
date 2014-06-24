/*
 * MultiShiftDecryptor.h
 *
 *  Created on: Jun 18, 2014
 *      Author: doug
 */

#ifndef MULTISHIFTDECRYPTOR_H_
#define MULTISHIFTDECRYPTOR_H_

#include <vector>
#include <string>

#include "Decryptor.h"
#include "Message.h"


class MultiShiftDecryptor : public Decryptor {
public:
	MultiShiftDecryptor();
	MultiShiftDecryptor(int index, std::string plainText,
			std::string cipherText, int keyLength = 1);
	virtual ~MultiShiftDecryptor();

	bool decrypt();

	const std::vector<Message>& getCipherSegments() const;
	int getKeyLength() const;
	const std::vector<Message>& getPlainSegments() const;
	const std::string getExplanation() const;
	const std::vector<int> &getKeyShifts() const;
	const std::string getKeyString() const;

protected:
	int keyLength;
	std::vector<Message> plainSegments;
	std::vector<Message> cipherSegments;
	std::vector<int> keyShifts;

	void initialize();

	static std::vector<Message> deriveSegments(std::string text, int keyLength);

	static int determineSegmentKey(Message &plainMessage, Message &cipherMessage);

};
#endif /* MULTISHIFTDECRYPTOR_H_ */
