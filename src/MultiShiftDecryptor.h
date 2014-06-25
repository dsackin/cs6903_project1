/*
 * MultiShiftDecryptor.h
 *
 *  Created on: Jun 18, 2014
 *      Author: Douglas Sackin, NYU CS6903, Summer 2014
 */

#ifndef MULTISHIFTDECRYPTOR_H_
#define MULTISHIFTDECRYPTOR_H_

#include <vector>
#include <string>
#include <math.h>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "prettyprint/prettyprint.hpp"

#include "Message.h"
#include "Decryptor.h"


class MultiShiftDecryptor : public Decryptor {
public:
	MultiShiftDecryptor() : keyLength(1) {}
	MultiShiftDecryptor(int index, std::string plainText,
			std::string cipherText, int keyLength = 1) : Decryptor(index, plainText, cipherText) {

		this->keyLength = keyLength;
	}

	virtual ~MultiShiftDecryptor() {
	}

	bool decrypt() {

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
					keyShifts.push_back(keyValue);
				} else
					return false;
			}

			return true;
		}

	const std::vector<Message>& getCipherSegments() const {
		return cipherSegments;
	}

	int getKeyLength() const {
		return keyLength;
	}

	/**
	 *
	 *
	 * @return
	 */
	const std::vector<Message>& getPlainSegments() const {
		return plainSegments;
	}

	/**
	 *
	 * @return
	 */
	const std::string getExplanation() const {
		std::string explanation;
		std::ostringstream os(explanation);

		os << "Decrypted cipher text found to match plain text at index " << dictionaryIndex << ". This appears to be a ";

		std::set<int> uniqueShifts(getKeyShifts().begin(), getKeyShifts().end());

		if (uniqueShifts.size() == 1) {
			char keySymbol = *(uniqueShifts.begin()) + plainSegments[0].getDistribution().getAlphabet()[0];
			os << "simple shift cipher using a shift of " << *uniqueShifts.begin() << " or '" << keySymbol << "'.";
		} else {
			os << "polyalphabetic shift cipher using an effective shift sequence of " << getKeyShifts() << " or '" << getKeyString() << "'.";
		}

		return std::string(os.str());
	}

	/**
	 *
	 * @return
	 */
	const std::vector<int> &getKeyShifts() const {
		return keyShifts;
	}

	/**
	 *
	 * @return
	 */
	const std::string getKeyString() const {
		std::string keyString;
		for (std::vector<int>::const_iterator it = keyShifts.begin(); it != keyShifts.end(); ++it) {
			char keySymbol = *it + plainSegments[0].getDistribution().getAlphabet()[0];
			keyString +=  keySymbol;
		}
		return keyString;
	}

protected:
	int keyLength;
	std::vector<Message> plainSegments;
	std::vector<Message> cipherSegments;
	std::vector<int> keyShifts;

	void initialize() {
		plainSegments = deriveSegments(plainText, keyLength);
		cipherSegments = deriveSegments(cipherText, keyLength);
		isInitialized = true;
	}

	static std::vector<Message> deriveSegments(std::string text, int keyLength)  {
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

	struct FrequencyOrderComparator
	{
	    bool operator() ( const std::pair<int, char>& lhs, const std::pair<int, char>& rhs)
	    {
	        return lhs.first < rhs.first;
	    }
	 };


	static int determineSegmentKey(Message &plainMessage, Message &cipherMessage) {
		std::vector<std::pair<int, char> > plainFreqs = plainMessage.getDistribution().extractFrequencies();
		std::vector<std::pair<int, char> > cipherFreqs = cipherMessage.getDistribution().extractFrequencies();

		// extractFrequenciesRaw() returned vector of std::pair<int, char>
		// stably sorted in ascending order by count, then symbol, so the
		// most frequent symbol in the cipher should be the last pair in the list.
		std::pair<int, char> cipherMostFrequentSymbol = cipherFreqs.back();
		std::pair<std::vector<std::pair<int, char> >::iterator, std::vector<std::pair<int, char> >::iterator> cipherMaxSymbolRange = std::equal_range(cipherFreqs.begin(), cipherFreqs.end(), cipherMostFrequentSymbol, FrequencyOrderComparator());
		std::pair<std::vector<std::pair<int, char> >::iterator, std::vector<std::pair<int, char> >::iterator> plainMaxSymbolRange = std::equal_range(plainFreqs.begin(), plainFreqs.end(), cipherMostFrequentSymbol, FrequencyOrderComparator());

		int alphabetSize = plainMessage.getDistribution().getAlphabetSize();
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


};
#endif /* MULTISHIFTDECRYPTOR_H_ */
