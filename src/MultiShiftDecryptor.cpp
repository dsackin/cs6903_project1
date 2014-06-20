/*
 * MultiShiftDecryptor.cpp
 *
 *  Created on: Jun 17, 2014
 *      Author: doug
 */

#include <math.h>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "MultiShiftDecryptor.h"

MultiShiftDecryptor::MultiShiftDecryptor() : keyLength(1) {}

MultiShiftDecryptor::MultiShiftDecryptor(int index, std::string plainText,
		std::string cipherText, int keyLength) : Decryptor(index, plainText, cipherText) {

	this->keyLength = keyLength;

	this->plainSegments = deriveSegments(plainText, keyLength);
	this->cipherSegments = deriveSegments(cipherText, keyLength);
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

bool MultiShiftDecryptor::decrypt() {

//	  std::string key(keyLength)
//	  for (int i; i < keyLength; i++) {
//		if (!cipherIntevals.at(i).getDistribution().equalByDistribution(candidateIntervals.at(i).getDistribution())
//	  	return false;
//		else {
//	   	char keyValue = determineIntervalKey(i)
//	   	if keyValue != '\0'
//	      	key.insert(i, keyValue)
//	   	else
//	      	return false;
//	}

	for (int segmentIndex = 0; segmentIndex < keyLength; segmentIndex++) {
		SymbolDistribution plainDistro = plainSegments[segmentIndex].getDistribution();
		SymbolDistribution cipherDistro = cipherSegments[segmentIndex].getDistribution();

		if (!cipherDistro.equalByDistribution(plainDistro))
			return false;

		char keyValue = determineSegmentKey(plainSegments[segmentIndex], cipherSegments[segmentIndex]);
		if (keyValue != '\0')
			keySolution += keyValue;
		else
			return false;
	}

	return true;
}

struct FrequencyComparator
{
    bool operator() ( const std::pair<int, char>& lhs, const std::pair<int, char>& rhs)
    {
        return lhs.first < rhs.first;
    }
 };

char MultiShiftDecryptor::determineSegmentKey(Message &plainMessage, Message &cipherMessage) {
	std::vector<std::pair<int, char> > plainFreqs = plainMessage.getDistribution().extractFrequenciesRaw();
	std::vector<std::pair<int, char> > cipherFreqs = cipherMessage.getDistribution().extractFrequenciesRaw();

	// extractFrequenciesRaw() returned vector of std::pair<int, char>
	// stably sorted in ascending order by count, then symbol, so the
	// most frequent symbol in the cipher should be the last pair in the list.
	std::pair<int, char> cipherMostFrequentSymbol = cipherFreqs.back();
	std::pair<std::vector<std::pair<int, char> >::iterator, std::vector<std::pair<int, char> >::iterator> cipherMaxSymbolRange = std::equal_range(cipherFreqs.begin(), cipherFreqs.end(), cipherFreqs.back(), FrequencyComparator());
	std::pair<std::vector<std::pair<int, char> >::iterator, std::vector<std::pair<int, char> >::iterator> plainMaxSymbolRange = std::equal_range(plainFreqs.begin(), plainFreqs.end(), cipherFreqs.back(), FrequencyComparator());

	char alphabetBase = plainMessage.getDistribution().getAlphabet()[0];
	for ( std::vector<std::pair<int, char> >::iterator cipherSymbol = cipherMaxSymbolRange.first; cipherSymbol != cipherMaxSymbolRange.second; ++cipherSymbol) {
		for ( std::vector<std::pair<int, char> >::iterator plainSymbol = plainMaxSymbolRange.first; plainSymbol != plainMaxSymbolRange.second; ++plainSymbol) {
			int shift = cipherSymbol->second - plainSymbol->second;

			std::string shiftedPlain = plainMessage.getShiftedText(shift);
			if (cipherMessage.getText() == shiftedPlain) {
				char keySymbol = shift + alphabetBase;
				return alphabetBase;
			}
		}
	}

	// no matches
	return '\0';
}


