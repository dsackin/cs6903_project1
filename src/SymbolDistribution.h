/*
 * SymbolDistribution.h
 *
 *  Created on: Jun 15, 2014
 *      Author: doug
 */

#ifndef SYMBOLDISTRIBUTION_H_
#define SYMBOLDISTRIBUTION_H_

#include <map>

class SymbolDistribution {
public:
	SymbolDistribution();
	virtual ~SymbolDistribution();

protected:
	std::map<int, char> distribution;
};

#endif /* SYMBOLDISTRIBUTION_H_ */
