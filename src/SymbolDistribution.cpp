/*
 * SymbolDistribution.cpp
 *
 *  Created on: Jun 15, 2014
 *      Author: doug
 */

#include <algorithm>

#include "SymbolDistribution.h"



SymbolDistribution::SymbolDistribution() {
	symbolCount = 0;
	currentShift = 0;
}

SymbolDistribution::SymbolDistribution(std::string &text) {

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

void SymbolDistribution::deriveDistribution(std::string &text) {
	for (std::string::iterator it = text.begin(); it != text.end(); ++it) {
		distribution[*it] += 1;
	}
}

void SymbolDistribution::shiftSymbols(int shift) {

	std::map<char, int> shiftedDistribution;
	for (std::map<char, int>::iterator it = distribution.begin(); it != distribution.end(); ++it) {

		char symbol = it->first;
		int shiftUnwrapped = (symbol - 'a') + (26 + shift);
		int shiftWrapped = shiftUnwrapped % 26;
		char shiftedSymbol = shiftWrapped + 'a';
//		char shiftedSymbol = (int)(it->first - 'a' + shift) % 26 + 'a';

		shiftedDistribution[shiftedSymbol] = it->second;
	}

	distribution = shiftedDistribution;
	currentShift += shift;
}
