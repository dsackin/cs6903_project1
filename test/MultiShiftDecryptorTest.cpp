/*
 * MultiShiftDecryptorTest.cpp
 *
 *  Created on: Jun 18, 2014
 *      Author: doug
 */

#include <iostream>

#include "gtest/gtest.h"
#include "prettyprint/prettyprint.hpp"

#include "../src/MultiShiftDecryptor.h"

class MultiShiftDecryptorTest: public ::testing::Test {
	void SetUp() {

		p1 = "abcabcab";
		c1 = "bcdbcdbc";
		p2 = "bacbacba";
		c2 = "zyazyazy";
		p3 = "efghiefghiefghiefghiefghiefghiefg";
		c3 = "defghdefghdefghdefghdefghdefghdef";

		m0 = MultiShiftDecryptor(0, p1, c1, 1);			// key = 'a'
		m1 = MultiShiftDecryptor(1, p1, c1, 3);			// key = 'aaa'

		m00 = MultiShiftDecryptor(0, p2, c2, 1);		// key = 'y'
		m2 = MultiShiftDecryptor(2, p2, c2, 3);			// key = 'yyy'

		m3 = MultiShiftDecryptor(3, p3, c3, 5); 		// key = 'zzzzz'

		m4 = MultiShiftDecryptor(4, p1, p2, 1);			// no key

		m5 = MultiShiftDecryptor(0, p3, c2, 1);			// different lengths, no key

	}

protected:
	MultiShiftDecryptor m0, m00, m1, m2, m3, m4, m5, m6;
	std::string p1, c1, p2, c2, p3, c3;
};

TEST_F(MultiShiftDecryptorTest, ConstructorTest) {
  ASSERT_EQ(m0.getPlainSegments()[0].getText(), "abcabcab");
  ASSERT_EQ(m0.getCipherSegments()[0].getText(), "bcdbcdbc");

  ASSERT_EQ(m1.getPlainSegments()[0].getText(), "aaa");
  ASSERT_EQ(m1.getCipherSegments()[0].getText(), "bbb");

  ASSERT_EQ(m1.getPlainSegments()[1].getText(), "bbb");
  ASSERT_EQ(m1.getCipherSegments()[1].getText(), "ccc");

  ASSERT_EQ(m1.getPlainSegments()[2].getText(), "cc");
  ASSERT_EQ(m1.getCipherSegments()[2].getText(), "dd");

  ASSERT_EQ(m0.getPlainSegments()[0].getDistribution().getDistribution(), m00.getPlainSegments()[0].getDistribution().getDistribution());

  SymbolDistribution m0Sym = m0.getPlainSegments()[0].getDistribution();
  SymbolDistribution m00Sym = m00.getPlainSegments()[0].getDistribution();

  ASSERT_TRUE(m0Sym.equalByDistribution(m00Sym));

}

TEST_F(MultiShiftDecryptorTest, DecryptTest) {
//	ASSERT_TRUE(m0.decrypt());
//	ASSERT_EQ(m0.getKeySolution(), "a");
//	ASSERT_TRUE(m1.decrypt());
//	ASSERT_EQ(m1.getKeySolution(), "aaa");
	ASSERT_TRUE(m2.decrypt());
	ASSERT_EQ(m2.getKeySolution(), "yyy");
	ASSERT_TRUE(m3.decrypt());
	ASSERT_EQ(m3.getKeySolution(), "zzzzz");
	ASSERT_TRUE(m00.decrypt());
	ASSERT_EQ(m00.getKeySolution(), "y");
	ASSERT_FALSE(m4.decrypt());
	ASSERT_FALSE(m5.decrypt());

}
