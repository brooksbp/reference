#include "gtest/gtest.h"

#include "base/bits/powers_of_two.h"

TEST(PowersOfTwoTest, floor2) {
  EXPECT_EQ(0, floor2(0));
  EXPECT_EQ(1, floor2(1));
  EXPECT_NE(1, floor2(2));
  EXPECT_EQ(2, floor2(2));

  EXPECT_EQ(1<<4, floor2( (1<<4)+1 ));
  EXPECT_NE(1<<4, floor2(  1<<5 ));
}

TEST(PowersOfTwoTest, ceil2) {
  EXPECT_EQ(0, ceil2(0));
  EXPECT_EQ(1, ceil2(1));
  EXPECT_NE(1, ceil2(2));

  EXPECT_EQ(1<<4, ceil2( (1<<4)-1 ));
}
