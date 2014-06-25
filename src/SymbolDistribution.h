/*
 * SymbolDistribution.h
 *
 *  Created on: Jun 15, 2014
 *      Author: Douglas Sackin, NYU CS6903, Summer 2014
 */

#ifndef SYMBOLDISTRIBUTION_H_
#define SYMBOLDISTRIBUTION_H_

#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#include "prettyprint/prettyprint.hpp"

static std::string defaultAlphabet = std::string("abcdefghijklmnopqrstuvwxyz");

/**
 *
 */
class SymbolDistribution {
public:

	/**
	 *
	 */
	SymbolDistribution() {
		this->alphabet = defaultAlphabet;
		symbolCount = 0;
		currentShift = 0;
	}

	/**
	 *
	 * @param text
	 * @param alphabet
	 */
	SymbolDistribution(const std::string &text, const std::string &alphabet = defaultAlphabet) {

		this->alphabet = alphabet;

		symbolCount = text.length();
		this->distribution = deriveDistribution(text);
		currentShift = 0;
	}

	/**
	 *
	 */
	virtual ~SymbolDistribution() { }

	/**
	 *
	 * @param other
	 * @return
	 */
	bool equalByDistribution(SymbolDistribution &other) {

		std::vector<std::pair<int, char> > left, right;
		left = extractFrequencies();
		right = other.extractFrequencies();

	//	std::cout << left << std::endl << right << std::endl;

		if (left.size() != right.size())
			return false;

		return std::equal(left.begin(), left.end(), right.begin(), FrequencyEqualityComparator());
	}

	/**
	 *
	 * @param other
	 * @return
	 */
	bool equalBySymbols(SymbolDistribution &other) {
		return distribution == other.distribution;
	}

	/**
	 *
	 * @return
	 */
	const std::map<char, int>& getDistribution() const  {
		return distribution;
	}

	/**
	 *
	 * @return
	 */
	int getSymbolCount() const {
		return symbolCount;
	}

	/**
	 *
	 * @param shift
	 */
	void shiftSymbols(int shift) {

		std::map<char, int> shiftedDistribution;
		for (std::map<char, int>::iterator it = distribution.begin(); it != distribution.end(); ++it) {

			char shiftedSymbol = ((it->first - getAlphabet()[0]) + (getAlphabetSize() + shift)) % getAlphabetSize() + getAlphabet()[0];

			shiftedDistribution[shiftedSymbol] = it->second;
		}

		distribution = shiftedDistribution;
		currentShift += shift;
	}

	/**
	 *
	 * @return
	 */
	int getCurrentShift() const {
		return currentShift;
	}

	/**
	 *
	 * @return
	 */
	const std::string getAlphabet() const {
		return alphabet;
	}

	/**
	 *
	 * @param alphabet
	 */
	void setAlphabet(const std::string alphabet)  {
		if (currentShift == 0)
			this->alphabet = alphabet;
		else {
			int oldShift = currentShift;
			shiftSymbols(-1 * currentShift);
			this->alphabet = alphabet;
			shiftSymbols(oldShift);
		}
	}

	/**
	 *
	 * @return
	 */
	const int getAlphabetSize() const  {
		return SymbolDistribution::alphabet.length();
	}



	/**
	 *
	 * @return
	 */
	std::vector<std::pair<int, char> > extractFrequencies() const {

		std::vector<std::pair<int, char> > frequencies;

		std::pair<int, char> symbolFrequency;
		for (std::map<char, int>::const_iterator it = distribution.begin(); it != distribution.end(); ++it) {
			symbolFrequency = std::pair<int, char>(it->second, it->first);

			frequencies.push_back(symbolFrequency);
		}

		std::stable_sort(frequencies.begin(), frequencies.end());

		return frequencies;
	}


protected:
	std::string alphabet;

	std::map<char, int> distribution;
	int symbolCount;
	int currentShift;

	/**
	 *
	 * @param text
	 * @return
	 */
	static std::map<char, int> deriveDistribution(const std::string &text) {
		std::map<char, int> distribution;
		for (std::string::const_iterator it = text.begin(); it != text.end(); ++it) {
			distribution[*it] += 1;
		}

		return distribution;
	}

	/**
	 *
	 */
	struct FrequencyEqualityComparator
	{
	    bool operator() ( std::pair<float, char> lhs, std::pair<float, char> rhs)
	    {
	        return lhs.first == rhs.first;
	    }
	 };
};

#endif /* SYMBOLDISTRIBUTION_H_ */
