/*
 * MessageTest.cpp
 *
 *  Created on: Jun 15, 2014
 *      Author: doug
 */

#include "gtest/gtest.h"

#include "../src/Message.h"

class MessageTest: public ::testing::Test {
	void SetUp() {
		message = Message("abcd");
	}

protected:
	Message message;
};
TEST_F(MessageTest, Message) {
  ASSERT_EQ("abcd", message.getText());
}

