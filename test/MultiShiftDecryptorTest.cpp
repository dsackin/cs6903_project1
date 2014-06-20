/*
 * MultiShiftDecryptorTest.cpp
 *
 *  Created on: Jun 18, 2014
 *      Author: doug
 */

#include "gtest/gtest.h"

#include "../src/MultiShiftDecryptor.h"

class MultiShiftDecryptorTest: public ::testing::Test {
	void SetUp() {

		p1 = "abcabcab";
		c1 = "bcdbcdbc";
		p2 = "bacbacba";
		c2 = "zyazyazy";
		p3 = "efghiefghiefghiefghiefghiefghiefg";
		c3 = "defghdefghdefghdefghdefghdefghdef";

		m0 = MultiShiftDecryptor(0, p1, c1, 1);
		m1 = MultiShiftDecryptor(1, "abcabcab", "bcdbcdbc", 3);

		m00 = MultiShiftDecryptor(0, "bacbacba", "zyazyazy", 1);
		m2 = MultiShiftDecryptor(2, "bacbacba", "zyazyazy", 3);

		m3 = MultiShiftDecryptor(3, "efghiefghiefghiefghiefghiefghiefg", "defghdefghdefghdefghdefghdefghdef", 5);

	}

protected:
	MultiShiftDecryptor m0, m00, m1, m2, m3;
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
