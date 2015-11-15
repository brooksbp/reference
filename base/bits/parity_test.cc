#include "gtest/gtest.h"

#include "base/bits/parity.h"

TEST(ParityTest, ResultsAreSame) {
  EXPECT_EQ(parity(0xF0F0F0F0), parity_scan(0xF0F0F0F0));
  EXPECT_EQ(parity(0xF0F0F0F0), parity_mul(0xF0F0F0F0));
}
