#include "gtest/gtest.h"

#include "base/bits/popcount.h"

TEST(PopcountTest, ResultsAreSame) {
  EXPECT_EQ(popcount(0xF0F0F0F0), popcount_drop_lsb(0xF0F0F0F0));
}
