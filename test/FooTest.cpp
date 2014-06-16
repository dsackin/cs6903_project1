#include "gtest/gtest.h"
#include "Foo.h"

class FooTest: public ::testing::Test {

protected:
	Foo foo;
};
TEST_F(FooTest, Foo) {
  ASSERT_TRUE(foo.foo());
}

