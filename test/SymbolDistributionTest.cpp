/*
 * SymbolDistributionTest.cpp
 *
 *  Created on: Jun 15, 2014
 *      Author: doug
 */

#include "../src/SymbolDistribution.h"

#include "gtest/gtest.h"

class SymbolDistributionTest: public ::testing::Test {
	void SetUp() {
		std::string s = "";
		d0 = SymbolDistribution(s);

		s = "abcdabcdabczfghhyz";
		d1 = SymbolDistribution(s);

		s = "cdacabzfghhyzbcdab";
		d2 = SymbolDistribution(s);

		s = "zbcdabcdacabzfghhyzbcdabcdcdacabzfghhyacabzfghhyzbcdab";
		d3 = SymbolDistribution(s);

		s = "thisisadifferentdistribution";
		d4 = SymbolDistribution();

		m1dist['a'] = 3;
		m1dist['b'] = 3;
		m1dist['c'] = 3;
		m1dist['d'] = 2;
		m1dist['f'] = 1;
		m1dist['g'] = 1;
		m1dist['h'] = 2;
		m1dist['y'] = 1;
		m1dist['z'] = 2;
		m1 = SymbolDistribution();
		m1.setSymbolCount(18);
		m1.setDistribution(m1dist);

		s1dist['d'] = 3;
		s1dist['e'] = 3;
		s1dist['f'] = 3;
		s1dist['g'] = 2;
		s1dist['i'] = 1;
		s1dist['j'] = 1;
		s1dist['k'] = 2;
		s1dist['b'] = 1;
		s1dist['c'] = 2;
		s1 = SymbolDistribution();
		s1.setSymbolCount(18);
		s1.setDistribution(s1dist);

		s2dist['y'] = 3;
		s2dist['z'] = 3;
		s2dist['a'] = 3;
		s2dist['b'] = 2;
		s2dist['d'] = 1;
		s2dist['e'] = 1;
		s2dist['f'] = 2;
		s2dist['w'] = 1;
		s2dist['x'] = 2;
		s2 = SymbolDistribution();
		s2.setSymbolCount(18);
		s2.setDistribution(s2dist);

	}

protected:

	std::map<char, int> m0dist, m1dist, s1dist, s2dist;

	SymbolDistribution d0, d1, d2, d3, d4;
	SymbolDistribution m1;
	SymbolDistribution s1, s2;

};

TEST_F(SymbolDistributionTest, DistributionDerivation) {
	ASSERT_EQ(m0dist, d0.getDistribution());
	ASSERT_EQ(m1dist, d1.getDistribution());
	ASSERT_TRUE(d1.getDistribution() == d2.getDistribution());
	ASSERT_FALSE(d1.getDistribution() == d3.getDistribution());
	ASSERT_FALSE(d1.getDistribution() == d4.getDistribution());
}

TEST_F(SymbolDistributionTest, DistributionEquality) {
	ASSERT_TRUE(d1.equalByDistribution(d2));
	ASSERT_TRUE(d1.equalByNormalizedDistribution(d2));
	ASSERT_TRUE(d1.equalBySymbols(d2));
	ASSERT_FALSE(d1.equalByDistribution(d3));
	ASSERT_TRUE(d1.equalByNormalizedDistribution(d3));
	ASSERT_FALSE(d1.equalBySymbols(d3));
	ASSERT_FALSE(d1.equalBySymbols(d4));
	ASSERT_FALSE(d1.equalByDistribution(d4));
	ASSERT_FALSE(d1.equalByNormalizedDistribution(d4));
	ASSERT_FALSE(d1.equalBySymbols(d0));
	ASSERT_FALSE(d1.equalByDistribution(d0));
	ASSERT_FALSE(d1.equalByNormalizedDistribution(d0));
}

TEST_F(SymbolDistributionTest, SymbolShift) {
	d1.shiftSymbols(3);
	d3.shiftSymbols(3);
	ASSERT_EQ(3, d1.getCurrentShift());
	ASSERT_EQ(3, d3.getCurrentShift());

	ASSERT_EQ(s1dist, d1.getDistribution());
	ASSERT_FALSE(d1.equalByDistribution(d2));
	ASSERT_FALSE(d1.equalByNormalizedDistribution(d2));
	ASSERT_TRUE(d1.equalByNormalizedDistribution(d3));
	ASSERT_FALSE(d1.equalByDistribution(d4));

	d2.shiftSymbols(-2);
	ASSERT_EQ(-2, d2.getCurrentShift());

	ASSERT_EQ(s2dist, d2.getDistribution());
	ASSERT_FALSE(d2.equalByDistribution(d1));

	d1.shiftSymbols(-5);
	ASSERT_EQ(-2, d1.getCurrentShift());

	ASSERT_EQ(s2dist, d1.getDistribution());
	ASSERT_TRUE(d2.equalByDistribution(d1));


}
