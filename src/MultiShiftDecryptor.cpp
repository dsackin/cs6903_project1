/*
 * MultiShiftDecryptor.cpp
 *
 *  Created on: Jun 17, 2014
 *      Author: doug
 */

#include <math.h>
#include <iostream>
#include <sstream>

#include "MultiShiftDecryptor.h"

MultiShiftDecryptor::MultiShiftDecryptor() {}

MultiShiftDecryptor::MultiShiftDecryptor(int index, std::string plainText,
		std::string cipherText, int keyLength) : Decryptor(index, plainText, cipherText) {

	this->keyLength = keyLength;

	plainSegments = deriveSegments(plainText, keyLength);
	cipherSegments = deriveSegments(cipherText, keyLength);
}

MultiShiftDecryptor::~MultiShiftDecryptor() {
}

const std::vector<Message>& MultiShiftDecryptor::getCipherSegments() const {
	return cipherSegments;
}

int MultiShiftDecryptor::getKeyLength() const {
	return keyLength;
}

const std::vector<Message>& MultiShiftDecryptor::getPlainSegments() const {
	return plainSegments;
}

std::vector<Message> MultiShiftDecryptor::deriveSegments(std::string text, int keyLength) {
	int textLength = text.length();

	int segmentMax = ceil((float)textLength / keyLength) + 1;
	char segments[keyLength][segmentMax];

	for (int textIndex = 0; textIndex < textLength; textIndex++) {
		int segment = textIndex % keyLength;
		int segmentIndex = floor(textIndex / keyLength);
		segments[segment][segmentIndex] = text[textIndex];
		segments[segment][segmentIndex + 1] = '\0';
//		printf("%d %d %d %s\n", textIndex, segment, segmentIndex, segments[segment]);
	}

	std::vector<Message> messages;
	for (int segmentIndex = 0; segmentIndex < keyLength; segmentIndex++) {
//		std::string s(segments[segmentIndex]);
//		std::cout << "text of segment " << segmentIndex << " " << s << std::endl;
//		Message m(s);
		messages.push_back(Message(std::string(segments[segmentIndex])));
	}

	return messages;
}

//int MultiShiftDecryptor::downSelectByDistribution() {
//
//	SymbolDistribution cipherDistribution = cipherText.getDistribution();
//	int viableCandidates = plainTexts.size();
//	for (int i = 0; i < plainTexts.size(); i++) {
//		SymbolDistribution candidateDistribution =
//				plainTexts[i].getDistribution();
//		if (!cipherDistribution.equalByDistribution(candidateDistribution)) {
//			plainTexts[i].exclude();
//			viableCandidates--;
//		}
//	}
//	return viableCandidates;
//}


int MultiShiftDecryptor::decrypt() {
	return 0;
}
