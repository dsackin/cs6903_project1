/*
 * SymbolDistribution.cpp
 *
 *  Created on: Jun 15, 2014
 *      Author: doug
 */

#include <algorithm>

#include "SymbolDistribution.h"



SymbolDistribution::SymbolDistribution() {
	this->alphabet = defaultAlphabet;
	symbolCount = 0;
	currentShift = 0;
}

SymbolDistribution::SymbolDistribution(const std::string &text, const std::string &alphabet) {

	this->alphabet = alphabet;

	symbolCount = text.length();
	deriveDistribution(text);
	currentShift = 0;
}

SymbolDistribution::~SymbolDistribution() {

}

bool SymbolDistribution::equalByDistribution(SymbolDistribution &other) {

	return extractFrequenciesRaw() == other.extractFrequenciesRaw();
}

bool SymbolDistribution::equalByNormalizedDistribution(SymbolDistribution &other) {

	return extractFrequenciesNormalized() == other.extractFrequenciesNormalized();
}


bool SymbolDistribution::equalBySymbols(SymbolDistribution &other) {
	return distribution == other.distribution;
}

std::vector<std::pair<int, char> > SymbolDistribution::extractFrequenciesRaw() {

	std::vector<std::pair<int, char> > frequencies;

	for (std::map<char, int>::iterator it = distribution.begin(); it != distribution.end(); ++it) {
		frequencies.push_back(std::pair<int, char>(it->second, it->first));
	}

	std::stable_sort(frequencies.begin(), frequencies.end());

	return frequencies;
}

std::vector<std::pair<float, char> > SymbolDistribution::extractFrequenciesNormalized() {

	std::vector<std::pair<float, char> > frequencies;

	for (std::map<char, int>::iterator it = distribution.begin(); it != distribution.end(); ++it) {
		frequencies.push_back(std::pair<float, char>((float)it->second / symbolCount, it->first));
	}

	std::stable_sort(frequencies.begin(), frequencies.end());

	return frequencies;
}

const std::map<char, int>& SymbolDistribution::getDistribution() const {
	return distribution;
}

void SymbolDistribution::setDistribution(
		const std::map<char, int>& distribution) {
	this->distribution = distribution;
}

int SymbolDistribution::getSymbolCount() const {
	return symbolCount;
}

void SymbolDistribution::setSymbolCount(int symbolCount) {
	this->symbolCount = symbolCount;
}

int SymbolDistribution::getCurrentShift() const {
	return currentShift;
}

void SymbolDistribution::deriveDistribution(const std::string &text) {
	for (std::string::const_iterator it = text.begin(); it != text.end(); ++it) {
		distribution[*it] += 1;
	}
}

void SymbolDistribution::shiftSymbols(int shift) {

	std::map<char, int> shiftedDistribution;
	for (std::map<char, int>::iterator it = distribution.begin(); it != distribution.end(); ++it) {

		char shiftedSymbol = ((it->first - getAlphabet()[0]) + (getAlphabetSize() + shift)) % getAlphabetSize() + getAlphabet()[0];

		shiftedDistribution[shiftedSymbol] = it->second;
	}

	distribution = shiftedDistribution;
	currentShift += shift;
}

std::string SymbolDistribution::getAlphabet() {
	return alphabet;
}

void SymbolDistribution::setAlphabet(std::string alphabet) {
	if (currentShift == 0)
		this->alphabet = alphabet;
	else {
		int oldShift = currentShift;
		shiftSymbols(-1 * currentShift);
		this->alphabet = alphabet;
		shiftSymbols(oldShift);
	}

}
int SymbolDistribution::getAlphabetSize() {
	return SymbolDistribution::alphabet.length();
}

