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
 * SymbolDistribution
 *
 * The SymbolDistribution class represents the frequency counts of the symbols
 * in a Message. The symbols are expected (but not currently required) to be
 * confined to the alphabet defined for a SymbolDistribution. The default
 * alphabet is the lowercase English alphabet.
 *
 * SymbolDistribution has methods to compare two SymbolDistributions by counts
 * (regardless of symbol) and by counts per specific symbol. At this time,
 * distributions are integer counts which requires that Messages being compared
 * by distribution have the same length. If lengths differed, the frequencies
 * could be normalized to the message length, but comparison of these floating
 * point numbers for equality is a trickier prospect.
 *
 */
class SymbolDistribution {
public:

	/**
	 * Default constructor. Assume the default alphabet.
	 */
	SymbolDistribution() {
		this->alphabet = defaultAlphabet;
		symbolCount = 0;
	}

	/**
	 * Common constructor takes the text of the underlying message and an
	 * optional string containing the alphabet. Initiates calculation of the
	 * symbol distribution on setting the text.
	 * @param text - string containing the message text
	 * @param alphabet - optional string containing the symbol alphabet
	 */
	SymbolDistribution(const std::string &text, const std::string &alphabet = defaultAlphabet) {

		this->alphabet = alphabet;

		symbolCount = text.length();
		this->distribution = deriveDistribution(text);
	}

	/**
	 * Default destructor
	 */
	virtual ~SymbolDistribution() { }

	/**
	 * Test for equality between this SymbolDistribution and another by
	 * comparing the symbol counts only. Does not compare the symbol values.
	 * @param other - the other SymbolDistribution
	 * @return bool - true if equal by frequencies only
	 */
	bool equalByDistribution(SymbolDistribution &other) {

		std::vector<std::pair<int, char> > left, right;

		// build sorted list of inverted <count, symbol> pairs for this
		// SymbolDistribution
		left = extractFrequencies();

		// build sorted list of inverted <count, symbol> pairs for the other
		// SymbolDistribution
		right = other.extractFrequencies();

		// simple test to ensure we have the same number of items
		if (left.size() != right.size())
			return false;

		// test if the two lists contain the same counts
		// FrequencyEqualityComparator compares only integer count in the pair
		return std::equal(left.begin(), left.end(), right.begin(),
				FrequencyEqualityComparator());
	}

	/**
	 * Test for total equality between this and another SymbolDistribution. In
	 * this case both the per symbol count must match. We can rely on the
	 * default == operator to test this.
	 * @param other - the other SymbolDistribution
	 * @return bool - true if equal by symbol counts
	 */
	bool equalBySymbols(SymbolDistribution &other) {
		return distribution == other.distribution;
	}

	/**
	 * Return the number of distinct symbols used in the underlying message
	 * @return int - count of distinct symbols in the message
	 */
	int getSymbolCount() const {
		return symbolCount;
	}

	/**
	 * Return the symbol alphabet defined for this SymbolDistribution and its
	 * Message
	 * @return std::string - alphabet for this SymbolDistribution
	 */
	const std::string getAlphabet() const {
		return alphabet;
	}

	/**
	 * Return the length of the alphabet
	 * @return int - length of the alphabet
	 */
	const int getAlphabetSize() const  {
		return getAlphabet().length();
	}



	/**
	 * Invert the symbol distribution, providing a list of pairs representing a
	 * count and the symbol counted. This list is stably sorted so that symbols
	 * with the same frequency appear in the same order as in the alphabet.
	 * @return std::vector<std::pair<int, char>> - list of counts and their
	 * symbols
	 */
	std::vector<std::pair<int, char> > extractFrequencies() const {

		std::vector<std::pair<int, char> > frequencies;

		std::pair<int, char> symbolFrequency;
		// iterate through the map, extracting each <symbol, count> pair and
		// inserting it into a new list as a <count, symbol> pair
		for (std::map<char, int>::const_iterator it = distribution.begin(); it != distribution.end(); ++it) {
			symbolFrequency = std::pair<int, char>(it->second, it->first);

			frequencies.push_back(symbolFrequency);
		}

		// sort the new list by frequency, but maintaining the original symbol
		// ordering for equal counts
		std::stable_sort(frequencies.begin(), frequencies.end());

		return frequencies;
	}


protected:
	// symbol set used by this SymbolDistribution and underlying Message
	std::string alphabet;

	// map backing this distribution
	std::map<char, int> distribution;

	// count of distinct symbols used in the underlying Message
	int symbolCount;

	/**
	 * Calculate the symbol distribution for the text string provided.
	 * @param text - string over which to calculate symbol distribution
	 * @return std::map<char, int> - map using symbol as key and count as value
	 */
	static std::map<char, int> deriveDistribution(const std::string &text) {
		std::map<char, int> distribution;

		// iterate through the text, indexing the map by symbol as key and
		// incrementing the count value by one for each time the symbol is encountered.
		for (std::string::const_iterator it = text.begin(); it != text.end(); ++it) {
			distribution[*it] += 1;
		}

		return distribution;
	}

	/**
	 * Inner utility class to implement comparison of two <int, char> pairs,
	 * ignoring the value of the chars.
	 */
	struct FrequencyEqualityComparator
	{
	    bool operator() ( std::pair<int, char> lhs, std::pair<int, char> rhs)
	    {
	        return lhs.first == rhs.first;
	    }
	 };
};

#endif /* SYMBOLDISTRIBUTION_H_ */
