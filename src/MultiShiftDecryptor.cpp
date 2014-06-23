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
}

MultiShiftDecryptor::~MultiShiftDecryptor() {
}

void MultiShiftDecryptor::initialize() {
	plainSegments = deriveSegments(plainText, keyLength);
	cipherSegments = deriveSegments(cipherText, keyLength);
	isInitialized = true;
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

	if (!isInitialized)
		initialize();

	for (int segmentIndex = 0; segmentIndex < keyLength; segmentIndex++) {
		SymbolDistribution plainDistro = plainSegments[segmentIndex].getDistribution();
		SymbolDistribution cipherDistro = cipherSegments[segmentIndex].getDistribution();

		if (!cipherDistro.equalByDistribution(plainDistro))
			return false;

		int keyValue = determineSegmentKey(plainSegments[segmentIndex], cipherSegments[segmentIndex]);
		if (keyValue >= 0) {
			char keySymbol = keyValue + plainDistro.getAlphabet()[0];
			keySolution.push_back(std::pair<int, char>(keyValue, keySymbol));
		} else
			return false;
	}

	return true;
}

struct FrequencyOrderComparator
{
    bool operator() ( const std::pair<int, char>& lhs, const std::pair<int, char>& rhs)
    {
        return lhs.first < rhs.first;
    }
 };

int MultiShiftDecryptor::determineSegmentKey(Message &plainMessage, Message &cipherMessage) {
	std::vector<std::pair<int, char> > plainFreqs = plainMessage.getDistribution().extractFrequencies();
	std::vector<std::pair<int, char> > cipherFreqs = cipherMessage.getDistribution().extractFrequencies();

	// extractFrequenciesRaw() returned vector of std::pair<int, char>
	// stably sorted in ascending order by count, then symbol, so the
	// most frequent symbol in the cipher should be the last pair in the list.
	std::pair<int, char> cipherMostFrequentSymbol = cipherFreqs.back();
	std::pair<std::vector<std::pair<int, char> >::iterator, std::vector<std::pair<int, char> >::iterator> cipherMaxSymbolRange = std::equal_range(cipherFreqs.begin(), cipherFreqs.end(), cipherMostFrequentSymbol, FrequencyOrderComparator());
	std::pair<std::vector<std::pair<int, char> >::iterator, std::vector<std::pair<int, char> >::iterator> plainMaxSymbolRange = std::equal_range(plainFreqs.begin(), plainFreqs.end(), cipherMostFrequentSymbol, FrequencyOrderComparator());

	int alphabetSize = plainMessage.getDistribution().getAlphabetSize();
	char alphabetBase = plainMessage.getDistribution().getAlphabet()[0];
	for ( std::vector<std::pair<int, char> >::iterator cipherSymbol = cipherMaxSymbolRange.first; cipherSymbol != cipherMaxSymbolRange.second; ++cipherSymbol) {
		for ( std::vector<std::pair<int, char> >::iterator plainSymbol = plainMaxSymbolRange.first; plainSymbol != plainMaxSymbolRange.second; ++plainSymbol) {
			int shift = ((cipherSymbol->second - plainSymbol->second) + alphabetSize) % alphabetSize;

			std::string shiftedPlain = plainMessage.getShiftedText(shift);
			if (cipherMessage.getText() == shiftedPlain) {
				return shift;
			}
		}
	}

	// no matches
	return -1;
}


