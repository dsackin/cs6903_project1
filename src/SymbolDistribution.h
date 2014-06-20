/*
 * SymbolDistribution.h
 *
 *  Created on: Jun 15, 2014
 *      Author: doug
 */

#ifndef SYMBOLDISTRIBUTION_H_
#define SYMBOLDISTRIBUTION_H_

#include <map>
#include <string>
#include <vector>

static std::string defaultAlphabet = std::string("abcdefghijklmnopqrstuvwxyz");

class SymbolDistribution {
public:

	SymbolDistribution();
	SymbolDistribution(const std::string &text, const std::string &alphabet = defaultAlphabet);
	virtual ~SymbolDistribution();

	bool equalByDistribution(SymbolDistribution &other);
	bool equalByNormalizedDistribution(SymbolDistribution &other);
	bool equalBySymbols(SymbolDistribution &other);
	const std::map<char, int>& getDistribution() const;
	void setDistribution(const std::map<char, int>& distribution);
	int getSymbolCount() const;
	void setSymbolCount(int symbolCount);

	void shiftSymbols(int shift);
	int getCurrentShift() const;

	const std::string getAlphabet() const;
	void setAlphabet(const std::string alphabet);
	const int getAlphabetSize() const;

	std::vector<std::pair<int, char> > extractFrequenciesRaw() const;
	std::vector<std::pair<float, char> > extractFrequenciesNormalized() const;


protected:
	std::string alphabet;

	std::map<char, int> distribution;
	int symbolCount;
	int currentShift;


	static std::map<char, int> deriveDistribution(const std::string &text);
};

#endif /* SYMBOLDISTRIBUTION_H_ */
