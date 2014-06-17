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

#define ALPHABET "abcdefghijklmnopqrstuvwxyz"
#define ALPHABET_SIZE "26"

class SymbolDistribution {
public:

	SymbolDistribution();
	SymbolDistribution(std::string &text);
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

protected:
	std::map<char, int> distribution;
	int symbolCount;
	int currentShift;

	std::vector<std::pair<int, char> > extractFrequenciesRaw();

	std::vector<std::pair<float, char> > extractFrequenciesNormalized();

	void deriveDistribution(std::string &text);
};

#endif /* SYMBOLDISTRIBUTION_H_ */
